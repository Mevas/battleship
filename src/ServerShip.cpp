//
// Created by tudor on 5/11/2020.
//

#include "../include/ServerShip.h"
#include "../include/ServerBoard.h"

ServerShip::ServerShip(ServerBoard *board, Cardinals direction, unsigned length) : board(board), direction(direction),
                                                                                   length(length) {}

ServerShip::ServerShip(std::vector<Coordinate> coords, ServerBoard *board, Cardinals direction) : board(board), direction(direction) {
    this->length = coords.size();
    this->coords = std::move(coords);
}

ServerShip::~ServerShip() = default;

const std::vector<Coordinate> &ServerShip::getCoords() const {
    return coords;
}

bool ServerShip::isDestroyed() {
    return hitCoords.size() == length;
}

void ServerShip::markHit(Coordinate cell) {
    hitCoords.insert(cell);
}

