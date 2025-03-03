#include "block.h"
#include <algorithm>
#include <climits>

Block::Block(std::vector<std::pair<int, int>> coordinates): coordinates(coordinates) {}

void Block::setCoordinates(std::vector<std::pair<int, int>> coordinates) { this->coordinates = coordinates; }

std::vector<std::pair<int, int>> Block::getCoordinates() const { 
    std::vector<std::pair<int, int>> position;
    for (auto [x, y]: coordinates) {
        position.push_back({x + offset.first, y + offset.second});
    }
    return position;
}

void Block::shift(int x, int y) {
    offset.first += x;
    offset.second += y;
}


// to do: might be better to implement SSR for rotations
void Block::rotate(bool clockwise) {
    std::vector<std::pair<int, int>> rotatedCoordinates;
    // if clockwise: (x, y) -> (-y, x)
    //         else: (x, y) -> (y, -x)
    int ri = clockwise? 1 : -1;

    int oldMinX = INT_MAX;
    int oldMinY = INT_MAX;
    int newMinX = INT_MAX;
    int newMinY = INT_MAX;

    for (auto [x, y]: coordinates) {
        if (x < oldMinX) oldMinX = x;
        if (y < oldMinY) oldMinY = y;

        int newX = -y * ri;
        int newY = x * ri;
        rotatedCoordinates.push_back({newX, newY});

        if (newX < newMinX) newMinX = newX;
        if (newY < newMinY) newMinY = newY;
    }

    std::pair<int, int> rotation_offset = {newMinX - oldMinX, newMinY - oldMinY};

    for (auto &[x, y]: rotatedCoordinates) {
        x -= rotation_offset.first;
        y -= rotation_offset.second;
    }

    this->coordinates = rotatedCoordinates;
}

IBlock::IBlock(): Block({{0, 1}, {1, 1}, {2, 1}, {3, 1}}) {}

JBlock::JBlock(): Block({{0, 0}, {0, 1}, {1, 1}, {2, 1}}) {}

LBlock::LBlock(): Block({{0, 1}, {1, 1}, {2, 1}, {2, 0}}) {}

OBlock::OBlock(): Block({{1, 0}, {2, 0}, {1, 1}, {2, 1}}) {}

SBlock::SBlock(): Block({{0, 1}, {1, 0}, {1, 1}, {2, 0}}) {}

TBlock::TBlock(): Block({{0, 1}, {1, 0}, {1, 1}, {2, 1}}) {}

ZBlock::ZBlock(): Block({{0, 0}, {1, 0}, {1, 1}, {2, 1}}) {}

char IBlock::getType() const { return 'I'; }

char JBlock::getType() const { return 'J'; }

char LBlock::getType() const { return 'L'; }

char OBlock::getType() const { return 'O'; }

char SBlock::getType() const { return 'S'; }

char TBlock::getType() const { return 'T'; }

char ZBlock::getType() const { return 'Z'; }
