#ifndef CELL_H
#define CELL_H

class Cell {
    char c;

    public:
        Cell();
        virtual ~Cell() = default;

        void setCell(char c);
        char getCell() const;
};

#endif
