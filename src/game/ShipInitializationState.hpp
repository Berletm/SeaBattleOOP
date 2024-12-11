#ifndef SHIP_INITIALIZATION_STATE_HPP_
#define SHIP_INITIALIZATION_STATE_HPP_

#include "other/ShipsData.hpp"
#include "GameState.hpp"

#include <vector>
#include <cstddef>

class Game;

class ShipInitializationState final: public GameState {
private:
    static constexpr size_t freedom_coefficient = 0;
    std::vector<size_t> ship_sizes;
    ssize_t points;
    size_t ship_counter;
    ShipData data;
public:
    explicit ShipInitializationState(Game& game) noexcept(true);

    void DoStateJob();

    size_t convert_ship_size_to_points(size_t size);
};

#endif