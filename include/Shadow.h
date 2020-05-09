#ifndef BATTLESHIP_SHADOW_H
#define BATTLESHIP_SHADOW_H

#include <set>

#include "Coordinate.h"

class Board;

class Shadow {
public:
    Shadow(Board &board);

    void markHit(Coordinate coords);

    void markMissed(Coordinate coords);

    void render(sf::RenderTarget *target);

private:
    Board &board;
    std::set<Coordinate> hit;
    std::set<Coordinate> missed;
};


#endif //BATTLESHIP_SHADOW_H
