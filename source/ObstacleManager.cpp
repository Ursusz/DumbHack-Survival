#include <fstream>

#include "../header/ObstacleManager.h"

ObstacleManager& ObstacleManager::getInstance() {
    static ObstacleManager instance;
    return instance;
}

void ObstacleManager::loadObstaclesWithBuffer(const std::string& filePath, int mapHeight, int mapWidth) {
    std::ifstream in(filePath);
    int obstacleReader;

    /// padding the obstacles in all directions, even wihtout diagonal padding
    /// makes the fps drop a lot, idk why :(
    // const std::vector<sf::Vector2i> directions = {
    //     {0, 0}, {1, 0}, {-1, 0}, {0, 1}, {0, -1},
    //     {1, 1}, {-1, 1}, {1, -1}, {-1, -1}
    // };
    // const std::vector<sf::Vector2i> directions = {
    //     {0, 0}, {1, 0}, {-1, 0}, {0, 1}, {0, -1}
    // };

    const std::vector<sf::Vector2i> directions = {
        {0, 0}
    };

    for (int i = 0; i < mapHeight; i++) {
        for (int j = 0; j < mapWidth; j++) {
            in >> obstacleReader;
            if (obstacleReader != 0) {
                for (const auto& dir : directions) {
                    sf::Vector2i bufferTile = {i + dir.x, j + dir.y};
                    if (bufferTile.x >= 0 && bufferTile.x < mapHeight &&
                        bufferTile.y >= 0 && bufferTile.y < mapWidth) {
                        obstacles.push_back(bufferTile);
                        }
                }
            }
        }
    }
    in.close();
}

const std::vector<sf::Vector2i>& ObstacleManager::getObstacles() const {
    return obstacles;
}
