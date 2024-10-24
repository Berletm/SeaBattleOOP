#ifndef ABILITY_MANAGER_HPP_
#define ABILITY_MANAGER_HPP_
#include <queue>
#include <memory>
#include <vector>
#include <algorithm>
#include <random>
#include "GameException.hpp"
#include "DoubleDamage.hpp"
#include "Scanner.hpp"
#include "RocketBarrage.hpp"
#include "AbilityInterface.hpp"


class AbilityManager {
public:
    explicit AbilityManager() {
        std::vector<std::unique_ptr<AbilityInterface>> shuffle_abillitites;
        shuffle_abillitites.emplace_back(std::make_unique<DoubleDamage>());
        shuffle_abillitites.emplace_back(std::make_unique<Scanner>());
        shuffle_abillitites.emplace_back(std::make_unique<RocketBarrage>());

        std::random_device rd;
        std::mt19937 generator(rd());
        shuffle(shuffle_abillitites.begin(), shuffle_abillitites.end(), generator);

        for (auto& abillity: shuffle_abillitites) {
            avalaible_abilities.push(std::move(abillity));
        }
    }

    void emptyAbilityQueue();

    bool ApplyAvalaibleAbillity(PlayGround& Field, ShipManager& ShipManager, Point point = {0, 0});

    void getRandomAbility();

    void getRocketBarrage();

    void getScanner();
    
    void getDoubleDamage();
private:
    enum class Abilities {DoubleDamage, Scanner, RocketBarrage};
    std::queue<std::unique_ptr<AbilityInterface>> avalaible_abilities;
};

#endif