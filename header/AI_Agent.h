#pragma once

#include <string>
#include <thread>
#include <mutex>
#include <iostream>
#include <vector>
#include <nlohmann/json.hpp>
#include <utility>
#include <cpr/cpr.h>

class GameEngine;

class AI_Agent {
    std::thread m_botCommunicationThread;

    bool m_stopBotCommunicationThread = false;

    std::string m_serializedGameState;

    std::mutex m_GameDataMutex;

    int m_agentAction = -1;
    std::mutex m_actionMutex;

    float playerX, playerY;
    int playerHP;


    std::vector<std::pair<float, float>> zombiesPositions;
    std::vector<std::pair<float, float>> computerPositions;
    std::vector<int> computersCompletions;
    std::vector<std::pair<float, float>> trapsPositions;

    void botCommunicationLoop(const GameEngine& game);
public:
    void updateGameState(const GameEngine& game);
    void updateBotData();

    void startBotCommunication(GameEngine& game);
    void stopBotCommunication();

    int getAgentAction();
};