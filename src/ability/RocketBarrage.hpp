#ifndef ROCKET_BARRAGE_HPP_
#define ROCKET_BARRAGE_HPP_

#include "AbilityInterface.hpp"

struct Player;

class RocketBarrage final: public AbilityInterface {
private:
    Player& user;
    Player& target;
public:
    RocketBarrage(Player& user, Player& target);

    bool applyAbility() const override;

    static void registerAbility();
};

#endif