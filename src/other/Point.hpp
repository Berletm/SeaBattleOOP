#ifndef POINT_HPP_
#define POINT_HPP_
#include <cstddef>

struct Point {
    size_t x;
    size_t y;
    inline Point(): x(0), y(0) {}
    inline Point(size_t x, size_t y): x(x), y(y) {}
};

#endif