#include "Player.hpp"
#include <nlohmann/json.hpp>

using json = nlohmann::json;

json Player::to_json() {
    json save_file;
    save_file["Field"] = Field.to_json();
    save_file["SManager"] = SManager.to_json();
    save_file["Cursor"] = {cursor.x, cursor.y};
    save_file["Buff"] = double_damage_buff;
    return save_file;
}