#ifndef SCANNER_HPP_
#define SCANNER_HPP_
#include "AbilityInterface.hpp"
#include "Point.hpp"

class Scanner final: public AbilityInterface {
public:
    bool applyAbility(PlayGround& Field, ShipManager& ShipManager, Point& point) override;
    
    void printAbility() override;
};

#endif