#include "Ship.hpp"

size_t Ship::getSize() const{
    return this->size;
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
            std::cout << "Already destroyed this ship segment\n";
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

Ship::ShipStates Ship::getSegment(size_t idx) {
    if (this->orientation == Ship::Orientation::horizontal) {
        return segments[idx];
    }
    return segments[idx];
}

void Ship::printShipHP() {
    for(const auto& segment: segments) {
        std::cout << int(segment) << " ";
    }
}

bool Ship::isDestroyed() const {
    for (const auto& segment: segments) {
        if (segment != ShipStates::destroyed_ship) {
            return false;
        }
    }
    return true;
}

bool Ship::isDamaged(size_t idx) const {
    if (segments[idx] != ShipStates::full_ship) {
        return true;
    }
    return false;
}