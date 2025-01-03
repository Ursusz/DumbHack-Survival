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
    m_textures.insert({1, "assets/Tree.png"});
    m_textures.insert({2, "assets/wall.png"});
    m_textures.insert({3, "assets/computer.png"});
    m_textures.insert({4, "assets/upper_wall.png"});
    m_textures.insert({5, "assets/left_wall.png"});
    m_textures.insert({6, "assets/wall_corner_left.png"});
    m_textures.insert({7, "assets/right_wall.png"});
    m_textures.insert({8, "assets/wall_corner_right.png"});

    std::ifstream file(mapFile);
    if (!file.is_open()) {
        throw fileNotFound(mapFile);
    }

    for(int i = 0; i < number_of_tiles_per_window_height; i++) {
        for(int j = 0; j < number_of_tiles_per_window_width; j++) {
            file >> mapLoader[i][j];
            if(mapLoader[i][j] == 3) {
                objectComputers.push_back(Computer(myVec(j * 48 + 24, i * 48 + 24)));
            }
            ///Every tile is 48x48 so I am placing them at 48 pixels between each of them
            ///but i want them to be placed where their origin is located (their center -> 48/2 = 24) so i am adding 24 more pixels
            std::string tileType;
            switch(mapLoader[i][j]) {
                case 0 : tileType = "floor";
                    break;
                case 1: tileType = "tree";
                    break;
                case 2: tileType = "wall";
                    break;
                case 3: tileType = "computer";
                    break;
                case 4: tileType = "wall";
                    break;
                case 5 : tileType = "wall";
                    break;
                case 6 : tileType = "wall";
                    break;
                case 7 : tileType = "wall";
                    break;
                case 8 : tileType = "wall";
                    break;
                default: tileType = "nothing";
                    break;
            }
            map[i][j] = Tile(myVec(j * 48 + 24, i * 48 + 24),
                            m_textures.at(mapLoader[i][j]),
                            tileType,
                            false,
                            tileType != "floor",
                            false,
                            1);
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