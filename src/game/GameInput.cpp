#include "GameInput.hpp"

bool GameInput::InputXY(Point& p) {
    std::string input;
    std::cin >> input;

    GameInput::action act = ConvertStringToAction(input);
    switch (act) {
        case action::CURSOR_DOWN: {
            if (p.y > 0) p.y--;
            break;
        }
        case action::CURSOR_UP: {
            p.y++;
            break;
        }
        case action::CURSOR_LEFT: {
            if (p.x > 0) p.x--;
            break;
        }
        case action::CURSOR_RIGHT: {
            p.x++;
            break;
        }
        case action::PRIMARY_ACTION: {
            return false;
        }
        default: return false;
    }
    return true;
}

bool GameInput::InputX(size_t& x) {
    std::string input;
    std::cin >> input;

    GameInput::action act = ConvertStringToAction(input);
    switch (act) {
        case action::CURSOR_LEFT: {
            if (x > 0) x--;
            break;
        }
        case action::CURSOR_RIGHT: {
            x++;
            break;
        }
        case action::PRIMARY_ACTION: {
            return false;
        }
        default: return false;
    }
    return true;
} 

bool GameInput::InputXYR(Point& p, Ship::Orientation& r) {
    std::string input;
    std::cin >> input;

    GameInput::action act = ConvertStringToAction(input);
    switch (act) {
        case action::CURSOR_DOWN: {
            if (p.y > 0) p.y--;
            break;
        }
        case action::CURSOR_UP: {
            p.y++;
            break;
        }
        case action::CURSOR_LEFT: {
            if (p.x > 0) p.x--;
            break;
        }
        case action::CURSOR_RIGHT: {
            p.x++;
            break;
        }
        case action::PRIMARY_ACTION: {
            return false;
        }
        case action::ROTATE: {
            r = (r == Ship::Orientation::vertical ? Ship::Orientation::horizontal: Ship::Orientation::vertical);
            break;
        }
        default: return false;
    }
    return true;
}

GameInput::action GameInput::ConvertStringToAction(std::string input) {
    char c = input[0];
    auto it = keybinds.find(c);

    if (it != keybinds.end()) {
        return it->second;
    }
    else {
        throw std::invalid_argument("invalid command character");
    }
}

GameInput::action GameInput::InputAction() {
    std::string input;
    std::cin >> input;

    return ConvertStringToAction(input);
}