#include <random>
#include <algorithm>
#include <vector>
#include "AbilityManager.hpp"

void AbilityManager::emptyAbilityQueue() {
    while(!avalaible_abilities.empty()) {
        avalaible_abilities.front()->printAbility();
        avalaible_abilities.pop();
    }
}


bool AbilityManager::ApplyAvalaibleAbillity(PlayGround& Field, ShipManager& ShipManager, Point point) {
    if (avalaible_abilities.size() == 0) {
        throw NoAbilityException("No abillities have left");
    }
    std::unique_ptr<AbilityInterface> ability = std::move(avalaible_abilities.front());
    avalaible_abilities.pop();
    return ability->applyAbility(Field, ShipManager, point);
}

void AbilityManager::getRandomAbility() {
    srand(time(NULL));
    Abilities ability_idx = Abilities(rand() % 3);
    switch (ability_idx) {
        case Abilities::DoubleDamage: {
            avalaible_abilities.push(std::make_unique<DoubleDamage>());
            break;
        }
        case Abilities::Scanner: {
            avalaible_abilities.push(std::make_unique<Scanner>());
            break;
        }
        case Abilities::RocketBarrage: {
            avalaible_abilities.push(std::make_unique<RocketBarrage>());
            break;
        }
    }
}

void AbilityManager::getRocketBarrage() {
    avalaible_abilities.push(std::make_unique<RocketBarrage>());
}

void AbilityManager::getScanner() {
    avalaible_abilities.push(std::make_unique<Scanner>());
}

void AbilityManager::getDoubleDamage() {
    avalaible_abilities.push(std::make_unique<DoubleDamage>());
}