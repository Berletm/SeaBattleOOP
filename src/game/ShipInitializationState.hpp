#ifndef SHIP_INITIALIZATION_STATE_HPP_
#define SHIP_INITIALIZATION_STATE_HPP_

#include "GameInput.hpp"
#include "Game.hpp"
#include "other/ShipsData.hpp"

class ShipInitializationState final: public GameState {
private:
    static constexpr size_t freedom_coefficient = 0;
    std::vector<size_t> ship_sizes;
    ssize_t points;
    size_t ship_counter;
    ShipData data;
public:
    inline ShipInitializationState(Game& game): GameState(game) {
        points = pow(Getplayer().Field.getFieldSize(), 2);
        ship_counter = 0;
        data = {
            {ShipType::battleship, 0},
            {ShipType::cruiser, 0},
            {ShipType::destroyer, 0},
            {ShipType::vedette, 0}
        };
    };
    void operator<<(GameInput msg);

    size_t convert_ship_size_to_points(size_t size);
};

#endif