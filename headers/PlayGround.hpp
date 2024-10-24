#ifndef PLAYGROUND_HPP_
#define PLAYGROUND_HPP_
<<<<<<< HEAD
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
=======
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
>>>>>>> lb2
        }

        Cell(const Cell& other): state(other.state), ship(other.ship), segment_idx(other.segment_idx) {
        }

<<<<<<< HEAD
        void ChangeState(CellStates new_state, Ship* ship_ptr = nullptr, size_t segment_idx = -1) {
            this->state = new_state;
            if (ship_ptr) {
                this->ship = ship_ptr;
                this->segment_idx = segment_idx;
            }
        }
=======
        void ChangeState(CellStates new_state, Ship* ship_ptr = nullptr, size_t segment_idx = -1);
>>>>>>> lb2

        CellStates GetState() const {
            return this->state;
        }

<<<<<<< HEAD
        Ship::ShipStates GetSegmentHP() const {
=======
        inline Ship::ShipStates GetSegmentHP() const {
>>>>>>> lb2
            return ship->getSegment(segment_idx);
        }
        
        inline void ChangeSegmentState() {
            ship->changeSegmentState(segment_idx);
        }

<<<<<<< HEAD
        Ship* GetShip() {
=======
        Ship* GetShip() const{
>>>>>>> lb2
            return ship;
        }

    private:
        CellStates state;
        Ship* ship;
        size_t segment_idx;
    };

    size_t size;
<<<<<<< HEAD
    vector<vector<Cell>> cells; 
    size_t miss_number;
    size_t hits_number;

    bool isInPlayGround(Point p) const;
=======
    std::vector<std::vector<Cell>> cells; 
    size_t miss_number;
    size_t hits_number;
    bool double_damage_buff;
>>>>>>> lb2

    bool checkCollision(Point p, Ship& ship, Ship::Orientation orientation);

public:
<<<<<<< HEAD
    explicit PlayGround(size_t size = 8): size(size), cells(size, vector<Cell>(size)), miss_number(0), hits_number(0) {
        if (size > 15) {
            throw invalid_argument("Too big playground size!\n");
=======
    explicit PlayGround(size_t size = 8): size(size), cells(size, std::vector<Cell>(size)), miss_number(0), hits_number(0), double_damage_buff(false) {
        if (size > 20) {
            throw GameException("Too big playground size!\n");
>>>>>>> lb2
        }
    }

    //copy constructor
<<<<<<< HEAD
    PlayGround(const PlayGround& other): size(other.size), cells(other.cells.size(), vector<Cell>(other.cells.size())) {
=======
    PlayGround(const PlayGround& other): size(other.size), cells(other.cells.size(), std::vector<Cell>(other.cells.size())) {
>>>>>>> lb2
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
<<<<<<< HEAD
        swap(size, other.size);
        swap(cells, other.cells);
=======
        std::swap(size, other.size);
        std::swap(cells, other.cells);
>>>>>>> lb2
    }

    PlayGround& operator= (PlayGround&& other) {
        if (this != &other) {
<<<<<<< HEAD
            swap(size, other.size);
            swap(cells, other.cells);
=======
            std::swap(size, other.size);
            std::swap(cells, other.cells);
>>>>>>> lb2
        }
        return *this;
    }

    void PlaceShip(Ship* ship, Point position, Ship::Orientation orientation);

    void DisplayPlayground();
<<<<<<< HEAD

    void Attack(Point p);
    
=======
    
    void DisplayPlaygroundWithOutFogOfWar();

    void Attack(Point p, AbilityManager& AbilityManager);

    void getDoubleDamageBuff();
    
    bool isUnderBuff();

    void dispellBuff();

    CellStates getCellState(Point p) const;

    size_t getFieldSize() const;

    bool isInPlayGround(Point p) const;
>>>>>>> lb2
};
#endif