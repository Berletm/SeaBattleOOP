#ifndef FIELD_CREATING_HPP_
#define FIELD_CREATING_HPP_

#include "game utils/CLIGameInput.hpp"
#include "Game.hpp"

class FieldCreatingState final: public GameState {
private:
    size_t size;
public:
    inline explicit FieldCreatingState(Game& game): GameState(game), size(0) {
        game.output.log_msg("Welcome to SeaBattle!");
    }

    void DoStateJob();
};


#endif