#include <iostream>

#include "other/Player.hpp"
#include "Scanner.hpp"
#include "other/PlayGround.hpp"
#include "AbilityRegistry.hpp"


Scanner::Scanner(Player& user, Player& target): user(user), target(target) {}

bool Scanner::applyAbility() const {
    if (!user.Field.isInPlayGround(user.cursor) || !user.Field.isInPlayGround({user.cursor.x + 1, user.cursor.y + 1})) {
        throw OutOfFieldAttackException("Can not scan area located out of field");
    }

    for (size_t x = user.cursor.x; x < user.cursor.x + 1; ++x) {
        for (size_t y = user.cursor.y; y < user.cursor.y + 1; ++y) {
            if (target.Field.getCellState({x, y}) == CellStates::ship) {
                return true;
            }
        }
    }
    return false;
}

void Scanner::registerAbility() {
    AbilityRegistry::instance().registerAbility("Scanner", [](Player& user, Player& target) {
        return std::make_unique<Scanner>(user, target);
    });
}