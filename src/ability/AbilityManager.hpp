#ifndef ABILITY_MANAGER_HPP_
#define ABILITY_MANAGER_HPP_

#include <queue>
#include <memory>
#include <vector>
#include <algorithm>
#include <random>
#include <tuple>

#include "other/GameException.hpp"

#include "DoubleDamage.hpp"
#include "Scanner.hpp"
#include "RocketBarrage.hpp"

#include "AbilityInterface.hpp"
#include "AbilityRegistry.hpp"

class AbilityManager {
public:
    explicit AbilityManager() {
        std::vector<std::string> shuffle_abillitites;
        for (const auto& ability: AbilityRegistry::instance()) {
            shuffle_abillitites.push_back(ability);
        }
        std::random_device rd;
        std::mt19937 generator(rd());
        shuffle(shuffle_abillitites.begin(), shuffle_abillitites.end(), generator);

        for (auto& abillity: shuffle_abillitites) {
            avalaible_abilities.push(abillity);
        }
    }

    const std::string top() const;

    void pop();

    void emptyAbilityQueue();

    void getRandomAbility();

    void getRocketBarrage();

    void getScanner();
    
    void getDoubleDamage();
private:
    std::queue<std::string> avalaible_abilities;
};

#endif