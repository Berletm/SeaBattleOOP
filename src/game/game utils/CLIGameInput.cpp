#include "CLIGameInput.hpp"
#include "../FileHandler.hpp"
#include "./other/GameException.hpp"

CLIGameInput::CLIGameInput() {
    try {
        FileHandler fh(custom_binds);
        fh.open_for_read();
        fh.read(*this);
        }
    catch(const std::exception& e) {
        std::cout << e.what() << std::endl;
        std::cout << "default keybinds applied" << std::endl;
        FileHandler fh(default_keybinds);
        fh.open_for_read();
        fh.read(*this);
    }
}

CLIGameInput& CLIGameInput::instance() {
    static CLIGameInput self;
    return self;
}

bool CLIGameInput::InputXY(Point& p) {
    action act = InputAction();
    switch (act) {
        case action::CURSOR_DOWN: {
            p.y++;
            break;
        }
        case action::CURSOR_UP: {
            if (p.y > 0) p.y--;
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

bool CLIGameInput::InputX(size_t& x) {
    action act = InputAction();
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

bool CLIGameInput::InputXYR(Point& p, Ship::Orientation& r) {
    action act = InputAction();
    switch (act) {
        case action::CURSOR_UP: {
            if (p.y > 0) p.y--;
            break;
        }
        case action::CURSOR_DOWN: {
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

action CLIGameInput::ConvertCharToAction(const char c) const {
    auto it = keybinds.find(c);

    if (it != keybinds.end()) {
        return it->second;
    }
    else {
        return action::INVALID;
    }
}

action CLIGameInput::InputAction() {
    char input;
    std::cin >> input;

    return ConvertCharToAction(input);
}

void CLIGameInput::CheckBinds() const {
    std::vector<action> actions;

    for (const auto& [key, action]: keybinds) {
        if (std::find(actions.begin(), actions.end(), action) != actions.end()) {
            throw GameException("Bind one action twice is forbiden\n");
        }
        actions.emplace_back(action);
    }
}

std::istream& operator>>(std::istream& is, CLIGameInput& game_input) {
    json j;
    is >> j;

    for (const auto& [key, val]: j.items()) {
        auto it = game_input.compulsory_binds.find(val);
        if (it != game_input.compulsory_binds.end()) {
            game_input.keybinds[key[0]] = it->second;
        }
        else {
            throw GameException("Unknown action bind\n");
        }
    }

    if (game_input.keybinds.size() != game_input.compulsory_binds.size()) {
        throw GameException("Binding one key twice is forbiden\n");
    }

    game_input.CheckBinds();

    return is;
}

const std::string CLIGameInput::InputString() const {
    std::string res;
    std::cin >> res;
    return res;
}
