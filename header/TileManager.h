#pragma once
#include <map>

#include "../header/Tile.h"

class TileManager{
    const int number_of_tiles_per_window_width = 40;
    const int number_of_tiles_per_window_height = 23;

    int **mapLoader;
    Tile **map;

    std::map<int, std::string> m_textures;
public:
    TileManager();
    ~TileManager();
    void loadMap(const std::string& mapFile);
    void printMap(sf::RenderTarget& target);
};