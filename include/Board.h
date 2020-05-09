#ifndef BATTLESHIP_BOARD_H
#define BATTLESHIP_BOARD_H

#include "Coordinate.h"

class Ship;

class Board {
public:
    explicit Board(sf::RenderWindow *window, unsigned player);

    virtual ~Board();

    void addShip(Coordinate head, unsigned length, unsigned rotation);

    unsigned attack();

    void update(sf::RenderWindow *window, sf::Vector2i mousePosWindow);

    void render(sf::RenderTarget *target);

    float getStartX() const;

    float getStartY() const;

private:
    sf::RenderWindow *window;
    sf::Vector2i mousePosWindow;
    unsigned playerNumber;
    unsigned size;
    std::vector<Ship *> ships;
    float startX;
    float startY;

    void drawGrid(sf::RenderTarget *target, Coordinate hoveredCell) const;

    Coordinate getHoveredCell() const;
};


#endif //BATTLESHIP_BOARD_H
