// AI_Agent.cpp
#include "../header/AI_Agent.h"

#include "GameEngine.h"

void AI_Agent::updateGameState(const GameEngine& game) {
    std::lock_guard<std::mutex> lock(m_GameDataMutex);

    playerX = game.getPlayer().getPositionFromComp().getX();
    playerY = game.getPlayer().getPositionFromComp().getY();
    playerHP = game.getPlayer().getHP();

    zombiesPositions = game.getZombiesPositions();
    computerPositions = game.getComputerPositions();
    computersCompletions = game.getComputersCompletions();
    trapsPositions = game.getTrapsPositions();
}

void AI_Agent::updateBotData() {
    std::lock_guard<std::mutex> lock(m_GameDataMutex);

    m_serializedGameState = "{";
    m_serializedGameState += "\"player\":{";
    m_serializedGameState += "\"x\":" + std::to_string(playerX) + ",";
    m_serializedGameState += "\"y\":" + std::to_string(playerY) + ",";
    m_serializedGameState += "\"hp\":" + std::to_string(playerHP);
    m_serializedGameState += "},";

    m_serializedGameState += "\"zombies\":[";
    for(size_t i = 0; i < zombiesPositions.size(); ++i) {
        m_serializedGameState += "{";
        m_serializedGameState += "\"x\":" + std::to_string(zombiesPositions[i].first) + ",";
        m_serializedGameState += "\"y\":" + std::to_string(zombiesPositions[i].second);
        m_serializedGameState += "}";
        if (i < zombiesPositions.size() - 1) {
            m_serializedGameState += ",";
        }
    }
    m_serializedGameState += "],";

    m_serializedGameState += "\"computers\":[";
    for(size_t i = 0; i < computerPositions.size(); ++i) {
        m_serializedGameState += "{";
        m_serializedGameState += "\"completion\":" + std::to_string(computersCompletions[i]);
        m_serializedGameState += "}";
        if (i < computerPositions.size() - 1) {
            m_serializedGameState += ",";
        }
    }
    m_serializedGameState += "]";

    m_serializedGameState += "}";
}

void AI_Agent::startBotCommunication(GameEngine& game) {
    m_botCommunicationThread = std::thread(&AI_Agent::botCommunicationLoop, this, std::ref(game));
}

void AI_Agent::botCommunicationLoop(const GameEngine& game) {
    cpr::Url update_state_url{"http://127.0.0.1:5002/update_state"};
    cpr::Url get_action_url{"http://127.0.0.1:5002/get_action"};

    while (!m_stopBotCommunicationThread) {
        cpr::Response action_res = cpr::Get(get_action_url);

        if (action_res.status_code == 200) {
            try {
                auto json_response = nlohmann::json::parse(action_res.text);
                if (json_response.contains("action") && !json_response["action"].is_null()) {
                    std::lock_guard<std::mutex> lock(m_actionMutex);
                    m_agentAction = json_response["action"].get<int>();
                    // std::cout << m_agentAction << std::endl;
                }
            } catch (const nlohmann::json::parse_error& e) {
                std::cerr << "Eroare la parsarea JSON pentru actiune: " << e.what() << std::endl;
            }
        } else {
            std::cerr << "Eroare la primirea actiunii: " << action_res.status_code << std::endl;
        }

        updateGameState(game);
        updateBotData();

        std::string json_data_to_send;
        {
            std::lock_guard<std::mutex> lock(m_GameDataMutex);
            json_data_to_send = m_serializedGameState;
        }

        cpr::Response state_res = cpr::Post(update_state_url,
                                             cpr::Header{{"Content-Type", "application/json"}},
                                             cpr::Body{json_data_to_send});
        // std::cout<<json_data_to_send<<std::endl;

        if (state_res.status_code != 200) {
            std::cerr << "Eroare la trimiterea starii: " << state_res.status_code << std::endl;
        }

        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
}

void AI_Agent::stopBotCommunication() {
    m_stopBotCommunicationThread = true;

    if (m_botCommunicationThread.joinable()) {
        m_botCommunicationThread.join();
    }
}

int AI_Agent::getAgentAction() {
    std::lock_guard<std::mutex> lock(m_actionMutex);
    int currentAction = m_agentAction;
    m_agentAction = -1;
    return currentAction;
}
