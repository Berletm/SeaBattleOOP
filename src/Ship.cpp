#include "Ship.hpp"

size_t Ship::getSize() {
        return this->size;
    }

void Ship::changeSize() {
        if (this->size != 0) {
            this->size--;
        }
        else {
            cout << "ship is already destroyed\n";
        }
    }

void Ship::setCoords(Point p) {
        this->coords = {p.x, p.y};
        isPlaced = true;
    }

Point Ship::getCoords() {
        return this->coords;
    }

Ship::Orientation Ship::getOrientation() {
        return this->orientation;
    }

void Ship::setOrientation(Orientation orientation) {
        this->orientation = orientation;
    }

void Ship::changeSegmentState(size_t index) {
        switch (segments[index]) {
            case ShipStates::full_ship: {
                segments[index] = ShipStates::damaged_ship;
                break;
            }
            case ShipStates::damaged_ship: {
                segments[index] = ShipStates::destroyed_ship;
                break;
            }
            case ShipStates::destroyed_ship: {
                cout << "Already destroyed this ship segment\n";
                break;
            }
        }
    }

bool Ship::status() {
        return this->isPlaced;
    }

Ship::ShipStates Ship::getSegment(Point p) {
        if (this->orientation == Ship::Orientation::horizontal) {
            return segments[p.x - coords.x];
        }
        return segments[p.y - coords.y];
    }