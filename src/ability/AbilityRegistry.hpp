#ifndef REGISTRY_HPP_
#define REGISTRY_HPP_

#include <unordered_map>
#include <string>
#include <functional>
#include <memory>

#include "AbilityInterface.hpp"

struct Player;

class AbilityRegistry {
private:
    using AbilityCreator = std::function<std::unique_ptr<AbilityInterface>(Player&, Player&)>;
    using Registry = std::unordered_map<std::string, AbilityCreator>;
    Registry abilityMap;

    AbilityRegistry() = default;

public:
    static AbilityRegistry& instance() {
        static AbilityRegistry instance;
        return instance;
    }

    void registerAbility(const std::string& name, AbilityCreator creator) {
        abilityMap[name] = creator;
    }

    size_t size() {
        return abilityMap.size();
    }

    std::unique_ptr<AbilityInterface> createAbility(const std::string& name, Player& user, Player& target) {
        auto it = abilityMap.find(name);
        if (it != abilityMap.end()) {
            return it->second(user, target);
        }
        return nullptr;
    }

    class iterator {
    public:
        using iterator_category = std::input_iterator_tag;
        using value_type = std::string;
        using difference_type = std::ptrdiff_t;
        using pointer = const std::string*;
        using reference = const std::string&;

    private:
        std::unordered_map<std::string, AbilityCreator>::iterator current;
        std::unordered_map<std::string, AbilityCreator>::iterator end;

    public:
        iterator(std::unordered_map<std::string, AbilityCreator>::iterator start,
                 std::unordered_map<std::string, AbilityCreator>::iterator end)
            : current(start), end(end) {}

        reference operator*() const { return current->first; }
        pointer operator->() const { return &(current->first); }

        iterator& operator++() {
            ++current;
            return *this;
        }

        iterator operator+(size_t n) const {
            auto temp = *this;
            for (size_t i = 0; i < n && temp.current != temp.end; ++i) {
                ++temp.current;
            }
            return temp;
        }

        bool operator!=(const iterator& other) const {
            return current != other.current;
        }
    };

    iterator begin() {
        return iterator(abilityMap.begin(), abilityMap.end());
    }

    iterator end() {
        return iterator(abilityMap.end(), abilityMap.end());
    }
};

#endif