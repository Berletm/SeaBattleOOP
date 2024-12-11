#ifndef GAME_HPP_
#define GAME_HPP_

#include <nlohmann/json.hpp>
#include "GameState.hpp"
#include "game utils/CLIGameInput.hpp"
#include "./other/HumanPlayer.hpp"

using json = nlohmann::json;

class Game {
private:
    bool is_running;

protected:
    friend class GameState;
    friend class FieldCreatingState;
    friend class ShipInitializationState;
    friend class ShipPlacementState;
    friend class BattleState;

    template <typename T1, typename T2>
    friend class GameControl;

    template <typename T>
    friend class GameRenderer;

    CLIGameInput input = CLIGameInput::instance();

    CLIGameOutput output = CLIGameOutput::instance();
    
    Player bot;
    HumanPlayer player;
    GameState* current_state;

    
public:
    explicit Game();
    
    void StartNewGame();
    void Play();
    void Load();
    void Save();
    void PlayerAttack();
    void BotAttack();
    void ApplyAbility();
    bool IsBotTurn();
    void CheckGameState();
    void ChangeState(GameState* new_state);
    bool IsRunning();
    void Quit();

    ~Game();
};

#endif