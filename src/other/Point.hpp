#ifndef POINT_HPP_
#define POINT_HPP_
#include <cstddef>

struct Point {
    size_t x;
    size_t y;
    
    inline Point(): x(0), y(0) {}
    inline Point(size_t x, size_t y): x(x), y(y) {}

    bool operator==(const Point& other) const {
        return x == other.x && y == other.y;
    }

    bool operator!=(const Point& other) const {
        return !(*this == other);
    }
    
    bool operator<(const Point& other) const {
        if (x == other.x) {
            return y < other.y;
        }
        return x < other.x;
    }
};

#endif