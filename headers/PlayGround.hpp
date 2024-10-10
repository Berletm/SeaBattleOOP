#ifndef PLAYGROUND_HPP_
#define PLAYGROUND_HPP_
using namespace std;
#include <vector>
#include "Ship.hpp"
#include "ShipManager.hpp"

class PlayGround{
private:
    enum CellStates {empty, unknown, ship};
    class Cell {
    public:
        Cell(CellStates state = CellStates::unknown): state(state), ship(nullptr), segment_idx(-1){
        }

        Cell(const Cell& other): state(other.state), ship(other.ship), segment_idx(other.segment_idx) {
        }

        void ChangeState(CellStates new_state) {
            this->state = new_state;
        }

        CellStates GetState() const {
            return this->state;
        }
    private:
        CellStates state;
        Ship* ship;
        size_t segment_idx;
    };

    size_t size;
    vector<vector<Cell>> cells; 
    size_t miss_number;
    size_t hits_number;

    bool isInPlayGround(Point p) const;

    bool checkCollision(Point p, Ship& ship, Ship::Orientation orientation);

public:
    explicit PlayGround(size_t size = 8): size(size), cells(size, vector<Cell>(size)), miss_number(0), hits_number(0) {
        if (size > 15) {
            throw invalid_argument("Too big playground size!\n");
        }
    }

    //copy constructor
    PlayGround(const PlayGround& other): size(other.size), cells(other.cells.size(), vector<Cell>(other.cells.size())) {
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
        swap(size, other.size);
        swap(cells, other.cells);
    }

    PlayGround& operator= (PlayGround&& other) {
        if (this != &other) {
            swap(size, other.size);
            swap(cells, other.cells);
        }
        return *this;
    }

    void PlaceShip(Ship* ship, Point position, Ship::Orientation orientation);

    void DisplayPlayground();

    void DisplayPlayground(ShipManager& Manager);

    void Attack(Point p, ShipManager& Manager);
    
};
#endif