#ifndef PLAYER_HPP_
#define PLAYER_HPP_

#include "PlayGround.hpp"
#include "ShipManager.hpp"

struct Player {
    PlayGround& Field;
    ShipManager& SManager;
    Point cursor;
    bool double_damage_buff;
};

#endif