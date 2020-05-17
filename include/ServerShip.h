//
// Created by tudor on 5/11/2020.
//

#ifndef BATTLESHIP_SERVERSHIP_H
#define BATTLESHIP_SERVERSHIP_H

#include <vector>
#include <set>
#include "Coordinate.h"

class ServerBoard;

enum class Cardinals;

class ServerShip {
public:
    ServerShip(ServerBoard *board, Cardinals direction, unsigned length);

    ServerShip(std::vector<Coordinate> coords, ServerBoard *board, Cardinals direction);

    virtual ~ServerShip();

    const std::vector<Coordinate> &getCoords() const;

    bool isDestroyed();

    void markHit(Coordinate cell);

private:
    std::vector<Coordinate> coords;
    std::set<Coordinate> hitCoords;
    int length;
    Cardinals direction;

    ServerBoard *board;
};

#endif //BATTLESHIP_SERVERSHIP_H
