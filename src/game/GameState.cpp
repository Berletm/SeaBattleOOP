#include "GameState.hpp"
#include "Game.hpp"
#include "FileHandler.hpp"
#include <ostream>

HumanPlayer& GameState::Getplayer() {return game.player;}

Player& GameState::Getbot() {return game.bot;}

bool GameState::save(const std::string& file_name) {
    FileHandler file_handler(file_name);

    file_handler.open_for_write();

    file_handler.write(*this);

    return true;
}

ShipManager GameState::shipmanager_from_json(const json& save_file) {
    ShipManager ShipManager;

    const auto& ships = save_file["ships"];

    for (const auto& ship: ships) {
        Point coords = Point(ship["coords"][0], ship["coords"][1]);
        size_t size = ship["size"];
        bool status = ship["isPlaced"];
        Ship::Orientation orientation = ship["Orientation"];
        std::vector<Ship::ShipStates> segments = ship["segments"];
        ShipManager.addShip(Ship(coords, size, orientation, segments, status));
    }
    
    return ShipManager;
}

PlayGround GameState::field_from_json(const json& save_file) {
    PlayGround Field(save_file["size"]);

    const auto& cells = save_file["cells"];

    for (size_t y = 0; y < Field.getFieldSize(); ++y) {
        for (size_t x = 0; x < Field.getFieldSize(); ++x) {
            Ship* ship = nullptr;

            if (!cells[x][y]["ship"].is_null()) {
                Point coords = Point(cells[x][y]["ship"]["coords"][0], cells[x][y]["ship"]["coords"][1]);
                size_t size = cells[x][y]["ship"]["size"];
                bool status = cells[x][y]["ship"]["isPlaced"];
                Ship::Orientation orientation = cells[x][y]["ship"]["Orientation"];
                std::vector<Ship::ShipStates> segments = cells[x][y]["ship"]["segments"];
                ship = new Ship(coords, size, orientation, segments, status);
            }

            Field.change_cell({x, y}, ship, cells[x][y]["state"], cells[x][y]["segment idx"]);
        }
    }
    return Field;
}

AbilityManager GameState::abilitymanager_from_json(const json& save_file) {
    AbilityManager AManager;

    AManager.emptyAbilityQueue();

    for (const auto& ability: save_file) {
        AManager.getAbility(ability);
    }
    return AManager;
}

bool GameState::load(const std::string& file_name) {
    FileHandler file_handler(file_name);

    file_handler.open_for_read();

    file_handler.read(*this);

    return true;
}

std::ostream& operator<<(std::ostream& os, GameState& state) {
    json save_file;
    save_file["human player"] = state.Getplayer().to_json();
    save_file["bot player"] = state.Getbot().to_json();

    os << save_file.dump(4) << std::endl;

    return os;
}

std::istream& operator>>(std::istream& is, GameState& state) {
    json save_file;
    is >> save_file;

    auto player_shipmanager_data = save_file["human player"]["SManager"];
    auto player_field_data = save_file["human player"]["Field"];
    auto abilitymanager_data = save_file["human player"]["AbilityManager"];
    auto player_cursor_data = save_file["human player"]["Cursor"];
    auto player_buff_data = save_file["human player"]["Buff"];

    auto bot_shipmanager_data = save_file["bot player"]["SManager"];
    auto bot_field_data = save_file["bot player"]["Field"];
    auto bot_cursor_data = save_file["bot player"]["Cursor"];
    auto bot_buff_data = save_file["bot player"]["Buff"];

    state.Getplayer().SManager = std::move(state.shipmanager_from_json(player_shipmanager_data));
    state.Getplayer().Field = std::move(state.field_from_json(player_field_data));
    state.Getplayer().AManager = std::move(state.abilitymanager_from_json(abilitymanager_data));
    state.Getplayer().cursor = std::move(Point(player_cursor_data[0], player_cursor_data[1]));
    state.Getplayer().double_damage_buff = player_buff_data;

    state.Getbot().SManager = std::move(state.shipmanager_from_json(bot_shipmanager_data));
    state.Getbot().Field = std::move(state.field_from_json(bot_field_data));
    state.Getbot().cursor = std::move(Point(bot_cursor_data[0], bot_cursor_data[1]));
    state.Getbot().double_damage_buff = bot_buff_data;

    return is;
}