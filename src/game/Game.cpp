#include "Game.hpp"
#include "GameInput.hpp"
#include "FieldCreatingState.hpp"
#include "ShipInitializationState.hpp"
#include "ShipPlacementState.hpp"
#include "BattleState.hpp"

Game::Game() {
    current_state = new FieldCreatingState(*this);
}

void Game::StartNewGame() {
    while (is_running) {
        (*current_state) << input;
    }
}

void Game::Play() {
    if (input.InputAction() == GameInput::action::LOAD) {
        std::string save_file;
        std::cin >> save_file;
        current_state->load(save_file);
        this->ChangeState(new BattleState(*this));
    }
    is_running = true;
    StartNewGame();
}

void Game::ChangeState(GameState* new_state) {
    delete current_state;
    current_state = new_state;
}

Game::~Game() {
    delete current_state;
}

bool Game::IsRunning() {
    return is_running;
}

void Game::Quit() {
    is_running = false;
}