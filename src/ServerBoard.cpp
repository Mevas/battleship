//
// Created by tudor on 5/11/2020.
//

#include "../include/ServerBoard.h"
#include "../include/Globals.h"
#include "../include/ServerShip.h"

ServerBoard::ServerBoard() {
    this->size = globals::boardNumCells;
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
                coords.emplace_back(head.X(), head.Y() - i);
                break;
            case Cardinals::EAST:
                coords.emplace_back(head.X() + i, head.Y());
                break;
            case Cardinals::SOUTH:
                coords.emplace_back(head.X(), head.Y() + i);
                break;
            case Cardinals::WEST:
                coords.emplace_back(head.X() - i, head.Y());
                break;
        }
    }

    this->ships.push_back(new ServerShip(coords, this, direction));
}

HitTypes ServerBoard::attack(Coordinate cell) {
    std::cout << cell.X() << " " << cell.Y() << std::endl;
    for(auto ship : ships) {
        for(auto shipCell : ship->getCoords()) {
            if(cell == shipCell) {
                ship->markHit(cell);
                if(ship->isDestroyed()) {
                    return HitTypes::DESTROYED;
                }
                return HitTypes::HIT;
            }
        }
    }

    return HitTypes::MISSED;
}


std::vector<ServerShip *> &ServerBoard::getShips() {
    return ships;
}

bool ServerBoard::wouldCollide(std::vector<Coordinate> coords) const {
    for(auto ship : ships) {
        for(auto cell : ship->getCoords()) {
            for(auto coord : coords) {
                if(coord == cell) {
                    return true;
                }
            }
        }
    }

    return false;
}

