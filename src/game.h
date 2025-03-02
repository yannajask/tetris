#ifndef GAME_H
#define GAME_H

#include "board.h"
#include "block.h"
#include "display.h"
#include <ostream>
#include <random>

class Display;

class Game {
    private:
        Board *gameBoard;
        Display *graphics;

        mutable std::random_device rd;
        mutable std::mt19937 gen;
        mutable std::uniform_int_distribution<> dis;

        int framerate = 48;
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

        void rotateBlock(bool clockwise = true);
        void moveBlockSide(int x);
        void moveBlockDown();
        void dropBlock();
        void placeBlock();

        void handleInput(bool &running);

    public:
        Game(int rows, int cols);
        ~Game();

        void play();
        
        friend std::ostream &operator<<(std::ostream &out, const Game &game);
        Block *getNextBlock() const;
        int getScore() const;
        int getLevel() const;
        int getLines() const;
};

#endif
