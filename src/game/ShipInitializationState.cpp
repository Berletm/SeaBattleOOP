#include "ShipInitializationState.hpp"
#include "ShipPlacementState.hpp"

void ShipInitializationState::operator<<(GameInput msg) {
    std::cout << "Input your ships" << std::endl;
    ssize_t min_cost = convert_ship_size_to_points(1);
    while (points - min_cost >= 0) {
        size_t current_ship_size = 1;
        while(msg.InputX(current_ship_size)) {
            system("clear");
            DisplayData(data);
            std::cout << "Current ship: " << (current_ship_size % 4) + 1 << std::endl;
        }
        current_ship_size = (current_ship_size % 4) + 1;
        ssize_t ship_cost = convert_ship_size_to_points(current_ship_size);
        
        points -= ship_cost;
        ship_counter++;
        data[ShipType(current_ship_size)] += 1;
        ship_sizes.push_back(current_ship_size);
    }
    if (ship_counter == 0) {
        throw GameException("Too shmall field\n");
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

size_t ShipInitializationState::convert_ship_size_to_points(size_t size) {
    return (size + 2) * 3 + freedom_coefficient;
}