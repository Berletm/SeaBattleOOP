#ifndef SCANNER_HPP_
#define SCANNER_HPP_

#include "AbilityInterface.hpp"

struct Player;

class Scanner final: public AbilityInterface {
private:
    Player& target;
    Player& user;
public:
    Scanner(Player& user, Player& target);
    
    bool applyAbility() const override;
    
    static void registerAbility();
};

#endif