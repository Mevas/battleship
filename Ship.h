#ifndef BATTLESHIP_SHIP_H
#define BATTLESHIP_SHIP_H

#include <vector>
#include "Coordinate.h"

#include "Board.h"

class Board;

class Ship {
public:
    Ship(std::vector<Coordinate> coords, Board *parent);

    virtual ~Ship();

    void update();

    void render(sf::RenderTarget *target);

private:
    std::vector<Coordinate> coords;
    std::vector<Coordinate> hitCoords;
    int length;

    Board *parent;
};


#endif //BATTLESHIP_SHIP_H
