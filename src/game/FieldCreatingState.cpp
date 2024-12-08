#include "FieldCreatingState.hpp"
#include "ShipInitializationState.hpp"

void FieldCreatingState::DoStateJob() { 
    while (game.input.InputX(size)) {
        game.output.clear();
        std::cout << "Field size: " << size << " width" << size << " height" << std::endl;
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