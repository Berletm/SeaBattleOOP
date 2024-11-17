#ifndef SHIP_PLACEMENT_STATE_HPP_
#define SHIP_PLACEMENT_STATE_HPP_

#include "GameInput.hpp"
#include "Game.hpp"

class ShipPlacementState final: public GameState {
public:
    inline explicit ShipPlacementState(Game& game): GameState(game) {
        std::cout << "Now place your ships!" << std::endl;
    }

    void operator<<(GameInput msg);

    void BotShipPlacement();
};

#endif