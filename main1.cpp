#include <iostream>
#include <vector>
#include <memory>
#include <random>
#include <unistd.h>
#include "Ship.hpp"
#include "ShipManager.hpp"
#include "PlayGround.hpp"
using namespace std;


int main() {
    try {
        random_device rd;
        mt19937 gen(rd());
        uniform_int_distribution<size_t> dist(0, 9);
        vector<size_t> sizes = {1, 2, 3, 4};
        ShipManager Manager(sizes.size(), sizes);
        PlayGround field(10);
        field.PlaceShip(Manager.getShip(), {0, 0}, Ship::Orientation::horizontal);
        field.PlaceShip(Manager.getShip(),  {2, 2}, Ship::Orientation::vertical);
        field.PlaceShip(Manager.getShip(), {5, 6}, Ship::Orientation::horizontal);
        field.PlaceShip(Manager.getShip(), {1, 5}, Ship::Orientation::vertical);
        for (size_t i = 0; i < 10; ++i) {
            field.Attack({dist(gen), dist(gen)});
            field.DisplayPlayground();
            sleep(1);
            system("clear");
        }
        field.DisplayPlayground();
        Manager.printShips();
    }
    catch(const invalid_argument& e) {
        cout << e.what() << "\n";
    }

    return 0;
}