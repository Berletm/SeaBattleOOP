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
    void update();
    void render_msg(std::string_view msg);
};

template <class Output>
void GameRenderer<Output>::render() {
    output.draw_field(game.bot.Field, game.player.cursor);
}

template <class Output>
void GameRenderer<Output>::render_msg(std::string_view msg) {
    output.log_msg(msg);
}

template <class Output>
void GameRenderer<Output>::update() {
    render();
}


#endif