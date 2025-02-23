#include "board.h"
#include "block.h"
#include "observer.h"
#include "subject.h"
#include "constants.h"
#include "textdisplay.h"


int main(int argc, const char *argv[]) {
    Board *game = new Board{BOARD_HEIGHT, BOARD_WIDTH};
    TextDisplay *graphics = new TextDisplay{game, BOARD_HEIGHT, BOARD_WIDTH};
    delete graphics;
    delete game;
    return 0;
}