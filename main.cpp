#include <random>
#include <unistd.h>
#include <algorithm>

#include "other/Ship.hpp"
#include "other/ShipManager.hpp"
#include "other/PlayGround.hpp"
#include "ability/AbilityRegistry.hpp"
#include "other/HumanPlayer.hpp"
#include "game/game utils/GameControl.hpp"
#include "game/game utils/GameRenderer.hpp"

void register_all_abilities() {
    DoubleDamage::registerAbility();
    RocketBarrage::registerAbility();
    Scanner::registerAbility();
}

int main() {
    register_all_abilities();
    try {
        Game session;
        GameControl<CLIGameInput, GameRenderer<CLIGameOutput>> controller(session);
        controller.run();
    }
    catch(const std::exception& e) {
        std::cout << e.what() << "\n";
    }

    return 0;
}