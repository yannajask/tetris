#ifndef GAME_H
#define GAME_H

#include "board.h"
#include "block.h"

class Game: public Subject {
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
        Block* createBlock() const;
        bool doesBlockCollide() const;
        void rotateBlock(bool clockwise = true);
        void moveBlockSide(int x);
        void moveBlockDown();
        void dropBlock();
        void placeBlock();

    public:
        Game(int rows, int cols);
        ~Game();

        int getScore() const;
        int getLevel() const;
        int getLines() const;
        virtual char getState(int x, int y) const override;
};

#endif
