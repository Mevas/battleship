#ifndef BATTLESHIP_SHIP_H
#define BATTLESHIP_SHIP_H

#include <vector>
#include <set>
#include "Coordinate.h"

class Board;

class Ship {
public:
    Ship(std::vector<Coordinate> coords, Board *board);

    virtual ~Ship();

    void update();

    void render(sf::RenderTarget *target, Coordinate hoveredCell);

    const std::vector<Coordinate> &getCoords() const;

    bool isDestroyed();

    void markHit(Coordinate cell);

private:
    std::vector<Coordinate> coords;
    std::set<Coordinate> hitCoords;
    int length;

    Board *board;
};


#endif //BATTLESHIP_SHIP_H
