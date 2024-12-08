#include "GameState.hpp"
#include "Game.hpp"
#include "FileHandler.hpp"
#include "other/Player.hpp"
#include "other/HumanPlayer.hpp"
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
        bool status = false;
        Ship::Orientation orientation = Ship::Orientation(ship["Orientation"]);
        std::vector<Ship::ShipStates> segments;
        for (auto& segment: ship["segments"]) {
            segments.push_back(Ship::ShipStates(segment));
        }
        Ship s(coords, size, orientation, segments, status);
        ShipManager.addShip(s);
    }
    
    return ShipManager;
}

PlayGround GameState::field_from_json(const json& save_file, ShipManager& SManager) {
    PlayGround Field(save_file["size"]);

    const auto& cells = save_file["cells"];

    for (size_t x = 0; x < Field.getFieldSize(); ++x) {
        for (size_t y = 0; y < Field.getFieldSize(); ++y) {
            Ship* ship = nullptr;

            Field.change_cell({x, y}, ship, CellStates(cells[x][y]["state"]), size_t(cells[x][y]["segment idx"]));
        }
    }

    while (Ship* ship = SManager.getShip()) {
        Field.PlaceShip(ship, ship->getCoords(), ship->getOrientation());
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
    state.Getplayer().Field = std::move(state.field_from_json(player_field_data, state.Getplayer().SManager));
    state.Getplayer().AManager = state.abilitymanager_from_json(abilitymanager_data);
    state.Getplayer().cursor = Point(player_cursor_data[0], player_cursor_data[1]);
    state.Getplayer().double_damage_buff = player_buff_data;

    state.Getbot().SManager = std::move(state.shipmanager_from_json(bot_shipmanager_data));
    state.Getbot().Field = std::move(state.field_from_json(bot_field_data, state.Getbot().SManager));
    state.Getbot().cursor = Point(bot_cursor_data[0], bot_cursor_data[1]);
    state.Getbot().double_damage_buff = bot_buff_data;

    return is;
}