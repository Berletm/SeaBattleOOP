#ifndef GAME_EXCEPTION_HPP_
#define GAME_EXCEPTION_HPP_
#include <iostream>
#include <string>

class GameException: public std::exception {
public:
    GameException(const std::string& message): message(message){
    }

    const char* what() const noexcept override {
        return message.c_str();
    }
private: 
    std::string message;
};

class NoAbilityException: public std::exception {
public:
    NoAbilityException(const std::string& message): message(message){
    }

    const char* what() const noexcept override {
        return message.c_str();
    }
private:
    std::string message;
};

class CollisionException: public std::exception {
public:
    CollisionException(const std::string& message): message(message){
    }

    const char* what() const noexcept override {
        return message.c_str();
    }
private:
    std::string message;
};

class OutOfFieldAttackException: public std::exception {
public:
    OutOfFieldAttackException(const std::string& message): message(message){
    }

    const char* what() const noexcept override {
        return message.c_str();
    }
private:
    std::string message;
};

class WrongShipSizeException: public std::exception {
public:
    WrongShipSizeException(const std::string& message): message(message){
    }

    const char* what() const noexcept override {
        return message.c_str();
    }
private:
    std::string message;
};

class WrongShipAmountException: public std::exception {
public:
    WrongShipAmountException(const std::string& message): message(message){
    }

    const char* what() const noexcept override {
        return message.c_str();
    }
private:
    std::string message;
};


#endif