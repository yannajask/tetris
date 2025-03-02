#include "game.h"
#include <algorithm>
#include <tuple>
#include <chrono>
#include <thread>

Game::Game(int rows, int cols): gameBoard(new Board{rows + 2, cols}), gen(rd()), dis(0, 6) {
    currentBlock = createBlock();
    nextBlock = createBlock();
}

Game::~Game() {
    delete currentBlock;
    delete nextBlock;
    delete gameBoard;
}

void Game::calculateScore() {
    int rowsCleared = gameBoard->clearRows();
    if (rowsCleared > 0) {
        int multiplier = 0;
        switch (rowsCleared) {
            case 1:
                multiplier = 40;
                break;
            case 2:
                multiplier = 100;
                break;
            case 3:
                multiplier = 300;
                break;
            case 4:
                multiplier = 1200;
                break;
        }

        score += multiplier * (level + 1);
        levelLines += rowsCleared;
        totalLines += rowsCleared;

        if (levelLines >= level * 10) {
            levelLines -= level * 10;
            ++level;

            // for levels 0-9, decrease frames per cell by 5
            if (level < 9) {
                framerate -= 5;
            // decrement frames by 1 for levels 11, 13, 16, 19, 29
            } else if (level == 10 || level == 13 || level == 16 || level == 19 || level == 29) {
                framerate -= 1;
            }
        }
    }
}

void Game::reset() {
    gameBoard->clear();
    score = 0;
    level = 0;
    levelLines = 0;
    totalLines = 0;
    delete currentBlock;
    delete nextBlock;
    currentBlock = createBlock();
    nextBlock = createBlock();
}

Block* Game::createBlock() const {
    int x = dis(gen);
    switch (x) {
        case 0:
            return new IBlock();
        case 1:
            return new JBlock();
        case 2:
            return new LBlock();
        case 3:
            return new OBlock();
        case 4:
            return new SBlock();
        case 5:
            return new TBlock();
        default:
            return new ZBlock();
    }
}

bool Game::doesBlockCollide() const {
    for (auto [x, y]: currentBlock->getCoordinates()) {
        if (!(gameBoard->isInside(x, y)) || gameBoard->getCell(x, y) != ' ') return true;
    }
    return false;
}

void Game::rotateBlock(bool clockwise) {
    currentBlock->rotate(clockwise);
    if (doesBlockCollide()) {
        currentBlock->rotate(!clockwise);
    }
}

void Game::moveBlockSide(int x) {
    currentBlock->shift(x, 0);
    if (doesBlockCollide()) {
        currentBlock->shift(-x, 0);
    }
}

void Game::moveBlockDown() {
    currentBlock->shift(0, 1);
    if (doesBlockCollide()) {
        currentBlock->shift(0, -1);
        placeBlock();
    }
}

void Game::dropBlock() {
    while (!doesBlockCollide()) {
        currentBlock->shift(0, 1);
    }
    currentBlock->shift(0, -1);
    placeBlock();
}

void Game::placeBlock() {
    for (auto [px, py]: currentBlock->getCoordinates()) {
        gameBoard->setCell(px, py, currentBlock->getType());
    }
    delete currentBlock;
    currentBlock = nextBlock;
    if (doesBlockCollide()) reset();
    nextBlock = createBlock();
    calculateScore();
}

void Game::play() {
    using clock = std::chrono::steady_clock;
    using fps_60 = std::chrono::duration<int, std::ratio<1, 60>>;

    bool running = true;
    auto moveInterval = fps_60(1) * framerate;
    auto lastMoveTime = clock::now();

    while (running) {
        auto start = clock::now();

        // handle input

        auto elapsedTime = start - lastMoveTime;
        if (elapsedTime >= moveInterval) {
            moveBlockDown();
            lastMoveTime = start;
        }

        // render board

        auto end = clock::now();
        if (end - start < fps_60(1)) {
            std::this_thread::sleep_until(start + fps_60(1));
        }
    }
}

std::ostream &operator<<(std::ostream &out, const Game &game) {
    int rows = game.gameBoard->getHeight();
    int cols = game.gameBoard->getWidth();
    auto currentCoordinates = game.currentBlock->getCoordinates();

    // first two rows are for blocks to spawn and should not be printed
    for (int j = 2; j < rows; ++j) {
        for (int i = 0; i < cols; ++i) {
            if (std::find(currentCoordinates.begin(), currentCoordinates.end(), std::make_pair(i, j)) != currentCoordinates.end()) {
                out << game.currentBlock->getType();
            } else {
                out << game.gameBoard->getCell(i, j);
            }
        }
        out << '\n';
    }

    return out;
}
