#include <iostream>
#include <memory>

#include "other/Player.hpp"
#include "DoubleDamage.hpp"
#include "other/PlayGround.hpp"
#include "AbilityRegistry.hpp"

DoubleDamage::DoubleDamage(Player& user): user(user) {} 

bool DoubleDamage::applyAbility() const{
    std::cout << "Next attack will deal double damage!\n";
    user.double_damage_buff = true;
    return true;
}

void DoubleDamage::registerAbility() {
    AbilityRegistry::instance().registerAbility("DoubleDamage", [](Player& user, Player& target) {
        return std::make_unique<DoubleDamage>(user);
    });
}