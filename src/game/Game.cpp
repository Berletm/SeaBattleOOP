#include "Game.hpp"
#include "FieldCreatingState.hpp"
#include "ShipInitializationState.hpp"
#include "ShipPlacementState.hpp"
#include "BattleState.hpp"

Game::Game() {
    current_state = new FieldCreatingState(*this);
}

void Game::StartNewGame() {
    ChangeState(new FieldCreatingState(*this));
    is_running = true;
    current_state->DoStateJob(); // field creating state
    current_state->DoStateJob(); // ship initialization state
    current_state->DoStateJob(); // ship placement state
}

void Game::Play() {
    is_running = true;
    output.log_msg("Press [l] to load saved game");
    if (input.InputAction() == action::LOAD) {
        Load();
    }
    else {
        StartNewGame();
    }

}

void Game::Load() {
    output.log_msg("Enter save file name");
    current_state->load(input.InputString());
    this->ChangeState(new BattleState(*this));
}


void Game::Save() {
    output.log_msg("Enter save file name");
    current_state->save(input.InputString());
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

void Game::PlayerAttack() {
    auto res = dynamic_cast<BattleState*>(current_state);
    if (res) {
        res->PlayerMove();
    }
}

void Game::BotAttack() {
    auto res = dynamic_cast<BattleState*>(current_state);
    if (res) {
        res->BotMove();
    }
}

void Game::ApplyAbility() {
    auto res = dynamic_cast<BattleState*>(current_state);
    if (res) {
        res->UseSpell();
    }
}

bool Game::IsBotTurn() {
    auto res = dynamic_cast<BattleState*>(current_state);
    return res->GetTurn() == Turn::BOT;
}

void Game::CheckGameState() {
    if (is_running && bot.SManager.getCurrentShipAmount() == 0) {
        output.log_msg("You've win the game");
        output.log_msg("Do you want to start next round?");
        output.log_msg("Press [e] to start or press any key to exit");

        if (input.InputAction() == action::PRIMARY_ACTION) {
            auto res = dynamic_cast<BattleState*>(current_state);
            res->NextRound();
        }
        else {
            Quit();
        }
    }
    else if (is_running && player.SManager.getCurrentShipAmount() == 0) {
        output.log_msg("You've lost the game");
        output.log_msg("Do you want to start new game?");
        output.log_msg("Press [e] to start or press any key to exit");
        if (input.InputAction() == action::PRIMARY_ACTION) {
            StartNewGame();
        }
        else {
            Quit();
        }
    }
}