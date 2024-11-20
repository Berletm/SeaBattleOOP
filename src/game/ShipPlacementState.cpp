#include "ShipPlacementState.hpp"
#include "BattleState.hpp"
#include <chrono>

void ShipPlacementState::operator<<(GameInput msg) {
    std::cout << "Now place your ships!" << std::endl;
    while(Ship* player_ship = Getplayer().SManager.getShip()) {
        Point& player_cursor = Getplayer().cursor;
        Ship::Orientation rotate = Ship::Orientation::horizontal;

        while (msg.InputXYR(player_cursor, rotate)) {
            system("clear");
            std::cout << "x = " << player_cursor.x << "y = " << player_cursor.y << std::endl;
            std::cout << "rotation = " << size_t(rotate) << std::endl;
        }
        try {
            Getplayer().Field.PlaceShip(player_ship, player_cursor, rotate);
        }
        catch (const CollisionException& e) {
            std::cout << "Can not place ship here, try again" << std::endl;
            continue;
        }
    }
    this->BotShipPlacement();
    game.ChangeState(new BattleState(game));
}

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