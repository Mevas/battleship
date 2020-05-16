cmake_minimum_required(VERSION 3.16)
project(battleship)

set(CMAKE_CXX_STANDARD 20)

# SFML
## If you want to link SFML statically
set(SFML_STATIC_LIBRARIES TRUE)

## In most cases better set in the CMake cache
set(SFML_DIR "lib/SFML/lib/cmake/SFML")
find_package(SFML 2.5 COMPONENTS system window graphics network audio REQUIRED)

# Define sources and executable
set(EXECUTABLE_NAME "battleship")
add_executable(${EXECUTABLE_NAME} main.cpp src/Server.cpp include/Server.h src/Client.cpp include/Client.h include/Constants.h src/Game.cpp include/Game.h src/State.cpp include/State.h src/GameState.cpp include/GameState.h src/Coordinate.cpp include/Coordinate.h src/Ship.cpp include/Ship.h src/Board.cpp include/Board.h src/Player.cpp include/Player.h src/Globals.cpp include/Globals.h src/Shadow.cpp include/Shadow.h include/ServerBoard.h src/ServerBoard.cpp include/ServerShip.h src/ServerShip.cpp src/MenuState.cpp include/MenuState.h src/Button.cpp include/Button.h src/Textbox.cpp include/Textbox.h src/ShipFactory.cpp include/ShipFactory.h)


target_link_libraries(battleship sfml-system sfml-window sfml-graphics sfml-network sfml-audio)

