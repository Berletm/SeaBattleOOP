#include <random>
#include <unistd.h>
#include <algorithm>

#include "other/Ship.hpp"
#include "other/ShipManager.hpp"
#include "other/PlayGround.hpp"
#include "SFML/Graphics.hpp"
#include "ability/AbilityRegistry.hpp"
#include "other/HumanPlayer.hpp"

void registerAllAbilities() {
    DoubleDamage::registerAbility();
    RocketBarrage::registerAbility();
    Scanner::registerAbility();
}


int main() {
    registerAllAbilities();
    try {
        std::vector<size_t> sizes = {1, 2, 3, 4};
        PlayGround Field(10);
        ShipManager ShipManager(sizes.size(), sizes);
        AbilityManager AbilityManager;
        HumanPlayer player(Field, ShipManager, AbilityManager);
        Field.PlaceShip(ShipManager.getShip(), {0, 0}, Ship::Orientation::horizontal);
        Field.PlaceShip(ShipManager.getShip(),  {3, 3}, Ship::Orientation::vertical);
        Field.PlaceShip(ShipManager.getShip(), {5, 6}, Ship::Orientation::horizontal);
        Field.PlaceShip(ShipManager.getShip(), {1, 5}, Ship::Orientation::vertical);
        
        AbilityManager.emptyAbilityQueue();
        AbilityManager.getDoubleDamage();
        AbilityManager.getRocketBarrage();
        
        player.cursor = {0, 0};
        player.attack(player);

        player.applyAbility(player);
        player.applyAbility(player);
        
        player.attack(player);

        player.Field.DisplayPlaygroundWithOutFogOfWar();
    }
    catch(const std::exception& e) {
        std::cout << e.what() << "\n";
    }

    return 0;
}