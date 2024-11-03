#ifndef DOUBLE_DAMAGE_HPP_
#define DOUBLE_DAMAGE_HPP_

#include "AbilityInterface.hpp"

struct Player;

class DoubleDamage final: public AbilityInterface {
private:
    Player& user;
public:
    explicit DoubleDamage(Player& user);

    bool applyAbility() const override;

    static void registerAbility();
};

#endif