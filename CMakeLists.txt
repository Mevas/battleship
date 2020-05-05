cmake_minimum_required(VERSION 3.16)
project(battleship)

set(CMAKE_CXX_STANDARD 20)

# SFML
## If you want to link SFML statically
set(SFML_STATIC_LIBRARIES TRUE)

## In most cases better set in the CMake cache
set(SFML_DIR "./lib/SFML/lib/cmake/SFML")
find_package(SFML 2.5 COMPONENTS system window graphics network audio REQUIRED)

# Define sources and executable
set(EXECUTABLE_NAME "battleship")
add_executable(${EXECUTABLE_NAME} main.cpp Game.cpp Game.h)


target_link_libraries(battleship sfml-system sfml-window sfml-graphics sfml-network sfml-audio)
