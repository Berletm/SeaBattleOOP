#ifndef HUMAN_PLAYER_HPP_
#define HUMAN_PLAYER_HPP_

#include "Player.hpp"
#include "./game/game utils/CLIGameInput.hpp"
#include "./game/game utils/CLIGameOutput.hpp"

struct HumanPlayer: public Player {
    AbilityManager AManager;
    CLIGameInput input = CLIGameInput::instance();
    CLIGameOutput output = CLIGameOutput::instance();
    
    void attack(Player& target);
    void applyAbility(Player& target);
    json to_json();
};

#endif