#include "block.h"
#include <algorithm>
#include <climits>

Block::Block(std::vector<std::pair<int, int>> coordinates): coordinates(coordinates) {}

void Block::setCoordinates(std::vector<std::pair<int, int>> coordinates) { this->coordinates = coordinates; }

std::vector<std::pair<int, int>> Block::getCoordinates() const { 
    std::vector<std::pair<int, int>> position;
    for (auto [i, j]: coordinates) {
        position.push_back({i + offset.first, j + offset.second});
    }
    return position;
}

void Block::shift(int rows, int cols) {
    offset.first += rows;
    offset.second += cols;
}


// to do: might be better to implement SSR for rotations
void Block::rotate(bool clockwise) {
    std::vector<std::pair<int, int>> rotatedCoordinates;
    // if clockwise: (i, j) -> (j, -i)
    //         else: (i, j) -> (-j, i)
    int ri = clockwise? 1 : -1;

    int oldMinM = INT_MAX, oldMinN = INT_MAX;
    int newMinM = INT_MAX, newMinN = INT_MAX;

    for (auto [i, j]: coordinates) {
        if (i < oldMinM) oldMinM = i;
        if (j < oldMinN) oldMinN = j;

        int newI = j * ri;
        int newJ = -i * ri;
        rotatedCoordinates.push_back({newI, newJ});

        if (newI < newMinM) newMinM = newI;
        if (newJ < newMinN) newMinN = newJ;
    }

    std::pair<int, int> rotation_offset = {newMinM - oldMinM, newMinN - oldMinN};

    for (auto &[i, j]: rotatedCoordinates) {
        i -= rotation_offset.first;
        j -= rotation_offset.second;
    }

    this->coordinates = rotatedCoordinates;
}

IBlock::IBlock(): Block({{1, 0}, {1, 1}, {1, 2}, {1, 3}}) {}

JBlock::JBlock(): Block({{0, 0}, {1, 0}, {1, 1}, {1, 2}}) {}

LBlock::LBlock(): Block({{1, 0}, {1, 1}, {1, 2}, {0, 2}}) {}

OBlock::OBlock(): Block({{1, 0}, {0, 2}, {1, 1}, {1, 2}}) {}

SBlock::SBlock(): Block({{1, 0}, {0, 1}, {1, 1}, {0, 2}}) {}

TBlock::TBlock(): Block({{1, 0}, {0, 1}, {1, 1}, {1, 2}}) {}

ZBlock::ZBlock(): Block({{0, 0}, {0, 1}, {1, 1}, {1, 2}}) {}

char IBlock::getType() const { return 'I'; }

char JBlock::getType() const { return 'J'; }

char LBlock::getType() const { return 'L'; }

char OBlock::getType() const { return 'O'; }

char SBlock::getType() const { return 'S'; }

char TBlock::getType() const { return 'T'; }

char ZBlock::getType() const { return 'Z'; }
