#pragma once
#include <map>
#include <SFML/Graphics/RenderTarget.hpp>
#include <fstream>
#include "../header/Tile.h"

class TileManager{
    enum : int {
        number_of_tiles_per_window_width = 40,
        number_of_tiles_per_window_height = 23
    };

    std::array<std::array<int, number_of_tiles_per_window_width>, number_of_tiles_per_window_height> mapLoader;
    std::array<std::array<Tile, number_of_tiles_per_window_width>, number_of_tiles_per_window_height> map;

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