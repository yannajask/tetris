#ifndef GAME_H
#define GAME_H

#include "board.h"
#include "block.h"
#include <ostream>

class Game {
    private:
        Board *gameBoard;
        const int seed;

        int score = 0;
        int level = 0;
        int levelLines = 0;
        int totalLines = 0;
        void calculateScore();
        void reset();

        Block *currentBlock;
        Block *nextBlock;
        Block *createBlock() const;
        bool doesBlockCollide() const;

    public:
        Game(int rows, int cols);
        ~Game();

        // move these to public for testing
        void rotateBlock(bool clockwise = true);
        void moveBlockSide(int x);
        void moveBlockDown();
        void dropBlock();
        void placeBlock();
        
        friend std::ostream &operator<<(std::ostream &out, const Game &game);
};

#endif
