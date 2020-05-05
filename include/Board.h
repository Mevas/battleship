#ifndef BATTLESHIP_BOARD_H
#define BATTLESHIP_BOARD_H

#include "Coordinate.h"
#include "Ship.h"

class Ship;

class Board {
public:
    explicit Board(unsigned player);

    void addShip(Coordinate head, unsigned length, unsigned rotation);

    unsigned attack();

    void update();

    void render(sf::RenderTarget *target);

    float getStartX() const;

    float getStartY() const;

private:
    unsigned playerNumber;
    unsigned size;
    std::vector<Ship> ships;
    float startX;
    float startY;

    void drawGrid(sf::RenderTarget *target) const;
};


#endif //BATTLESHIP_BOARD_H
