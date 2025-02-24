#include "game.h"
#include <algorithm>
#include <tuple>

Game::Game(int rows, int cols): gameBoard(new Board{rows, cols}), seed(1738) {
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
        }
    }
}

void Game::reset() {
    gameBoard->clear();
    int score = 0;
    int level = 0;
    int levelLines = 0;
    int totalLines = 0;
    currentBlock = createBlock();
    nextBlock = createBlock();
}

Block* Game::createBlock() const {
    int x = rand() % 7;
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
        case 6:
            return new ZBlock();
    }
}

bool Game::doesBlockCollide() const {
    for (auto [px, py]: currentBlock->getCoordinates()) {
        if (!(gameBoard->isInside(px, py))) return false;
        if (gameBoard->getCell(px, py) != ' ') return false;
    }
    return true;
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
    currentBlock = nextBlock;
    if (doesBlockCollide()) reset();
    nextBlock = createBlock();
    calculateScore();
}

std::ostream &operator<<(std::ostream &out, const Game &game) {
    auto currentCoordinates = game.currentBlock->getCoordinates();
    for (int row = 0; row < game.gameBoard->getHeight(); ++row) {
        for (int col = 0; col < game.gameBoard->getWidth(); ++col) {
            if (std::find(currentCoordinates.begin(), currentCoordinates.end(), std::make_pair(row, col)) != currentCoordinates.end()) {
                out << game.currentBlock->getType();
            } else {
                out << game.gameBoard->getCell(row, col);
            }
        }
        out << '\n';
    }
    return out;
}
