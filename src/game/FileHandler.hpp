#ifndef FILE_HANDLER_HPP_
#define FILE_HANDLER_HPP_

#include <nlohmann/json.hpp>
#include <fstream>
#include "GameState.hpp"
#include "./game/game utils/CLIGameInput.hpp"

using json = nlohmann::json;

class FileHandler {
private:
    const std::string& filename;
    std::ifstream input_file;
    std::ofstream output_file;
public:
    FileHandler(const std::string& filename);

    void open_for_read();

    void open_for_write();

    void read(GameState& current_state);

    void read(CLIGameInput& game_input);

    void write(GameState& current_state);

    void close_read();

    void close_write();

    ~FileHandler();
};

#endif