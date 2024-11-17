#include <random>
#include <unistd.h>
#include <algorithm>

#include "other/Ship.hpp"
#include "other/ShipManager.hpp"
#include "other/PlayGround.hpp"
#include "ability/AbilityRegistry.hpp"
#include "other/HumanPlayer.hpp"
#include "game/Game.hpp"

void registerAllAbilities() {
    DoubleDamage::registerAbility();
    RocketBarrage::registerAbility();
    Scanner::registerAbility();
}


int main() {
    registerAllAbilities();
    try {
        Game session;
        session.Play();
    }
    catch(const std::exception& e) {
        std::cout << e.what() << "\n";
    }

    return 0;
}