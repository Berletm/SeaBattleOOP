#include <random>
#include <algorithm>
#include <vector>

#include "AbilityManager.hpp"

void AbilityManager::emptyAbilityQueue() {
    while(!avalaible_abilities.empty()) {
        avalaible_abilities.pop_back();
    }
}

void AbilityManager::getRandomAbility() {
    srand(time(NULL));
    AbilityRegistry& registry = AbilityRegistry::instance();
    auto ability = *(registry.begin() + (rand() % registry.size()));
    avalaible_abilities.push_back(ability);
}

void AbilityManager::getAbility(const std::string& ability) {
    avalaible_abilities.push_back(ability);
}

void AbilityManager::getRocketBarrage() {
    avalaible_abilities.push_back("RocketBarrage");
}

void AbilityManager::getScanner() {
    avalaible_abilities.push_back("Scanner");
}

void AbilityManager::getDoubleDamage() {
    avalaible_abilities.push_back("DoubleDamage");
}

const std::string AbilityManager::top() const {
    if (avalaible_abilities.empty()) {
        throw NoAbilityException("Ability queue is empty");
    }

    auto res = avalaible_abilities.front();
    return res;
}

void AbilityManager::pop() {
    std::reverse(avalaible_abilities.begin(), avalaible_abilities.end());
    avalaible_abilities.pop_back();
    std::reverse(avalaible_abilities.begin(), avalaible_abilities.end());
}

json AbilityManager::to_json() {
    json save_file = json::array();

    for (const auto& ability: avalaible_abilities) {
        save_file.push_back(ability);
    }
    
    return save_file;
}
