#include "../header/TileManager.h"

#include <fstream>

#include "SFML/Graphics/RenderTarget.hpp"

TileManager::TileManager() {
    mapLoader = new int*[number_of_tiles_per_window_width];
    for(int i = 0; i < number_of_tiles_per_window_width; i++) {
        mapLoader[i] = new int[number_of_tiles_per_window_height];
    }

    map = new Tile*[number_of_tiles_per_window_width];
    for(int i = 0; i < number_of_tiles_per_window_width; i++) {
        map[i] = new Tile[number_of_tiles_per_window_height];
    }
}

TileManager::TileManager(const TileManager& rhs) {
    mapLoader = new int*[number_of_tiles_per_window_width];
    for(int i = 0; i < number_of_tiles_per_window_width; i++) {
        mapLoader[i] = new int[number_of_tiles_per_window_height];
    }
    map = new Tile*[number_of_tiles_per_window_width];
    for(int i = 0; i < number_of_tiles_per_window_width; i++) {
        map[i] = new Tile[number_of_tiles_per_window_height];
    }
    for(int i = 0; i < number_of_tiles_per_window_width; i++) {
        for(int j = 0; j < number_of_tiles_per_window_height; j++) {
            mapLoader[i][j] = rhs.mapLoader[i][j];
        }
    }
}

TileManager& TileManager::operator=(const TileManager& rhs) {
    if (this == &rhs) {
        return *this;
    }
    for (int i = 0; i < number_of_tiles_per_window_height; ++i) {
        delete[] mapLoader[i];
        delete[] map[i];
    }
    delete[] mapLoader;
    delete[] map;

    mapLoader = new int*[number_of_tiles_per_window_height];
    for (int i = 0; i < number_of_tiles_per_window_height; ++i) {
        mapLoader[i] = new int[number_of_tiles_per_window_width];
    }

    map = new Tile*[number_of_tiles_per_window_height];
    for (int i = 0; i < number_of_tiles_per_window_height; ++i) {
        map[i] = new Tile[number_of_tiles_per_window_width];
    }
    m_textures = rhs.m_textures;

    for (int i = 0; i < number_of_tiles_per_window_height; ++i) {
        for (int j = 0; j < number_of_tiles_per_window_width; ++j) {
            mapLoader[i][j] = rhs.mapLoader[i][j];
            map[i][j] = rhs.map[i][j];
        }
    }

    return *this;
}


TileManager::~TileManager() {
    for(int i = 0; i < number_of_tiles_per_window_width; i++) {
        delete[] mapLoader[i];
    }
    delete[] mapLoader;

    for(int i = 0; i < number_of_tiles_per_window_width; i++) {
        delete[] map[i];
    }
    delete[] map;
}


void TileManager::loadMap(const std::string &mapFile) {
    m_textures.insert({0, "assets/WoodenPlank.png"});
    std::ifstream file(mapFile);
    if (!file.is_open()) {
        std::cerr << "Could not open file " << mapFile << std::endl;
    }

    for(int i = 0; i < number_of_tiles_per_window_width; i++) {
        for(int j = 0; j < number_of_tiles_per_window_height; j++) {
            file >> mapLoader[i][j];
            map[i][j] = Tile(myVec(i*48 + 24, j*48 + 24), m_textures.at(mapLoader[i][j]));
        }
    }
    file.close();
}

void TileManager::printMap(sf::RenderTarget& target) {
    for(int i = 0; i < number_of_tiles_per_window_width; i++) {
        for(int j = 0; j < number_of_tiles_per_window_height; j++) {
            map[i][j].draw(target);
        }
    }
}