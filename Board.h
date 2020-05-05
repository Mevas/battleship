#ifndef BATTLESHIP_BOARD_H
#define BATTLESHIP_BOARD_H

#include <iostream>

#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>

#include "Ship.h"

class Board {
public:
    explicit Board(unsigned player);

    void addShip(Coordinate head, unsigned length, unsigned rotation);

    unsigned attack();

    void update();

    void render(sf::RenderTarget *target);
private:
    unsigned playerNumber;
    unsigned size;
    std::vector<Ship> ships;
    float startX;
    float startY;

    void drawGrid(sf::RenderTarget *target) const;

};


#endif //BATTLESHIP_BOARD_H
