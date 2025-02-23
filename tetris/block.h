#ifndef BLOCK_H
#define BLOCK_H

#include "cell.h"
#include <memory>
#include <vector>

class Block {
    private:
        std::vector<std::pair<int, int>> coordinates;
        std::pair<int, int> offset;

    public:
        explicit Block(std::vector<std::pair<int, int>> coordinates);
        virtual ~Block() = default;

        virtual char getType() const = 0;
        void setCoordinates(std::vector<std::pair<int, int>> coordinates);
        std::vector<std::pair<int, int>> getCoordinates() const;

        void shift(int x, int y);
        void rotate(bool clockwise = true);
};

class IBlock: public Block {
    public:
        explicit IBlock();
        virtual char getType() const override;

};

class JBlock: public Block {
    public:
        explicit JBlock();
        virtual char getType() const override;
};

class LBlock: public Block {
    public:
        explicit LBlock();
        virtual char getType() const override;

};

class OBlock: public Block {
    public:
        explicit OBlock();
        virtual char getType() const override;

};

class SBlock: public Block {
    public:
        explicit SBlock();
        virtual char getType() const override;

};

class TBlock: public Block {
    public:
        explicit TBlock();
        virtual char getType() const override;

};

class ZBlock: public Block {
    public:
        explicit ZBlock();
        virtual char getType() const override;

};

#endif
