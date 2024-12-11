#ifndef SHIP_PLACEMENT_STATE_HPP_
#define SHIP_PLACEMENT_STATE_HPP_

#include "GameState.hpp"

class Game;

class ShipPlacementState final: public GameState {
public:
    explicit ShipPlacementState(Game& game) noexcept(true);
    
    void DoStateJob();

    void BotShipPlacement();
};

#endif