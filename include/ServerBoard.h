//
// Created by tudor on 5/11/2020.
//

#ifndef BATTLESHIP_SERVERBOARD_H
#define BATTLESHIP_SERVERBOARD_H

#include <stack>
#include "Coordinate.h"
#include "Constants.h"

class ServerShip;

class ServerBoard {
public:
    explicit ServerBoard();

    virtual ~ServerBoard();

    void addShip(Coordinate head, unsigned length, Cardinals direction);

    HitTypes attack(Coordinate cell);

    unsigned getShipCount()
    {
        return this->shipCount;
    }

private:
    unsigned shipCount;
    std::vector<ServerShip *> ships;
};

#endif //BATTLESHIP_SERVERBOARD_H
