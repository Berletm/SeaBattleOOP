#include "FieldCreatingState.hpp"
#include "ShipInitializationState.hpp"
#include "game utils/CLIGameInput.hpp"
#include "Game.hpp"

FieldCreatingState::FieldCreatingState(Game& game) noexcept(true): GameState(game), size(0) {
    game.output.log_msg("Welcome to SeaBattle!");
}


void FieldCreatingState::DoStateJob() { 
    while (game.input.InputX(size)) {
        game.output.clear();
        game.output.init_msg(this, size);
    }
    try {
        Getplayer().Field = PlayGround(size);
        Getbot().Field = PlayGround(size);
        game.ChangeState(new ShipInitializationState(game));
    }
    catch (GameException& e) {
        e.what();
        return;
    }
}