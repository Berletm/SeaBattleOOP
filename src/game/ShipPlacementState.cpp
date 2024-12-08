#include "ShipPlacementState.hpp"
#include "BattleState.hpp"
#include <chrono>

void ShipPlacementState::BotShipPlacement() {
    std::mt19937 rnd(std::chrono::steady_clock::now().time_since_epoch().count());
    std::uniform_int_distribution<size_t> dist(0, Getbot().Field.getFieldSize() - 1);

    while(Ship* bot_ship = Getbot().SManager.getShip()) {
        Point& bot_cursor = Getbot().cursor;
        Ship::Orientation rotate = Ship::Orientation(dist(rnd) % 2);

        bot_cursor.x = dist(rnd);
        bot_cursor.y = dist(rnd);

        try {
            Getbot().Field.PlaceShip(bot_ship, bot_cursor, rotate);
        }
        catch (const CollisionException& e) {
            continue;
        }
    }
}

void ShipPlacementState::DoStateJob() {
    
    game.output.log_msg("Now place your ships!");

    while(Ship* player_ship = Getplayer().SManager.getShip()) {
        Point& player_cursor = Getplayer().cursor;
        Ship::Orientation rotate = Ship::Orientation::horizontal;

        while (game.input.InputXYR(player_cursor, rotate)) {
            game.output.clear();
            if (size_t(rotate)) {
                game.output.draw_field(Getplayer().Field, player_cursor, {player_ship->getSize(), 1}, true);

            }
            else {
                game.output.draw_field(Getplayer().Field, player_cursor, {1, player_ship->getSize()}, true);
            }
            std::cout << "rotation = " << size_t(rotate) << std::endl;
        }
        try {
            Getplayer().Field.PlaceShip(player_ship, player_cursor, rotate);
        }
        catch (const CollisionException& e) {
            game.output.log_msg("Can not place ship here, try again");
            continue;
        }
    }
    this->BotShipPlacement();
    game.ChangeState(new BattleState(game));
}