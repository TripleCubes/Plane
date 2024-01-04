#ifndef INTPOS2D_H
#define INTPOS2D_H

#include <cstddef>

struct IntPos2d {
    IntPos2d(int x, int y): x(x), y(y) {};
    bool operator == (IntPos2d pos) const { return pos.x == x && pos.y == y; };
    int x = 0;
    int y = 0;
};

struct IntPos2dHash {
    std::size_t operator () (const IntPos2d &pos) const;
};

#endif
