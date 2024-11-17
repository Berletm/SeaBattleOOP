cmake_minimum_required(VERSION 3.21)

project(SeaBattle)

if(CMAKE_EXPORT_COMPILE_COMMANDS)
    set(CMAKE_CXX_STANDARD_INCLUDE_DIRECTORIES ${CMAKE_CXX_IMPLICIT_INCLUDE_DIRECTORIES})
endif()

add_executable(${PROJECT_NAME} main.cpp)

include_directories(SeaBattle src)

add_subdirectory(src)

find_package(nlohmann_json 3.2.0 REQUIRED)

target_link_libraries(${PROJECT_NAME} nlohmann_json::nlohmann_json)