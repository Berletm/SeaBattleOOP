#include "Scanner.hpp"
#include "PlayGround.hpp"
#include <iostream>

bool Scanner::applyAbility(PlayGround& Field, ShipManager& ShipManager, Point& point) {
    if (!Field.isInPlayGround(point) || !Field.isInPlayGround({point.x + 2, point.y + 2})) {
        throw OutOfFieldAttackException("Can not scan area located out of field");
    }
    std::cout << "Scanner used on field" << "\n";
    for (size_t x = point.x; x < point.x + 2; ++x) {
        for (size_t y = point.y; y < point.y + 2; ++y) {
            if (Field.getCellState({x, y}) == CellStates::ship) {
                return true;
            }
        }
    }
    return false;
}

void Scanner::printAbility() {
    std::cout << "Scanner" << "\n";
}