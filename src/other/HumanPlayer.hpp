#ifndef HUMAN_PLAYER_HPP_
#define HUMAN_PLAYER_HPP_

#include "ability/AbilityManager.hpp"
#include "Player.hpp"
#include <nlohmann/json.hpp>

using json = nlohmann::json;

struct HumanPlayer: public Player {
    AbilityManager AManager;

    void attack(Player& target);
    void applyAbility(Player& target);
    json to_json();
};

#endif