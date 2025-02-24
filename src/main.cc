
#include "game.h"
#include "block.h"
#include "constants.h"
#include <iostream>

int main(int argc, const char *argv[]) {
    Game tetris(BOARD_HEIGHT, BOARD_WIDTH);
    std::cout << tetris;
    std::cout << "---" << std::endl;
    tetris.dropBlock();
    std::cout << tetris;
    std::cout << "---" << std::endl;
    tetris.moveBlockDown();
    std::cout << tetris;
    std::cout << "---" << std::endl;
    return 0;
}