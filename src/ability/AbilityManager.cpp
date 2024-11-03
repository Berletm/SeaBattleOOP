#include <random>
#include <algorithm>
#include <vector>

#include "AbilityManager.hpp"

void AbilityManager::emptyAbilityQueue() {
    while(!avalaible_abilities.empty()) {
        avalaible_abilities.pop();
    }
}

void AbilityManager::getRandomAbility() {
    srand(time(NULL));
    AbilityRegistry& registry = AbilityRegistry::instance();
    auto ability = *(registry.begin() + (rand() % registry.size()));
    avalaible_abilities.push(ability);
}

void AbilityManager::getRocketBarrage() {
    avalaible_abilities.push("RocketBarrage");
}

void AbilityManager::getScanner() {
    avalaible_abilities.push("Scanner");
}

void AbilityManager::getDoubleDamage() {
    avalaible_abilities.push("DoubleDamage");
}

const std::string AbilityManager::top() const {
    if (avalaible_abilities.empty()) {
        throw NoAbilityException("Ability queue is empty");
    }

    auto res = avalaible_abilities.front();
    return res;
}

void AbilityManager::pop() {
    avalaible_abilities.pop();
}