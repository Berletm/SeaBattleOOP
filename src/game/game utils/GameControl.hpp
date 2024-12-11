#ifndef GAME_CONTROL_HPP_
#define GAME_CONTROL_HPP_

#include "./game/Game.hpp"

template <class Input, class Renderer>
class GameControl {
private:
    Game& current_session;
    Input input = Input::instance();
    Renderer output = Renderer::instance();
    std::map<action, std::function<void()>> actions;
public:
    GameControl(Game& game);

    void run();
};

template <class Input, class Renderer>
GameControl<Input, Renderer>::GameControl(Game& game): current_session(game), output(game) {
    actions[action::LOAD] = [&]() {current_session.Load();};
    actions[action::PRIMARY_ACTION] = [&]() {current_session.PlayerAttack();};
    actions[action::SECONDARY_ACTION] = [&]() {current_session.ApplyAbility();};
    actions[action::SAVE] = [&]() {current_session.Save();};
    actions[action::QUIT] = [&]() {current_session.Quit();};
}

template <class Input, class Renderer>
void GameControl<Input, Renderer>::run() {
    current_session.Play();
    while (current_session.is_running) {
        auto act = input.InputAction();
        if (actions.find(act) != actions.end()) {
            actions[act]();
        }
        else {
            output.render_msg("Unknown action");
        }
        if (!current_session.IsBotTurn()) continue;
        current_session.BotAttack();
        current_session.CheckGameState();
        output.render();
    }
}

#endif