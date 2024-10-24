#ifndef ROCKET_BARRAGE_HPP_
#define ROCKET_BARRAGE_HPP_
#include "AbilityInterface.hpp"

class RocketBarrage final: public AbilityInterface {
public:
    bool applyAbility(PlayGround& Field, ShipManager& manager, Point& point) override;
    
    void printAbility() override;
};

#endif