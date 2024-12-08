#include "CLIGameOutput.hpp"
#include "./other/PlayGround.hpp"

CLIGameOutput& CLIGameOutput::instance() {
    static CLIGameOutput self;
    return self;
}

void CLIGameOutput::ability_msg(std::string_view ability_name) {
    if (ability_name == "Scanner") {
        std::cout << "Input area to be scanned" << std::endl;
    }
    if (ability_name == "DoubleDamage") {
        std::cout << "Next attack will deal double damage" << std::endl;
    }
    if (ability_name == "RocketBarrage") {
        std::cout << "Rocket barrage attacked ship" << std::endl;
    }
}

void CLIGameOutput::ability_msg(std::string_view ability_name, bool flag) {
    if (flag) {
        if (ability_name == "Scanner") {
            std::cout << "Scanner found ship there" << std::endl;
        }
        if (ability_name == "DoubleDamage") {
            std::cout << "Double damage buff applied" << std::endl;
        }
    }
    else {
        if (ability_name == "Scanner") {
            std::cout << "Scanner did not find any ship here" << std::endl;
        }
        if (ability_name == "DoubleDamage") {
            std::cout << "Double damage buff expired" << std::endl;
        }
    }
}

void CLIGameOutput::point_msg(const Point& p) {
    std::cout << "x = " << p.x << " y = " << p.y << std::endl;
}

void CLIGameOutput::log_msg(std::string_view msg) { 
    std::cout << msg << std::endl;
}

void CLIGameOutput::clear() {
    system("clear");
}

void CLIGameOutput::draw_field_without_fog(PlayGround& field, Point cursor, Point cursor_end, bool flag) {
    clear();

    cursor_end = {cursor_end.x + cursor.x, cursor_end.y + cursor.y};

    for (size_t y = 0; y < field.size ; ++y) {
        for (size_t x = 0; x < field.size; ++x) {
            if (flag && x >= cursor.x && x < cursor_end.x && y >= cursor.y && y < cursor_end.y) {
                std::cout << MAGENTA_SQUARE;
            }
            else {
                if (x == cursor.x && y == cursor.y) {
                    std::cout << MAGENTA_SQUARE;
                }
                else if (field.cells[x][y].GetState() == CellStates::unknown && !field.cells[x][y].GetShip()) {
                    std::cout << WHITE_SQUARE;
                }
                else if (field.cells[x][y].GetState() == CellStates::empty) {
                    std::cout << BLUE_SQUARE;
                }
                else if (field.cells[x][y].GetShip()) {
                    std::cout << convert_number_to_color(size_t(field.cells[x][y].GetSegmentHP()));
                }
            }
        }
        std::cout << '\n';
    }
}

const std::string CLIGameOutput::convert_number_to_color(size_t n) const { 
    switch(n) {
        case 0: {
            return RED_SQUARE;
        }
        case 1: {
            return ORANGE_SQUARE;
        }
        case 2: {
            return GREEN_SQUARE;
        }
    }
    return WHITE_SQUARE;
}

void CLIGameOutput::draw_field(PlayGround& field, Point cursor, Point cursor_end, bool flag) {
    clear();

    cursor_end = {cursor_end.x + cursor.x, cursor_end.y + cursor.y};

    for (size_t y = 0; y < field.size; ++y) {
        for (size_t x = 0; x < field.size; ++x) {
            if (flag && x >= cursor.x && x < cursor_end.x && y >= cursor.y && y < cursor_end.y) {
                std::cout << MAGENTA_SQUARE;
            }
            else {
                if (x == cursor.x && y == cursor.y) {
                    std::cout << MAGENTA_SQUARE; 
                }
                else if (field.cells[x][y].GetState() == CellStates::unknown) {
                    std::cout << WHITE_SQUARE;
                }
                else if (field.cells[x][y].GetState() == CellStates::empty) {
                    std::cout << BLUE_SQUARE;
                }
                else if (field.cells[x][y].GetState() == CellStates::ship) {
                    std::cout << convert_number_to_color(size_t(field.cells[x][y].GetSegmentHP()));
                }
            }
        }
        std::cout << '\n';
    }
}

void CLIGameOutput::display_buff(bool flag) const {
    if (flag) {
        std::cout << "active: double damage buff" << std::endl;
    }
}