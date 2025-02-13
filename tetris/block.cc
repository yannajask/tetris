#include "block.h"

#include <map>

void Block::shift(int rows, int columns) {
    for (auto &[px, py]: cells) {
        ++px; ++py;
    }
}

void Block::rotateCCW() {

}

void Block::rotateCW() {

}