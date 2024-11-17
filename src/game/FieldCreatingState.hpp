#ifndef FIELD_CREATING_HPP_
#define FIELD_CREATING_HPP_

#include "GameInput.hpp"
#include "Game.hpp"

class FieldCreatingState final: public GameState {
private:
    size_t size;
public:
    inline explicit FieldCreatingState(Game& game): GameState(game), size(0) {
        std::cout << "Welcome to SeaBattle!" << std::endl;
    }

    void operator<<(GameInput msg);
};


#endif