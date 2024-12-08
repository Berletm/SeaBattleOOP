#include "FileHandler.hpp"
#include <exception>

FileHandler::FileHandler(const std::string& filename): filename(filename) {}

void FileHandler::open_for_read() {
    input_file.open(filename);
    
    if (!input_file.is_open()) {
        throw std::runtime_error("Failed openning file for reading\n");
    }
}

void FileHandler::open_for_write() {
    output_file.open(filename);

    if (!output_file.is_open()) {
        throw std::runtime_error("Failed openning file for writing\n");
    }
}

void FileHandler::read(GameState& current_state) {
    if (input_file.is_open()) {
        input_file >> current_state;
    }
    else {
        throw std::runtime_error("File for reading is not open\n");
    }
}

void FileHandler::write(GameState& current_state) {
    if (output_file.is_open()) {
        output_file << current_state;
    }
    else {
        throw std::runtime_error("File for writing is not open\n");
    }
}

void FileHandler::read(CLIGameInput& game_input) { 
    if (input_file.is_open()) {
        input_file >> game_input;
    }
    else {
        throw std::runtime_error("File for writing is not open\n");
    }
}

void FileHandler::close_read() {
    if (input_file.is_open()) {
        input_file.close();
    }
}

void FileHandler::close_write() {
    if (output_file.is_open()) {
        output_file.close();
    }
}

FileHandler::~FileHandler() {
    close_read();
    close_write();
}