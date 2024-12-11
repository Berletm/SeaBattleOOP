#ifndef GAME_RENDERER_HPP_
#define GAME_RENDERER_HPP_

#include "./game/Game.hpp"
#include <string_view>

template <class Output>
class GameRenderer {
private:
    Output output = Output::instance();
    Game& game;
    GameRenderer(Game& game): game{game} {}

    template<typename T1, typename T2>
    friend class GameControl;
public:
    static GameRenderer& instance(Game& game) {
        static GameRenderer self(game);
        return self;
    }

    void render();

    void render_attack();

    void update();

    void render_msg(std::string_view msg);

    void render_ability_msg(std::string_view msg);

    void render_ability_res_msg(std::string_view msg, bool res);
};

template <class Output>
void GameRenderer<Output>::render() {
    output.clear();
    output.draw_fields(game.player.Field, game.bot.Field);
}

template <class Output>
void GameRenderer<Output>::render_attack() {
    output.clear();
    output.draw_field(game.bot.Field, game.player.cursor);
    output.display_buff(game.player.double_damage_buff);
}

template <class Output>
void GameRenderer<Output>::render_msg(std::string_view msg) {
    output.log_msg(msg);
}

template <class Output>
void GameRenderer<Output>::render_ability_msg(std::string_view msg) {
    output.ability_msg(msg);
}

template <class Output>
void GameRenderer<Output>::render_ability_res_msg(std::string_view msg, bool res) {
    output.ability_msg(msg, res);
}

template <class Output>
void GameRenderer<Output>::update() {
    render();
}


#endif