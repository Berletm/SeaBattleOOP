#ifndef SHIP_MANAGER_HPP_
#define SHIP_MANAGER_HPP_
using namespace std;
#include <iostream>
#include <vector>
#include "Ship.hpp"

class ShipManager{
public:
    explicit ShipManager(size_t ship_amount, vector<size_t>& ship_sizes) {
        if (ship_amount != ship_sizes.size()) {
            throw invalid_argument("Ship amount must match amount of ship's sizes");
        }
        for(size_t size: ship_sizes) {
            ships.emplace_back(Ship(size));
        }
    }

    //copy constructor
    ShipManager(const ShipManager& other): ships(other.ships) {
    }

    ShipManager& operator= (const ShipManager& other) {
        if (this != &other) {
            ships = other.ships;
        }
        return *this;
    }

    //move constructor
    ShipManager(ShipManager&& other) {
        swap(ships, other.ships);
    }
    
    ShipManager& operator= (ShipManager&& other) {
        if (this != &other) {
            swap(ships, other.ships);
        }
        return *this;
    }

    void printShips();

    Ship* getShip();

    Ship* getShip(Point p);
    
private:
    vector<Ship> ships;
};
#endif