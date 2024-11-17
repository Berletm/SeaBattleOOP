#ifndef SHIP_INITIALIZATION_STATE_HPP_
#define SHIP_INITIALIZATION_STATE_HPP_

#include "GameInput.hpp"
#include "Game.hpp"
#include "other/ShipsData.hpp"

class ShipInitializationState final: public GameState {
private:
    std::vector<size_t> ship_sizes;
    size_t ship_counter;
    ShipData data;
public:
    inline ShipInitializationState(Game& game): GameState(game) {
        std::cout << "Input ship amount" << std::endl;
        std::cin >> ship_counter;
        data = {
            {ShipType::battleship, 0},
            {ShipType::cruiser, 0},
            {ShipType::destroyer, 0},
            {ShipType::vedette, 0}
        };
    };
    void operator<<(GameInput msg);
};

#endif