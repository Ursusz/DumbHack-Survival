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
    number_of_tiles_per_window_width = rhs.number_of_tiles_per_window_width;
    number_of_tiles_per_window_height = rhs.number_of_tiles_per_window_height;
    for (int i = 0; i < number_of_tiles_per_window_height; ++i) {
         for (int j = 0; j < number_of_tiles_per_window_width; ++j) {
             mapLoader[i][j] = rhs.mapLoader[i][j];
             map[i][j] = rhs.map[i][j];
         }
    }
    m_textures = rhs.m_textures;
    return *this;
}

Tile& TileManager::getTile(size_t i, size_t j) {
    return map[i][j];
}

void TileManager::loadMap(const std::string &mapFile, std::vector<Computer>& objectComputers) {
    m_textures.insert({0, "assets/woodenPlank.png"});
    m_textures.insert({1, "assets/table.png"});
    m_textures.insert({2, "assets/Tree.png"});
    m_textures.insert({3, "assets/wall.png"});
    m_textures.insert({4, "assets/computer.png"});
    m_textures.insert({5, "assets/upper_wall.png"});
    m_textures.insert({6, "assets/left_wall.png"});
    m_textures.insert({7, "assets/wall_corner_left.png"});
    m_textures.insert({8, "assets/right_wall.png"});
    m_textures.insert({9, "assets/wall_corner_right.png"});
    std::ifstream file(mapFile);
    if (!file.is_open()) {
        std::cerr << "Could not open file " << mapFile << std::endl;
    }

    for(int i = 0; i < number_of_tiles_per_window_height; i++) {
        for(int j = 0; j < number_of_tiles_per_window_width; j++) {
            file >> mapLoader[i][j];
            if(mapLoader[i][j] == 4) {
                objectComputers.push_back(Computer(myVec(j * 48 + 24, i * 48 + 24)));
            }
            ///Every tile is 48x48 so I am placing them at 48 pixels between each of them
            ///but i want them to be placed where their origin is located (their center -> 48/2 = 24) so i am adding 24 more pixels
            map[i][j] = Tile(myVec(j * 48 + 24, i * 48 + 24),
                            m_textures.at(mapLoader[i][j]),
                            mapLoader[i][j] != 0 ? "tile" : "test");
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