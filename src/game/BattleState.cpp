#include "BattleState.hpp"
#include "ShipPlacementState.hpp"
#include "Game.hpp"
#include <chrono>
#include <random>

BattleState::BattleState(Game& game) noexcept(true): GameState(game) {
    game.output.log_msg("Now start battle!");
    current_turn = Turn::HUMAN;
}

void BattleState::SwitchTurn() {
    current_turn = (current_turn == Turn::BOT) ? Turn::HUMAN: Turn::BOT;
}

void BattleState::NextRound() {
    Getbot().Field = std::move(PlayGround(Getbot().Field.getFieldSize()));
    Getbot().SManager = std::move(ShipManager(Getbot().SManager.getShipAmount(), Getbot().SManager.getShipSizes()));
    ShipPlacementState sps(game);
    sps.BotShipPlacement();
}

 void BattleState::PlayerMove() { 
    while (game.input.InputXY(Getplayer().cursor)) {
        game.output.clear();
        game.output.draw_fields(game.player.Field, game.bot.Field, game.player.cursor);
        game.output.display_buff(game.player.double_damage_buff);
    }
    try {
        Getplayer().attack(Getbot());
    }
    catch (const OutOfFieldAttackException& e) {
        game.output.log_msg(e.what());
    }
    SwitchTurn();
 }

 void BattleState::BotMove() {
    std::mt19937 rnd(std::chrono::steady_clock::now().time_since_epoch().count());
    std::uniform_int_distribution<size_t> dist(0, Getbot().Field.getFieldSize() - 1);

    Getbot().cursor = {dist(rnd), dist(rnd)};
    Getplayer().Field.Attack(Getbot().cursor);
    SwitchTurn();
 }

 void BattleState::UseSpell() { 
    try {
        Getplayer().applyAbility(Getbot());
    }
    catch (const NoAbilityException& e) {
        game.output.log_msg(e.what());
    }
 }

 void BattleState::DoStateJob() {
    
 }

 Turn BattleState::GetTurn() {
    return current_turn;
 }