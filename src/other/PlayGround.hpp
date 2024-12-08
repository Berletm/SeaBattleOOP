#ifndef PLAYGROUND_HPP_
#define PLAYGROUND_HPP_

#include <vector>
#include <nlohmann/json.hpp>
#include <fstream>
#include "ability/AbilityManager.hpp"
#include "Ship.hpp"

using json = nlohmann::json;

enum class CellStates {empty, unknown, ship};
class PlayGround{
private:
    friend class CLIGameOutput;
    class Cell {
    friend class PlayGround;
    public:
        Cell(CellStates state = CellStates::unknown): state(state), ship(nullptr), segment_idx(0) 
        {}

        Cell(const Cell& other): state(other.state), ship(other.ship), segment_idx(other.segment_idx) {}

        void ChangeState(CellStates new_state, Ship* ship_ptr = nullptr, size_t segment_idx = 0);

        CellStates GetState() const {
            return this->state;
        }

        inline Ship::ShipStates GetSegmentHP() const {
            return ship->getSegment(segment_idx);
        }
        
        inline void ChangeSegmentState() {
            ship->changeSegmentState(segment_idx);
        }

        Ship* GetShip() const{
            return ship;
        }

        json to_json() const {
            if (ship) {
                return json{
                    {"state", state},
                    {"ship", ship->to_json()},
                    {"segment idx", segment_idx}
                };
            }
            else {
                return json{
                    {"state", state},
                    {"ship", nullptr},
                    {"segment idx", segment_idx}
                };
            }
        }

    private:
        CellStates state;
        Ship* ship;
        size_t segment_idx;
    };

    size_t size;    
    std::vector<std::vector<Cell>> cells;

    bool checkCollision(Point p, Ship& ship, Ship::Orientation orientation);

public:
    explicit PlayGround(size_t size = 8): size(size), cells(size, std::vector<Cell>(size)) {
        if (size > 20) {
            throw GameException("Too big playground size!\n");
        }
        if (size <= 1) {
            throw GameException("Too shmall playground size\n");
        }
    }

    //copy constructor
    PlayGround(const PlayGround& other): size(other.size), cells(other.cells.size(), std::vector<Cell>(other.cells.size())) {
        for (size_t i = 0; i < other.cells.size(); ++i) {
            cells[i] = other.cells[i];
        }
    }

    PlayGround& operator= (const PlayGround& other) {
        if (this != &other) {
            this->size = other.size;
            cells = other.cells;
        }
        return *this;
    }

    //move constructor
    PlayGround(PlayGround&& other) noexcept: size(0) {
        std::swap(size, other.size);
        std::swap(cells, other.cells);
    }

    PlayGround& operator= (PlayGround&& other) {
        if (this != &other) {
            std::swap(size, other.size);
            std::swap(cells, other.cells);
        }
        return *this;
    }

    void PlaceShip(Ship* ship, Point position, Ship::Orientation orientation);

    void DisplayPlayground();
    
    void DisplayPlaygroundWithOutFogOfWar();

    bool Attack(Point p);

    CellStates getCellState(Point p) const;

    size_t getFieldSize() const;

    bool isInPlayGround(Point p) const;

    Ship* getShip(const Point& p) {
        return cells[p.x][p.y].GetShip();
    }

    json to_json() const {
        json save_file;
        save_file["size"] = size;
        json cells = json::array();
        for (size_t x = 0; x < size; ++x) {
            json j_row = json::array();
            for (size_t y = 0; y < size; ++y) {
                j_row.push_back(this->cells[x][y].to_json());
            }
            cells.push_back(j_row);
        }
        save_file["cells"] = cells;
        return save_file;
    }

    void change_cell(Point p, Ship* ship, CellStates state, size_t segement_idx) {
        this->cells[p.x][p.y].ship = ship;
        this->cells[p.x][p.y].state = state;
        this->cells[p.x][p.y].segment_idx = segement_idx;
    }

    const size_t get_current_ship_amount();
};
#endif