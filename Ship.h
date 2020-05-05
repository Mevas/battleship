#ifndef BATTLESHIP_SHIP_H
#define BATTLESHIP_SHIP_H

#include <vector>
#include "Coordinate.h"

class Ship {
public:
    Ship(std::vector<Coordinate> coords);
    virtual ~Ship();
private:
    std::vector<Coordinate> coords;
    std::vector<Coordinate> hitCoords;
    int length;
};


#endif //BATTLESHIP_SHIP_H
