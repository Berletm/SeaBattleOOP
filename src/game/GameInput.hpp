#ifndef GAME_INPUT_HPP_
#define GAME_INPUT_HPP_

class Game;
#include "other/HumanPlayer.hpp"

class GameInput {
protected:
    friend class BattleState;
    friend class Game;
    enum class action {CURSOR_DOWN, CURSOR_UP, CURSOR_LEFT, CURSOR_RIGHT, PRIMARY_ACTION, ROTATE, SECONDARY_ACTION, SAVE, LOAD};
    std::unordered_map<char, action> keybinds = {
        {'s', action::CURSOR_DOWN},
        {'w', action::CURSOR_UP},
        {'a', action::CURSOR_LEFT},
        {'d', action::CURSOR_RIGHT},
        {'e', action::PRIMARY_ACTION},
        {'r', action::ROTATE},
        {'q', action::SECONDARY_ACTION},
        {'t', action::SAVE},
        {'l', action::LOAD}
    };
public:
    void operator>>(Game& game);
    action ConvertStringToAction(std::string input);
    bool InputXYR(Point& p, Ship::Orientation& r);
    bool InputXY(Point& p);
    bool InputX(size_t& x);
    action InputAction();
};

#endif