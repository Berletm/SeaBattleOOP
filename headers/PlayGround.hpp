#ifndef PLAYGROUND_HPP_
#define PLAYGROUND_HPP_
#include <vector>
#include "AbilityManager.hpp"
#include "Ship.hpp"
#include "GameException.hpp"

enum class CellStates {empty, unknown, ship};
class PlayGround{
private:
    class Cell {
    public:
        Cell(CellStates state = CellStates::unknown): state(state), ship(nullptr){
        }

        Cell(const Cell& other): state(other.state), ship(other.ship), segment_idx(other.segment_idx) {
        }

        void ChangeState(CellStates new_state, Ship* ship_ptr = nullptr, size_t segment_idx = -1);

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

    private:
        CellStates state;
        Ship* ship;
        size_t segment_idx;
    };

    size_t size;
    std::vector<std::vector<Cell>> cells; 
    size_t miss_number;
    size_t hits_number;
    bool double_damage_buff;

    bool checkCollision(Point p, Ship& ship, Ship::Orientation orientation);

public:
    explicit PlayGround(size_t size = 8): size(size), cells(size, std::vector<Cell>(size)), miss_number(0), hits_number(0), double_damage_buff(false) {
        if (size > 20) {
            throw GameException("Too big playground size!\n");
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

    void Attack(Point p, AbilityManager& AbilityManager);

    void getDoubleDamageBuff();
    
    bool isUnderBuff();

    void dispellBuff();

    CellStates getCellState(Point p) const;

    size_t getFieldSize() const;

    bool isInPlayGround(Point p) const;
};
#endif