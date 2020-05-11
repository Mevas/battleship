//
// Created by tudor on 5/11/2020.
//

#include <iostream>
#include "../include/ServerShip.h"
#include "../include/Globals.h"
#include "../include/ServerBoard.h"
#include "../include/Player.h"

ServerShip::ServerShip(ServerBoard *board, Cardinals direction, unsigned length) : board(board), direction(direction), length(length) {

}

ServerShip::ServerShip(std::vector<Coordinate> coords, ServerBoard *board, Cardinals direction) : board(board), direction(direction) {
    this->length = coords.size();
    this->coords = std::move(coords);
    std::cout << "Ship created at coord " << this->coords[0] << std::endl;
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

bool ServerShip::place(Coordinate center) {
    Coordinate cell;
    std::vector<Coordinate> coords;
    for(int i = 0; i < length; i++) {
        switch(direction) {
            case Cardinals::NORTH:
                cell = Coordinate(center.X(), center.Y() + i);
                break;
            case Cardinals::EAST:
                cell = Coordinate(center.X() - i, center.Y());
                break;
            case Cardinals::SOUTH:
                cell = Coordinate(center.X(), center.Y() - i);
                break;
            case Cardinals::WEST:
                cell = Coordinate(center.X() + i, center.Y());
                break;
        }

        coords.push_back(cell);
    }

    if(board->wouldCollide(coords)) {
        return false;
    }

    this->coords = coords;
    return true;
}
