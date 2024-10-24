#include "PlayGround.hpp"

bool PlayGround::isInPlayGround(Point p) const {
    return p.x < this->size && p.y < this->size;
}

bool PlayGround::checkCollision(Point p, Ship& ship, Ship::Orientation orientation) {
    for (size_t l = 0; l < ship.getSize(); ++l) {
        size_t currentX = (orientation == Ship::Orientation::horizontal) ? p.x + l : p.x;
        size_t currentY = (orientation == Ship::Orientation::horizontal) ? p.y : p.y + l;

<<<<<<< HEAD
        if (!isInPlayGround({currentX, currentY}) || (cells[currentX][currentY].GetState() == CellStates::ship)) {
=======
        if (!isInPlayGround({currentX, currentY}) || (cells[currentX][currentY].GetShip() != nullptr)) {
>>>>>>> lb2
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
<<<<<<< HEAD
                    (cells[neighborX][neighborY].GetState() == CellStates::ship)) {
=======
                    (cells[neighborX][neighborY].GetShip() != nullptr)) {
>>>>>>> lb2
                    return true;
                }
            }
        }
    }
    return false;
}

void PlayGround::PlaceShip(Ship* ship, Point position, Ship::Orientation orientation) {
        if (ship == nullptr) {
<<<<<<< HEAD
            throw invalid_argument("Cannot place null object");
        }

        if (checkCollision(position, *ship, orientation)) {
            throw invalid_argument("Cannot place ship on this coordinates!");
=======
            throw CollisionException("Cannot place null object");
        }

        if (checkCollision(position, *ship, orientation)) {
            throw CollisionException("Cannot place ship on this coordinates!");
>>>>>>> lb2
        }

        if (orientation == Ship::Orientation::horizontal) {
            for(size_t x = position.x; x < position.x + ship->getSize(); ++x) {
                cells[x][position.y].ChangeState(CellStates::unknown, ship, x - position.x);
            }
            ship->setCoords(position);
            ship->setOrientation(orientation);
        }
        else if (orientation == Ship::Orientation::vertical) {
            for(size_t y = position.y; y < position.y + ship->getSize(); ++y) {
                cells[position.x][y].ChangeState(CellStates::unknown, ship, y - position.y);
            }
            ship->setCoords(position);
            ship->setOrientation(orientation);
        }
    }

void PlayGround::DisplayPlayground() {
<<<<<<< HEAD
    cout << "Amount of hits: " << hits_number << " " << "Amount of misses: " << miss_number << "\n";
    cout << "Total accuracy: " << double(hits_number) / double(hits_number + miss_number) << "\n";
    for (size_t y = 0; y < this->size; ++y) {
        for (size_t x = 0; x < this->size; ++x) {
            if (cells[x][y].GetState() == CellStates::unknown) {
                cout << "#" << " ";
            }
            else if (cells[x][y].GetState() == CellStates::empty) {
                cout << "*" << " ";
            }
            else if (cells[x][y].GetState() == CellStates::ship) {
                cout << size_t(cells[x][y].GetSegmentHP()) << " ";
            }
        }
        cout << '\n';
    }
}

void PlayGround::Attack(Point p) {
    switch (this->cells[p.x][p.y].GetState()) {
        case ship: {
            cells[p.x][p.y].ChangeSegmentState();
            cout << "Hit!\n";
            hits_number += 1;
            break;
        }
        case empty: {
            cout << "Miss!\n";
            miss_number += 1;
            break;
        }
        case unknown: {
            if (cells[p.x][p.y].GetShip()) {
                cout << "Hit!\n";
                hits_number += 1;
                this->cells[p.x][p.y].ChangeState(CellStates::ship);
                cells[p.x][p.y].ChangeSegmentState();
            }
            else {
                cout << "Miss!\n";
=======
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

void PlayGround::Attack(Point p, AbilityManager& AbilityManager) {
    if (!isInPlayGround(p)) {
        throw OutOfFieldAttackException("Out of field attack is inaccessible");
    }

    switch (this->cells[p.x][p.y].GetState()) {
        case CellStates::ship: {
            if (this->double_damage_buff) {
                cells[p.x][p.y].ChangeSegmentState();
                cells[p.x][p.y].ChangeSegmentState();
                std::cout << "DD Hit!\n";
                hits_number += 2;
                this->double_damage_buff = false;
                break;
            }
            else {
                cells[p.x][p.y].ChangeSegmentState();
                std::cout << "Hit!\n";
                hits_number += 1;
                break;
            }
        }
        case CellStates::empty: {
            if (this->double_damage_buff) {
                this->double_damage_buff = false;
            }
            std::cout << "Miss!\n";
            miss_number += 1;
            break;
        }
        case CellStates::unknown: {
            Ship* ship = cells[p.x][p.y].GetShip();
            if (ship) {
                if (this->double_damage_buff) {
                    std::cout << "DD HIT!\n";
                    hits_number += 2;
                    if (ship->getOrientation() == Ship::Orientation::horizontal) {
                        this->cells[p.x][p.y].ChangeState(CellStates::ship, ship, p.x - ship->getCoords().x);
                    }
                    else {
                        this->cells[p.x][p.y].ChangeState(CellStates::ship, ship, p.y - ship->getCoords().y);

                    }
                    this->cells[p.x][p.y].ChangeSegmentState();
                    this->cells[p.x][p.y].ChangeSegmentState();
                    this->double_damage_buff = false;
                }
                else { 
                    std::cout << "Hit!\n";
                    hits_number += 1;
                    if (ship->getOrientation() == Ship::Orientation::horizontal) {
                        this->cells[p.x][p.y].ChangeState(CellStates::ship, ship, p.x - ship->getCoords().x);
                    }
                    else {
                        this->cells[p.x][p.y].ChangeState(CellStates::ship, ship, p.y - ship->getCoords().y);

                    }
                    this->cells[p.x][p.y].ChangeSegmentState();
                }
            }
            else {
                if (this->double_damage_buff) {
                    this->double_damage_buff = false;
                }
                std::cout << "Miss!\n";
>>>>>>> lb2
                miss_number += 1;
                this->cells[p.x][p.y].ChangeState(CellStates::empty);
            }
            break;
        }
    }
<<<<<<< HEAD
=======
}

void PlayGround::getDoubleDamageBuff() {
    this->double_damage_buff = true;
}

CellStates PlayGround::getCellState(Point p) const{
    if (cells[p.x][p.y].GetShip()) {
        return CellStates::ship;
    }
    return CellStates::unknown;
}

inline size_t PlayGround::getFieldSize() const{
    return this->size;
}

void PlayGround::Cell::ChangeState(CellStates new_state, Ship* ship_ptr, size_t segment_idx) {
    this->state = new_state;
    if (ship_ptr) {
        this->ship = ship_ptr;
        this->segment_idx = segment_idx;
    }
}

bool PlayGround::isUnderBuff() {
    return this->double_damage_buff;
}

void PlayGround::dispellBuff() {
    this->double_damage_buff = false;
>>>>>>> lb2
}