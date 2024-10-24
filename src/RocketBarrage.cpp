#include <random>
#include "RocketBarrage.hpp"
#include "PlayGround.hpp"
#include "ShipManager.hpp"

bool RocketBarrage::applyAbility(PlayGround& Field, ShipManager& ShipManager, Point& point) {
    std::cout << "RocketBarrage attacked the ship" << "\n";

    srand(time(NULL));

    if (ShipManager.getShipAmount() > 0) {
        size_t random_idx = rand() % ShipManager.getShipAmount();
        Ship* ship = ShipManager.getShip(random_idx);
        size_t segment_idx = rand() % ship->getSize();
        if (Field.isUnderBuff()) {
            ship->changeSegmentState(segment_idx);
            Field.dispellBuff();
        }
        ship->changeSegmentState(segment_idx);
        return true;
    }
    return false;
}

void RocketBarrage::printAbility() {
    std::cout << "RocketBarrage" << "\n";
}