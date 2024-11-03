#include "HumanPlayer.hpp"

HumanPlayer::HumanPlayer(PlayGround& Field, ShipManager& SManager, AbilityManager& AbilityManager): Player{Field, SManager}, AManager(AbilityManager) {}

void HumanPlayer::applyAbility(Player& target) {
    auto ability_name = AManager.top();
    AManager.pop();

    auto ability = AbilityRegistry::instance().createAbility(ability_name, *this ,target);
    ability->applyAbility();
}

void HumanPlayer::attack(Player& target) {
    bool hitted = target.Field.Attack(cursor);
    
    if (double_damage_buff) {
        hitted |= target.Field.Attack(cursor);
        double_damage_buff = false;
    }

    if (hitted && target.Field.getShip(cursor)->isDestroyed()) {
        AManager.getRandomAbility();
    }
}
