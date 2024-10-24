#include <iostream>
#include "DoubleDamage.hpp"
#include "PlayGround.hpp"

bool DoubleDamage::applyAbility(PlayGround& Field, ShipManager& ShipManager, Point& point) {
    std::cout << "Next attack will deal double damage!\n";
    Field.getDoubleDamageBuff();
    return true;
}

void DoubleDamage::printAbility() {
    std::cout << "DoubleDamage" << "\n";
}