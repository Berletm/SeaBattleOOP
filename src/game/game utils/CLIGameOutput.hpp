#ifndef CLI_GAME_OUTPUT_HPP_
#define CLI_GAME_OUTPUT_HPP_

#include <string_view>
#include <iostream>
#include "./other/Point.hpp"

class GameState;
class PlayGround;

class CLIGameOutput {
private:
    CLIGameOutput() = default;
    const std::string BLUE_SQUARE = "\033[44m  \033[0m";
    const std::string WHITE_SQUARE = "\033[47m  \033[0m";
    const std::string RED_SQUARE = "\033[41m  \033[0m";
    const std::string ORANGE_SQUARE = "\033[48;5;214m  \033[0m";
    const std::string GREEN_SQUARE = "\033[42m  \033[0m";
    const std::string MAGENTA_SQUARE = "\033[45m  \033[0m";
public:
    static CLIGameOutput& instance();
    void ability_msg(std::string_view ability_name);
    void ability_msg(std::string_view ability_name, bool flag);
    void log_msg(std::string_view msg);
    void init_msg(GameState* current_state);
    void point_msg(const Point& p);
    void exception_msg(std::string exception);
    void draw_field_without_fog(PlayGround& field, Point cursor, Point cursor_end = {0, 0}, bool flag = false);
    void draw_field(PlayGround& field, Point cursor, Point cursor_end = {0, 0}, bool flag = false);
    void draw_field_ship_placement(PlayGround& field, Point cursor, Point cursor_end, bool flag = false);
    const std::string convert_number_to_color(size_t n) const;
    void display_buff(bool flag) const;
    void clear();
};


#endif