#ifndef SHIPS_DATA_HPP_
#define SHIPS_DATA_HPP_

#include <map>

enum class ShipType {vedette = 1, destroyer, cruiser, battleship};

using ShipData = std::map<ShipType, size_t>;

inline void DisplayData(const ShipData& data) {
    for (const auto& pair : data) {
        std::cout << "Тип корабля: " << size_t(pair.first) << ", Размер корабля: " << pair.second << std::endl;
    }
}

#endif