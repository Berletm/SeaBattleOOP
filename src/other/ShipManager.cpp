#include "ShipManager.hpp"

void ShipManager::printShips() {
    for(Ship& ship: ships) {
        ship.printShipHP();
        std::cout << "\n";
    }
}

Ship* ShipManager::getShip() {
    for (Ship& ship: ships) {
        if (!ship.status()) {
            return &ship;
        }
    }
    return nullptr;
}

Ship* ShipManager::getShip(Point p) {
    for (Ship& ship: ships) {
        Point ship_coords = ship.getCoords();
        if (ship.getOrientation() == Ship::Orientation::horizontal) {
            if (p.y == ship_coords.y && p.x >= ship_coords.x && p.x < (ship_coords.x + ship.getSize())) {
                return &ship;
            }
        }
        else {
            if (p.x == ship_coords.x && p.y >= ship_coords.y && p.y < (ship_coords.y + ship.getSize())) {
                return &ship;
            }
        }
    }
    return nullptr;
}


size_t ShipManager::getShipAmount() const {
    return ships.size();
}

Ship* ShipManager::getShip(size_t idx) {
    return &ships[idx];
}

size_t ShipManager::getCurrentShipAmount() const{
    size_t counter = 0;
    for (const auto& ship: ships) {
        if (!ship.isDestroyed()) {
            counter++;
        }
    }
    return counter;
}

void ShipManager::addShip(Ship& ship) {
    this->ships.push_back(ship);
}

json ShipManager::to_json() const {
    json save_file;
    json ships_array = json::array();

    for (const auto& ship: ships) {
        ships_array.push_back(ship.to_json());
    }

    save_file["ships"] = ships_array;
    return save_file;
}

std::vector<size_t> ShipManager::getShipSizes() {
    std::vector<size_t> res;
    for (const auto& ship: ships) {
        res.push_back(ship.getSize());
    }
    return res;
}