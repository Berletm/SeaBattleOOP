#include "HumanPlayer.hpp"

void HumanPlayer::applyAbility(Player& target) {
    auto ability_name = AManager.top();
    AManager.pop();

    output.ability_msg(ability_name);

    if (ability_name == "Scanner") {
        output.clear();
        output.draw_fields(this->Field, target.Field, cursor, {2, 2}, true);
        output.ability_msg(ability_name);

        while (input.InputXY(this->cursor)) {
            output.clear();
            output.draw_fields(this->Field, target.Field, cursor, {2, 2}, true);
            output.ability_msg(ability_name);
        }
    }

    auto ability = AbilityRegistry::instance().createAbility(ability_name, *this, target);
    auto res = ability->applyAbility();
    output.ability_msg(ability_name, res);
}

void HumanPlayer::attack(Player& target) {
    bool hitted = target.Field.Attack(cursor);

    if (double_damage_buff) {
        hitted |= target.Field.Attack(cursor);
        double_damage_buff = false;
    }

    if (hitted && target.Field.getShip(cursor)->isDestroyed()) {
        auto ability = AManager.getRandomAbility();
        output.log_msg(ability);
    }
}

json HumanPlayer::to_json() {
    json save_file = Player::to_json();
    save_file["AbilityManager"] = AManager.to_json();
    return save_file;
}