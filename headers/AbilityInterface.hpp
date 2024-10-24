#ifndef ABILLITY_INTERFACE_HPP_
#define ABILLITY_INTERFACE_HPP_
#include "Point.hpp"
class PlayGround;
class ShipManager;

class AbilityInterface {
public:
    void virtual printAbility() = 0;

    bool virtual applyAbility(PlayGround& Field, ShipManager& ShipManager, Point& point) = 0;
    
    virtual ~AbilityInterface() = default;
};

#endif