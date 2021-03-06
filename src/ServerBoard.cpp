//
// Created by tudor on 5/11/2020.
//

#include "../include/ServerBoard.h"
#include "../include/Globals.h"
#include "../include/ServerShip.h"

ServerBoard::ServerBoard() {
    this->shipCount = 0;
}

ServerBoard::~ServerBoard() {
    for(auto &ship : this->ships) {
        delete ship;
    }
}

void ServerBoard::addShip(Coordinate head, unsigned length, Cardinals direction) {
    std::vector<Coordinate> coords;
    for(int i = 0; i < length; i++) {
        switch(direction) {
            case Cardinals::NORTH:
                coords.emplace_back(head.X(), head.Y() + i);
                break;
            case Cardinals::EAST:
                coords.emplace_back(head.X() - i, head.Y());
                break;
            case Cardinals::SOUTH:
                coords.emplace_back(head.X(), head.Y() - i);
                break;
            case Cardinals::WEST:
                coords.emplace_back(head.X() + i, head.Y());
                break;
        }
    }

    this->ships.push_back(new ServerShip(coords, this, direction));
    this->shipCount++;
}

HitTypes ServerBoard::attack(Coordinate cell) {
    for(auto ship : ships) {
        for(auto shipCell : ship->getCoords()) {
            if(cell == shipCell) {
                ship->markHit(cell);
                if(ship->isDestroyed()) {
                    this->shipCount--;
                    return HitTypes::DESTROYED;
                }
                return HitTypes::HIT;
            }
        }
    }

    return HitTypes::MISSED;
}


