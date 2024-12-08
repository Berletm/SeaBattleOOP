#include <random>

#include "other/Player.hpp"
#include "RocketBarrage.hpp"
#include "other/PlayGround.hpp"
#include "other/ShipManager.hpp"
#include "AbilityRegistry.hpp"

RocketBarrage::RocketBarrage(Player& user, Player& target): user(user), target(target) {}

bool RocketBarrage::applyAbility() const {
    srand(time(NULL));

    if (target.SManager.getShipAmount() > 0) {
        size_t random_idx = rand() % target.SManager.getShipAmount();
        Ship* ship = target.SManager.getShip(random_idx);
        size_t segment_idx = rand() % ship->getSize();
        if (user.double_damage_buff) {
            ship->changeSegmentState(segment_idx);
            user.double_damage_buff = false;
        }
        ship->changeSegmentState(segment_idx);
        return true;
    }
    return false;
}

void RocketBarrage::registerAbility() {
    AbilityRegistry::instance().registerAbility("RocketBarrage", [](Player& user, Player& target) {
        return std::make_unique<RocketBarrage>(user, target);
    });
}