#ifndef CLI_GAME_INPUT_HPP_
#define CLI_GAME_INPUT_HPP_

class Game;
#include <string_view>
#include "./other/Ship.hpp"
#include "CLIGameOutput.hpp"

enum class action {CURSOR_DOWN, CURSOR_UP, CURSOR_LEFT, CURSOR_RIGHT, PRIMARY_ACTION, ROTATE, SECONDARY_ACTION, SAVE, LOAD, START_NEW_GAME, INVALID};

class CLIGameInput {
private:
    CLIGameInput();
    CLIGameOutput output = CLIGameOutput::instance();
protected:
    const std::string default_keybinds = "../src/game/game utils/default_keybindings.json";
    const std::string custom_binds = "../src/game/game utils/custom_keybindings.json";
    friend class BattleState;
    friend class Game;
    std::unordered_map<char, action> keybinds;
    std::unordered_map<std::string, action> compulsory_binds = {
    {"down", action::CURSOR_DOWN},
    {"up", action::CURSOR_UP}, 
    {"left", action::CURSOR_LEFT}, 
    {"right", action::CURSOR_RIGHT}, 
    {"rotate", action::ROTATE}, 
    {"primary_action", action::PRIMARY_ACTION},
    {"secondary_action", action::SECONDARY_ACTION}, 
    {"save", action::SAVE},
    {"load", action::LOAD},
    {"start_new_game", action::START_NEW_GAME}
    };
public:
    static CLIGameInput& instance();
    action ConvertCharToAction(const char c) const;
    action InputAction();
    bool InputXYR(Point& p, Ship::Orientation& r);
    bool InputXY(Point& p);
    bool InputX(size_t& x);
    const std::string InputString() const;
    void CheckBinds() const;
    friend std::istream& operator>>(std::istream& is, CLIGameInput& game_input);
};

std::istream& operator>>(std::istream& is, CLIGameInput& game_input);

#endif