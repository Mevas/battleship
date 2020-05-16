#ifndef BATTLESHIP_SHIP_H
#define BATTLESHIP_SHIP_H

#include <vector>
#include <set>
#include "Coordinate.h"

class Board;

enum class Cardinals;

class Ship {
public:
    Ship(Board *board, Cardinals direction, unsigned length);

    Ship(std::vector<Coordinate> coords, Board *board, Cardinals direction);

    virtual ~Ship();

    void update();

    void render(sf::RenderTarget *target, Coordinate hoveredCell, bool onCursor = false);

    const std::vector<Coordinate> &getCoords() const;

    bool isDestroyed();

    void markHit(Coordinate cell);

    void rotate();

    bool place(Coordinate center);

private:
    std::vector<Coordinate> coords;
    std::set<Coordinate> hitCoords;
    int length;
    Cardinals direction;

    Board *board;
};


#endif //BATTLESHIP_SHIP_H
