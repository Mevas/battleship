#include "../include/ShipFactory.h"

ShipFactory::ShipFactory(Board &board) : board(board) {}

Ship *ShipFactory::createShip(ShipTypes type) {
    switch(type) {
        case DESTROYER:
            return new Ship(&board, Cardinals::NORTH, 2);
        case SUBMARINE:
        case CRUISER:
            return new Ship(&board, Cardinals::NORTH, 3);
        case BATTLESHIP:
            return new Ship(&board, Cardinals::NORTH, 4);
        case CARRIER:
            return new Ship(&board, Cardinals::NORTH, 5);
    }
}
