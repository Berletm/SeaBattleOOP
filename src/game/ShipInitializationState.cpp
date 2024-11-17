#include "ShipInitializationState.hpp"
#include "ShipPlacementState.hpp"

void ShipInitializationState::operator<<(GameInput msg) {
    std::cout << "Input your ships" << std::endl;
    for (size_t i = 0; i < ship_counter; ++i) {
        size_t current_ship_size = 1;
        while(msg.InputX(current_ship_size)) {
            system("clear");
            DisplayData(data);
            std::cout << "Current ship: " << current_ship_size % 4  + 1 << std::endl;
        }
        data[ShipType(current_ship_size % 4  + 1)] += 1;
        ship_sizes.push_back(current_ship_size % 4  + 1);
    }
    try {
        Getplayer().SManager = ShipManager(ship_counter, ship_sizes);
        Getbot().SManager = ShipManager(ship_counter, ship_sizes);
        game.ChangeState(new ShipPlacementState(game));
    }
    catch (const GameException& e) {
        e.what();
    }
}