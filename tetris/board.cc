#include "board.h"
#include <iostream>

Board::Board(int rows, int cols): rows(rows), cols(cols), cells(rows, std::vector<std::unique_ptr<Cell>> (cols)) {}

std::vector<std::vector<std::unique_ptr<Cell>>> &Board::grid() { return cells; }

//void Board::render() { notifyObservers(); }
void Board::render() {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            std::cout << getState(i, j);
        }

        std::cout << "\n";
    }
}

char Board::getState(int x, int y) const { return cells[x][y]->getCell(); }
