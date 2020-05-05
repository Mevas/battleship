#ifndef BATTLESHIP_BOARD_H
#define BATTLESHIP_BOARD_H


#include "Ship.h"

class Board {
public:
    Board();

    void addShip(Coordinate head, unsigned length, unsigned rotation);

    unsigned attack();

private:
    unsigned size;
    std::vector<Ship> ships;
};


#endif //BATTLESHIP_BOARD_H
