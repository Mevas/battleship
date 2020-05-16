#ifndef BATTLESHIP_SHIPFACTORY_H
#define BATTLESHIP_SHIPFACTORY_H

#include "Ship.h"
#include "Constants.h"

class ShipFactory {
public:
    ShipFactory(Board &board);

    Ship *createShip(ShipTypes type);

private:
    Board &board;
};


#endif //BATTLESHIP_SHIPFACTORY_H
