#ifndef GAME_STATE_HPP_
#define GAME_STATE_HPP_

#include "GameInput.hpp"

class GameState {
protected:
    Game& game;

    HumanPlayer& Getplayer();
    Player& Getbot();
public:
    friend std::ostream& operator<<(std::ostream& os, GameState& state);
    friend std::istream& operator>>(std::istream& is, GameState& state);
    

    GameState(Game& game): game(game) {}
    virtual void operator<<(GameInput msg) = 0;
    virtual ~GameState() {};

    ShipManager shipmanager_from_json(const json& save_file);
    PlayGround field_from_json(const json& save_file, ShipManager& SManager);
    AbilityManager abilitymanager_from_json(const json& save_file);

    bool save(const std::string& file_name);
    bool load(const std::string& file_name);
};

std::ostream& operator<<(std::ostream& os, GameState& state);
std::istream& operator>>(std::istream& is, GameState& state);

#endif