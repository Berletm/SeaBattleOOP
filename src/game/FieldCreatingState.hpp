#ifndef FIELD_CREATING_HPP_
#define FIELD_CREATING_HPP_

#include "GameState.hpp"
#include <cstddef>

class Game;

class FieldCreatingState final: public GameState {
private:
    size_t size;
public:
    explicit FieldCreatingState(Game& game) noexcept(true);

    void DoStateJob();
};


#endif