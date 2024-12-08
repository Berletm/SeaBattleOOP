#ifndef SHIP_PLACEMENT_STATE_HPP_
#define SHIP_PLACEMENT_STATE_HPP_

#include "game utils/CLIGameInput.hpp"
#include "Game.hpp"

class ShipPlacementState final: public GameState {
public:
    inline explicit ShipPlacementState(Game& game): GameState(game) {
    }
    
    void DoStateJob();

    void BotShipPlacement();
};

#endif