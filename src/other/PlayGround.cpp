#include "PlayGround.hpp"

bool PlayGround::isInPlayGround(Point p) const {
    return p.x < this->size && p.y < this->size;
}

bool PlayGround::checkCollision(Point p, Ship& ship, Ship::Orientation orientation) {
    for (size_t l = 0; l < ship.getSize(); ++l) {
        size_t currentX = (orientation == Ship::Orientation::horizontal) ? p.x + l : p.x;
        size_t currentY = (orientation == Ship::Orientation::horizontal) ? p.y : p.y + l;

        if (!isInPlayGround({currentX, currentY}) || (cells[currentX][currentY].GetShip() != nullptr)) {
            return true;
        }
    }

    for (size_t l = 0; l < ship.getSize(); ++l) {
        size_t currentX = (orientation == Ship::Orientation::horizontal) ? p.x + l : p.x;
        size_t currentY = (orientation == Ship::Orientation::horizontal) ? p.y : p.y + l;

        for (int dx = -1; dx <= 1; ++dx) {
            for (int dy = -1; dy <= 1; ++dy) {
                if (dx == 0 && dy == 0) continue;

                size_t neighborX = currentX + dx;
                size_t neighborY = currentY + dy;

                if (isInPlayGround({neighborX, neighborY}) && 
                    (cells[neighborX][neighborY].GetShip() != nullptr)) {
                    return true;
                }
            }
        }
    }
    return false;
}

void PlayGround::PlaceShip(Ship* ship, Point position, Ship::Orientation orientation) {
        if (ship == nullptr) {
            throw CollisionException("Cannot place null object");
        }

        if (checkCollision(position, *ship, orientation)) {
            throw CollisionException("Cannot place ship on this coordinates!");
        }

        if (orientation == Ship::Orientation::horizontal) {
            for(size_t x = position.x; x < position.x + ship->getSize(); ++x) {
                if (ship->isDamaged(x - position.x)) {
                    cells[x][position.y].ChangeState(CellStates::ship, ship, x - position.x);

                }
                else {
                    cells[x][position.y].ChangeState(CellStates::unknown, ship, x - position.x);
                }
            }
            ship->setCoords(position);
            ship->setOrientation(orientation);
        }
        else if (orientation == Ship::Orientation::vertical) {
            for(size_t y = position.y; y < position.y + ship->getSize(); ++y) {
                if (ship->isDamaged(y - position.y)) {
                    cells[position.x][y].ChangeState(CellStates::ship, ship, y - position.y);
                }
                else  {
                    cells[position.x][y].ChangeState(CellStates::unknown, ship, y - position.y);
                }
            }
            ship->setCoords(position);
            ship->setOrientation(orientation);
        }
    }

void PlayGround::DisplayPlayground() {
    for (size_t y = 0; y < this->size; ++y) {
        for (size_t x = 0; x < this->size; ++x) {
            if (cells[x][y].GetState() == CellStates::unknown) {
                std::cout << "#" << " ";
            }
            else if (cells[x][y].GetState() == CellStates::empty) {
                std::cout << "*" << " ";
            }
            else if (cells[x][y].GetState() == CellStates::ship) {
                std::cout << size_t(cells[x][y].GetSegmentHP()) << " ";
            }
        }
        std::cout << '\n';
    }
}

void PlayGround::DisplayPlaygroundWithOutFogOfWar() {
    for (size_t y = 0; y < this->size; ++y) {
        for (size_t x = 0; x < this->size; ++x) {
            if (cells[x][y].GetState() == CellStates::unknown && !cells[x][y].GetShip()) {
                std::cout << "#" << " ";
            }
            else if (cells[x][y].GetState() == CellStates::empty) {
                std::cout << "*" << " ";
            }
            else if (cells[x][y].GetShip()) {
                std::cout << size_t(cells[x][y].GetSegmentHP()) << " ";
            }
        }
        std::cout << '\n';
    }
}

bool PlayGround::Attack(Point p) {
    if (!isInPlayGround(p)) {
        throw OutOfFieldAttackException("Out of field attack is inaccessible");
    }

    switch (this->cells[p.x][p.y].GetState()) {
        case CellStates::ship: {
            cells[p.x][p.y].ChangeSegmentState();
            return true;
        }
        case CellStates::empty: {
            return false;
        }
        case CellStates::unknown: {
            Ship* ship = cells[p.x][p.y].GetShip();
            if (ship) {
                if (ship->getOrientation() == Ship::Orientation::horizontal) {
                    this->cells[p.x][p.y].ChangeState(CellStates::ship, ship, p.x - ship->getCoords().x);
                }
                else {
                    this->cells[p.x][p.y].ChangeState(CellStates::ship, ship, p.y - ship->getCoords().y);

                }
                this->cells[p.x][p.y].ChangeSegmentState();
                return true;
            }
            else {
                this->cells[p.x][p.y].ChangeState(CellStates::empty);
                return false;
            }
        }
    }
}

CellStates PlayGround::getCellState(Point p) const{
    if (cells[p.x][p.y].GetShip()) {
        return CellStates::ship;
    }
    return CellStates::unknown;
}

size_t PlayGround::getFieldSize() const{
    return this->size;
}

void PlayGround::Cell::ChangeState(CellStates new_state, Ship* ship_ptr, size_t segment_idx) {
    this->state = new_state;
    if (ship_ptr) {
        this->ship = ship_ptr;
        this->segment_idx = segment_idx;
    }
}