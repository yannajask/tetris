#include "cell.h"

Cell::Cell(): c(' ') {}

void Cell::setCell(char c) { this->c = c; }

char Cell::getCell() const { return this->c; }
