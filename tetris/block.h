#ifndef BLOCK_H
#define BLOCK_H

#include <vector>
#include <tuple>

class Block {
    private:
        std::vector<std::pair<int, int>> cells;

    public:
        Block();

        void shift(int rows, int columns);
        void rotateCCW();
        void rotateCW();
};


#endif
