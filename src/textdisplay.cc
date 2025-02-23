#include "textdisplay.h"
#include "board.h"
#include "subject.h"
#include <iostream>

TextDisplay::TextDisplay(Board *board, int rows, int cols): board(board), rows(rows), cols(cols) {
    board->attach(this);
}

TextDisplay::~TextDisplay() { board->detach(this); }

void TextDisplay::notify() { 
    std::cout << " _____ ___ _____ ___ _   __\n" 
              << "|_   _| __|_   _| _ \ |/' _/\n"
              << "  | | | _|  | | | v / |`._`.\n"
              << "  |_| |___| |_| |_|_\_||___/\n";

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            std::cout << board->getState(i, j);
        }
        std::cout << "\n";
    }
}
