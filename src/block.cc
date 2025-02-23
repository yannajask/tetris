#include "block.h"
#include <algorithm>
#include <climits>

Block::Block(std::vector<std::pair<int, int>> coordinates): coordinates(coordinates) {}

void Block::setCoordinates(std::vector<std::pair<int, int>> coordinates) { this->coordinates = coordinates; }

std::vector<std::pair<int, int>> Block::getCoordinates() const { 
    std::vector<std::pair<int, int>> position;
    for (auto [px, py]: coordinates) {
        position.push_back({px += offset.first, py += offset.second});
    }
    return position;
}

void Block::shift(int x, int y) {
    offset.first += x;
    offset.second += y;
}

void Block::rotate(bool clockwise) {
    std::vector<std::pair<int, int>> rotated_coordinates;
    // if clockwise: (x, y) -> (-y, x)
    //         else: (x, y) -> (y, -x)
    int ri = clockwise? 1 : -1;

    int old_min_x = INT_MAX;
    int old_max_y = INT_MIN;
    int new_min_x = INT_MAX;
    int new_max_y = INT_MIN;

    for (auto [px, py]: coordinates) {
        if (px < old_min_x) old_min_x = px;
        if (py > old_max_y) old_max_y = py;
        if (-py * ri < new_min_x) new_min_x = -py * ri;
        if (px * ri > new_max_y) new_max_y = px * ri;
        rotated_coordinates.push_back({-py * ri, px * ri});
    }

    std::pair<int, int> rotation_offset = {new_min_x - old_min_x, new_max_y - old_max_y};

    for (auto &[px, py]: rotated_coordinates) {
        px -= rotation_offset.first;
        py -= rotation_offset.second;
    }

    // check for collisions i'd assume
    coordinates = rotated_coordinates;
}

IBlock::IBlock(): Block({{0, 0}, {1, 0}, {2, 0}, {3, 0}}) {}

JBlock::JBlock(): Block({{0, 0}, {0, 1}, {1, 1}, {2, 1}}) {}

LBlock::LBlock(): Block({{0, 1}, {1, 1}, {2, 1}, {2, 0}}) {}

OBlock::OBlock(): Block({{1, 0}, {2, 0}, {1, 1}, {2, 1}}) {}

SBlock::SBlock(): Block({{0, 1}, {1, 0}, {1, 1}, {0, 1}}) {}

TBlock::TBlock(): Block({{0, 1}, {1, 0}, {1, 1}, {2, 1}}) {}

ZBlock::ZBlock(): Block({{0, 0}, {1, 0}, {1, 1}, {2, 1}}) {}

char IBlock::getType() const { return 'I'; }

char JBlock::getType() const { return 'J'; }

char LBlock::getType() const { return 'L'; }

char OBlock::getType() const { return 'O'; }

char SBlock::getType() const { return 'S'; }

char TBlock::getType() const { return 'T'; }

char ZBlock::getType() const { return 'Z'; }
