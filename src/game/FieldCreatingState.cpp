#include "FieldCreatingState.hpp"
#include "ShipInitializationState.hpp"

void FieldCreatingState::operator<<(GameInput msg) {
    while (msg.InputX(size)) {
        system("clear");
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