#ifndef BATTLESHIP_SHADOW_H
#define BATTLESHIP_SHADOW_H

#include <set>

#include "Coordinate.h"
#include "Constants.h"

class Board;

class Shadow {
public:
    Shadow(Board &board);

    void render(sf::RenderTarget *target);

    const std::set<Coordinate> &getHit() const;

    const std::set<Coordinate> &getMissed() const;

    void mark(Coordinate coords, HitTypes hitType);

private:
    Board &board;
    std::set<Coordinate> hit;
    std::set<Coordinate> missed;
    std::set<Coordinate> destroyed;

    void markHit(Coordinate coords);

    void markMissed(Coordinate coords);

    void markDestroyed(Coordinate coords);
};


#endif //BATTLESHIP_SHADOW_H
