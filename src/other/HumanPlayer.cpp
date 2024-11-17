#include <nlohmann/json.hpp>
#include "HumanPlayer.hpp"
#include "game/GameInput.hpp"

using json = nlohmann::json;

void HumanPlayer::applyAbility(Player& target) {
    auto ability_name = AManager.top();
    AManager.pop();

    if (ability_name == "Scanner") {
        GameInput input;
        std::cout << "Input area to be scanned" << std::endl;
        while (input.InputXY(this->cursor)) {
            system("clear");
            std::cout << "Input area to be scanned" << std::endl;
            std::cout << "x = " << this->cursor.x << " y = " << this->cursor.y << std::endl;
        }
    }

    auto ability = AbilityRegistry::instance().createAbility(ability_name, *this, target);
    auto res = ability->applyAbility();
    std::cout << res << std::endl;
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

json HumanPlayer::to_json() {
    json save_file = Player::to_json();
    save_file["AbilityManager"] = AManager.to_json();
    return save_file;
}