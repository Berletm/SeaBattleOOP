#ifndef DOUBLE_DAMAGE_HPP_
#define DOUBLE_DAMAGE_HPP_
#include "AbilityInterface.hpp"

class DoubleDamage final: public AbilityInterface {
public:
    bool applyAbility(PlayGround& Field, ShipManager& ShipManager, Point& point) override;
    
    void printAbility() override;
};

#endif