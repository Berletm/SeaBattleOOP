#include "ShipInitializationState.hpp"
#include "ShipPlacementState.hpp"
#include "Game.hpp"

ShipInitializationState::ShipInitializationState(Game& game) noexcept(true): GameState(game) {
    points = pow(Getplayer().Field.getFieldSize(), 2);
    ship_counter = 0;
    data = {
        {ShipType::battleship, 0},
        {ShipType::cruiser, 0},
        {ShipType::destroyer, 0},
        {ShipType::vedette, 0}
    };
};

size_t ShipInitializationState::convert_ship_size_to_points(size_t size) {
    return (size + 2) * 3 + freedom_coefficient;
}

void ShipInitializationState::DoStateJob() {
    game.output.log_msg("Input your ships");

    ssize_t min_cost = convert_ship_size_to_points(1);
    
    while (points - min_cost >= 0) {
        size_t current_ship_size = 1;
        while(game.input.InputX(current_ship_size)) {
            game.output.clear();
            DisplayData(data);
            game.output.init_msg(this, (current_ship_size % 4) + 1 );
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
        game.output.log_msg(e.what());
    }
}