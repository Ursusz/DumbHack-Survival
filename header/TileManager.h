#pragma once
#include <map>
#include <SFML/Graphics/RenderTarget.hpp>
#include <fstream>
#include "../header/Tile.h"

class TileManager{
    int number_of_tiles_per_window_width = 40;
    int number_of_tiles_per_window_height = 23;

    static constexpr int width = 40;
    static constexpr int height = 23;
    
    std::vector<std::vector<int>> mapLoader = std::vector<std::vector<int>>(height, std::vector<int>(width));
    std::vector<std::vector<Tile>> map = std::vector<std::vector<Tile>>(height, std::vector<Tile>(width));

    std::map<int, std::string> m_textures;
public:
    TileManager() = default;
    TileManager(const TileManager& rhs);
    ~TileManager() = default;

    Tile& getTile(size_t i, size_t j);

    TileManager& operator=(const TileManager& rhs);
    void loadMap(const std::string& mapFile);
    void printMap(sf::RenderTarget& target);
};