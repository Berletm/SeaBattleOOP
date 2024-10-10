#include "PlayGround.hpp"

bool PlayGround::isInPlayGround(Point p) const {
        return p.x < this->size && p.y < this->size;
    }

bool PlayGround::checkCollision(Point p, Ship& ship, Ship::Orientation orientation) {
    for (size_t l = 0; l < ship.getSize(); ++l) {
        size_t currentX = (orientation == Ship::Orientation::horizontal) ? p.x + l : p.x;
        size_t currentY = (orientation == Ship::Orientation::horizontal) ? p.y : p.y + l;

        if (!isInPlayGround({currentX, currentY}) || (cells[currentX][currentY].GetState() == CellStates::ship)) {
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
                    (cells[neighborX][neighborY].GetState() == CellStates::ship)) {
                    return true;
                }
            }
        }
    }
    return false;
    }

void PlayGround::PlaceShip(Ship* ship, Point position, Ship::Orientation orientation) {
        if (ship == nullptr) {
            throw invalid_argument("Cannot place null object");
        }

        if (checkCollision(position, *ship, orientation)) {
            throw invalid_argument("Cannot place ship on this coordinates!");
        }

        if (orientation == Ship::Orientation::horizontal) {
            for(size_t x = position.x; x < position.x + ship->getSize(); ++x) {
                cells[x][position.y].ChangeState(CellStates::ship);
            }
            ship->setCoords(position);
            ship->setOrientation(orientation);
        }
        else if (orientation == Ship::Orientation::vertical) {
            for(size_t y = position.y; y < position.y + ship->getSize(); ++y) {
                cells[position.x][y].ChangeState(CellStates::ship);
            }
            ship->setCoords(position);
            ship->setOrientation(orientation);
        }
    }

void PlayGround::DisplayPlayground() {
        for (size_t y = 0; y < this->size; ++y) {
            for (size_t x = 0; x < this->size; ++x) {
                cout << "Amount of hits: " << hits_number << " " << "Amount of misses: " << miss_number << "\n";
                cout << "Total accuracy: " << double(hits_number) / double(hits_number + miss_number) << "\n";
                if (cells[x][y].GetState() == CellStates::unknown) {
                    cout << "#" << " ";
                }
                else if (cells[x][y].GetState() == CellStates::empty) {
                    cout << "*" << " ";
                }
                else if (cells[x][y].GetState() == CellStates::ship) {
                    cout << "S" << " ";
                }
            }
            cout << '\n';
        }
    }

void PlayGround::DisplayPlayground(ShipManager& Manager) {
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
                    cout << int(Manager.getShip({x, y})->getSegment({x, y})) << " ";
                }
            }
            cout << '\n';
        }
    }

void PlayGround::Attack(Point p, ShipManager& Manager) {
        switch (this->cells[p.x][p.y].GetState()) {
            case ship: {
                Ship* ship = Manager.getShip(p);
                if (ship->getOrientation() == Ship::Orientation::horizontal) {
                        ship->changeSegmentState(p.x - ship->getCoords().x);
                }
                else {
                    ship->changeSegmentState(p.y - ship->getCoords().y);
                }
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
                Ship* ship =  Manager.getShip(p);
                if (ship) {
                    cout << "Hit!\n";
                    hits_number += 1;
                    this->cells[p.x][p.y].ChangeState(CellStates::ship);
                    if (ship->getOrientation() == Ship::Orientation::horizontal) {
                        ship->changeSegmentState(p.x - ship->getCoords().x);
                    }
                    else {
                        ship->changeSegmentState(p.y - ship->getCoords().y);
                    }
                }
                else {
                    cout << "Miss!\n";
                    miss_number += 1;
                    this->cells[p.x][p.y].ChangeState(CellStates::empty);
                }
                break;
            }
        }
    }