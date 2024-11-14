#include "../header/TileManager.h"

TileManager::TileManager(const TileManager& rhs)
    : mapLoader(rhs.mapLoader)
    , map(rhs.map)
    , m_textures(rhs.m_textures)
{}

TileManager& TileManager::operator=(const TileManager& rhs) {
     if (this == &rhs) {
         return *this;
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

Tile& TileManager::getTile(size_t i, size_t j) {
    return map[i][j];
}


void TileManager::loadMap(const std::string &mapFile) {
    m_textures.insert({0, "assets/WoodenPlank.png"});
    m_textures.insert({1, "assets/pixil-frame-0 (5).png"});
    std::ifstream file(mapFile);
    if (!file.is_open()) {
        std::cerr << "Could not open file " << mapFile << std::endl;
    }

    for(int i = 0; i < number_of_tiles_per_window_height; i++) {
        for(int j = 0; j < number_of_tiles_per_window_width; j++) {
            file >> mapLoader[i][j];
            map[i][j] = Tile(myVec(j * 48 + 24, i * 48 + 24),
                            m_textures.at(mapLoader[i][j]),
                            mapLoader[i][j] == 1 ? "tile" : "test");
        }
    }
    file.close();
}

void TileManager::printMap(sf::RenderTarget& target) {
    for(int i = 0; i < number_of_tiles_per_window_height; i++) {
        for(int j = 0; j < number_of_tiles_per_window_width; j++) {
            map[i][j].draw(target);
        }
    }
}