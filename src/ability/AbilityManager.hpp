#ifndef ABILITY_MANAGER_HPP_
#define ABILITY_MANAGER_HPP_

#include <queue>
#include <memory>
#include <vector>
#include <algorithm>
#include <random>
#include <tuple>
#include <nlohmann/json.hpp>

#include "other/GameException.hpp"
#include "DoubleDamage.hpp"
#include "Scanner.hpp"
#include "RocketBarrage.hpp"
#include "AbilityInterface.hpp"
#include "AbilityRegistry.hpp"

using json = nlohmann::json;

class AbilityManager {
public:
    explicit AbilityManager() {
        for (const auto& ability: AbilityRegistry::instance()) {
            avalaible_abilities.push_back(ability);
        }
        
        std::random_device rd;
        std::mt19937 generator(rd());
        shuffle(avalaible_abilities.begin(), avalaible_abilities.end(), generator);
    }

    const std::string top() const;

    void pop();

    void emptyAbilityQueue();

    const std::string getRandomAbility();

    void getRocketBarrage();

    void getScanner();
    
    void getDoubleDamage();

    void getAbility(const std::string& ability);

    json to_json();
private:
    std::vector<std::string> avalaible_abilities;
};

#endif