#ifndef ABILLITY_INTERFACE_HPP_
#define ABILLITY_INTERFACE_HPP_

#include "other/Point.hpp"

class AbilityInterface {
public:
    virtual bool applyAbility() const = 0;

    virtual ~AbilityInterface() = default;
};

#endif