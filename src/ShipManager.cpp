#include "ShipManager.hpp"

void ShipManager::printShips() {
        for(Ship& ship: ships) {
            cout << ship.getSize() << '\n';
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