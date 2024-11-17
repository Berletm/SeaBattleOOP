#ifndef PLAYER_HPP_
#define PLAYER_HPP_

#include <nlohmann/json.hpp>
#include "PlayGround.hpp"
#include "ShipManager.hpp"

using json = nlohmann::json;

struct Player {
    PlayGround Field;
    ShipManager SManager;
    Point cursor;
    bool double_damage_buff = false;

    json to_json();
};

#endif