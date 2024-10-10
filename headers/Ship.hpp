#ifndef SHIP_HPP_
#define SHIP_HPP_
#include <iostream>
#include <vector>
using namespace std;

struct Point {
    size_t x;
    size_t y;
};

class Ship {
public:
    enum class Orientation {vertical, horizontal};
    enum class ShipStates {destroyed_ship, damaged_ship, full_ship};
    Ship(size_t size): size(size), isPlaced(false){
        if (size < 1 || size > 4) {
            throw invalid_argument("Ship size must be between 1 and 4.\n");
        }
        segments.resize(size, ShipStates::full_ship);
    }

    size_t getSize();
    
    void changeSize();
    
    void setCoords(Point p);

    Point getCoords();

    Orientation getOrientation();

    void setOrientation(Orientation orientation);

    void changeSegmentState(size_t index);

    bool status();
    
    ShipStates getSegment(Point p);

    ShipStates getSegment(size_t idx);
    
    void printShipHP();
private:
    Point coords;
    size_t size;
    Orientation orientation;
    vector<ShipStates> segments;
    bool isPlaced;
};

#endif