#include <Helper.h>
#include "env_fixes.h"
#include "../header/GameEngine.h"

int main() {
    init_threads();
    Helper helper;
    helper.help();
    GameEngine game("D:/DumbHack-Survival/Init/setup.txt");
    game.run();
    return 0;
}
