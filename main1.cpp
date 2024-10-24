#include <random>
#include <unistd.h>
#include <algorithm>
#include "Ship.hpp"
#include "ShipManager.hpp"
#include "PlayGround.hpp"
#include "AbilityManager.hpp"
#include "SFML/Graphics.hpp"


int main() {
    try {
        std::vector<size_t> sizes = {1, 2, 3, 4};
        PlayGround Field(10);
        ShipManager ShipManager(sizes.size(), sizes);
        AbilityManager AbilityManager;
        Field.PlaceShip(ShipManager.getShip(), {0, 0}, Ship::Orientation::horizontal);
        Field.PlaceShip(ShipManager.getShip(),  {3, 3}, Ship::Orientation::vertical);
        Field.PlaceShip(ShipManager.getShip(), {5, 6}, Ship::Orientation::horizontal);
        Field.PlaceShip(ShipManager.getShip(), {1, 5}, Ship::Orientation::vertical);
        
        AbilityManager.emptyAbilityQueue();
        AbilityManager.getDoubleDamage();
        AbilityManager.getScanner();
        AbilityManager.getRocketBarrage();

        AbilityManager.ApplyAvalaibleAbillity(Field, ShipManager);
        bool res = AbilityManager.ApplyAvalaibleAbillity(Field, ShipManager, {7, 7});
        AbilityManager.ApplyAvalaibleAbillity(Field, ShipManager);

        Field.Attack({0, 0}, AbilityManager);
        std::cout << res << std::endl;
        
        Field.DisplayPlaygroundWithOutFogOfWar();
    }
    catch(const std::exception& e) {
        std::cout << e.what() << "\n";
    }

    return 0;
}