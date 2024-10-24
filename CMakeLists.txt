cmake_minimum_required(VERSION 3.21)

project(SeaBattle)

<<<<<<< HEAD
set(SOURCE main1.cpp src/PlayGround.cpp src/Ship.cpp src/ShipManager.cpp)

include_directories(headers)

add_executable(${PROJECT_NAME} ${SOURCE})
=======
if(CMAKE_EXPORT_COMPILE_COMMANDS)
    set(CMAKE_CXX_STANDARD_INCLUDE_DIRECTORIES ${CMAKE_CXX_IMPLICIT_INCLUDE_DIRECTORIES})
endif()

set(SOURCE main1.cpp src/AbilityManager.cpp src/Scanner.cpp src/DoubleDamage.cpp 
    src/RocketBarrage.cpp src/PlayGround.cpp src/Ship.cpp src/ShipManager.cpp)

include_directories(headers)

find_package(SFML 2.6.1 COMPONENTS graphics window system REQUIRED)

add_executable(${PROJECT_NAME} ${SOURCE})

target_link_libraries(${PROJECT_NAME} sfml-graphics sfml-window sfml-system)
>>>>>>> lb2
