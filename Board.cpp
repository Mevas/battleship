#include "Board.h"

Board::Board() {
    this->addShip(Coordinate(5, 5), 2, 0);
}

void Board::addShip(Coordinate head, unsigned length, unsigned rotation) {
    std::vector<Coordinate> coords;
    for (int i = 0; i < length; i++) {
        switch(rotation) {
            case 0: // North
                coords.emplace_back(head.X(), head.Y() + i);
            case 1: // East
                coords.emplace_back(head.X() - i, head.Y());
            case 2: // South
                coords.emplace_back(head.X(), head.Y() - i);
            case 3: // West
                coords.emplace_back(head.X() + i, head.Y());
            default:
                continue;
        }
    }

    this->ships.emplace_back(coords);
}

unsigned Board::attack() {
    return 0;
}
