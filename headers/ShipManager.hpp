#ifndef SHIP_MANAGER_HPP_
#define SHIP_MANAGER_HPP_
<<<<<<< HEAD
using namespace std;
#include <iostream>
#include <vector>
=======
>>>>>>> lb2
#include "Ship.hpp"

class ShipManager{
public:
<<<<<<< HEAD
    explicit ShipManager(size_t ship_amount, vector<size_t>& ship_sizes) {
        if (ship_amount != ship_sizes.size()) {
            throw invalid_argument("Ship amount must match amount of ship's sizes");
=======
    explicit ShipManager(size_t ship_amount, std::vector<size_t>& ship_sizes) {
        if (ship_amount != ship_sizes.size()) {
            throw WrongShipAmountException("Ship amount must match amount of ship's sizes");
>>>>>>> lb2
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
<<<<<<< HEAD
        swap(ships, other.ships);
=======
        std::swap(ships, other.ships);
>>>>>>> lb2
    }
    
    ShipManager& operator= (ShipManager&& other) {
        if (this != &other) {
<<<<<<< HEAD
            swap(ships, other.ships);
=======
            std::swap(ships, other.ships);
>>>>>>> lb2
        }
        return *this;
    }

    void printShips();

    Ship* getShip();

    Ship* getShip(Point p);
    
<<<<<<< HEAD
private:
    vector<Ship> ships;
=======
    Ship* getShip(size_t idx);
    
    size_t getShipAmount() const;
private:
    std::vector<Ship> ships;
>>>>>>> lb2
};
#endif