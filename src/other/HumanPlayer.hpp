#ifndef HUMAN_PLAYER_HPP_
#define HUMAN_PLAYER_HPP_

#include "ability/AbilityManager.hpp"
#include "Player.hpp"

struct HumanPlayer: public Player {
    AbilityManager& AManager;

    HumanPlayer(PlayGround& Field, ShipManager& SManager, AbilityManager& AbilityManager);
    
    void attack(Player& target);
    void applyAbility(Player& target);
};

#endif