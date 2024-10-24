cmake_minimum_required(VERSION 3.21)

project(SeaBattle)

set(SOURCE main1.cpp src/PlayGround.cpp src/Ship.cpp src/ShipManager.cpp)

include_directories(headers)

add_executable(${PROJECT_NAME} ${SOURCE})
