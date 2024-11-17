#include "BattleState.hpp"
#include "ShipPlacementState.hpp"
#include <chrono>

void BattleState::operator<<(GameInput msg) {
    std::mt19937 rnd(std::chrono::steady_clock::now().time_since_epoch().count());
    std::uniform_int_distribution<size_t> dist(0, Getbot().Field.getFieldSize() - 1);

    while (game.IsRunning() && Getplayer().SManager.getCurrentShipAmount() && Getbot().SManager.getCurrentShipAmount()) {
        if (current_turn == Turn::HUMAN) {
            auto action = msg.InputAction();
            if (action == GameInput::action::PRIMARY_ACTION) {
                //system("clear");
                while (msg.InputXY(Getplayer().cursor)) {
                    system("clear");
                    std::cout << "x = " << Getplayer().cursor.x << " y = " << Getplayer().cursor.y << std::endl;
                }
                try {
                    Getbot().Field.Attack(Getplayer().cursor);
                    system("clear");
                    Getbot().Field.DisplayPlayground();
                }
                catch (const OutOfFieldAttackException& e) {
                    e.what();
                    continue;
                }
            }
            else if (action == GameInput::action::SECONDARY_ACTION) {
                Getplayer().applyAbility(Getbot());
            }
            else if (action == GameInput::action::SAVE) {
                std::cout << "Input save file name" << std::endl;
                std::string file_name = "save1.json";
                //std::cin >> file_name;
                save(file_name);
                game.Quit();
            }
            else if (action == GameInput::action::LOAD) {
                std::cout << "Input save file name" << std::endl;
                std::string file_name;
                std::cin >> file_name;
                load(file_name);
                continue;
            }
            else {
                std::cout << "try again" << std::endl;
                continue;
            }
            SwitchTurn();
        }
        else {
            Getbot().cursor = {dist(rnd), dist(rnd)};
            Getplayer().Field.Attack(Getbot().cursor);
            SwitchTurn();
        }
    }
    if (game.IsRunning() && Getplayer().SManager.getCurrentShipAmount()) {
        NextRound();
    }
    else {
        game.Quit();
    }
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