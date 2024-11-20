#ifndef SHIP_MANAGER_HPP_
#define SHIP_MANAGER_HPP_

#include "Ship.hpp"
#include <algorithm>
#include <nlohmann/json.hpp>

using json = nlohmann::json;

class ShipManager{
public:
    ShipManager() {}

    explicit ShipManager(size_t ship_amount, std::vector<size_t> ship_sizes) {
        if (ship_amount != ship_sizes.size()) {
            std::cout << ship_amount << ship_sizes.size() << std::endl;
            throw WrongShipAmountException("Ship amount must match amount of ship's sizes");
        }
        sort(ship_sizes.begin(), ship_sizes.end());
        for(size_t size: ship_sizes) {
            ships.emplace_back(Ship(size));
        }
        std::reverse(ships.begin(), ships.end());
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
        std::swap(ships, other.ships);
    }
    
    ShipManager& operator=(ShipManager&& other) {
        if (this != &other) {
            std::swap(ships, other.ships);
        }
        return *this;
    }

    void printShips();

    Ship* getShip();

    Ship* getShip(Point p);
    
    Ship* getShip(size_t idx);
    
    size_t getShipAmount() const;

    size_t getCurrentShipAmount() const;

    void addShip(Ship& ship);

    json to_json() const;

    std::vector<size_t> getShipSizes();
private:
    std::vector<Ship> ships;
};
#endif