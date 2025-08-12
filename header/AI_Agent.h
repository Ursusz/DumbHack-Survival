#pragma once
#include <cpr/cpr.h>
#include <nlohmann/json.hpp>
#include <string>
#include <thread>
#include <mutex>
#include <vector>
#include <utility>

class GameEngine;

class AI_Agent {
    std::thread m_botCommunicationThread;

    bool m_stopBotCommunicationThread = false;

    std::string m_serializedGameState;

    std::mutex m_GameDataMutex;

    int m_agentAction = -1;
    std::mutex m_actionMutex;

    float playerX = 0, playerY = 0;
    int playerHP = 100;

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