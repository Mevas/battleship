#ifndef BATTLESHIP_BOARD_H
#define BATTLESHIP_BOARD_H

#include "Coordinate.h"

class Ship;

class Shadow;

class Player;

class Board {
public:
    explicit Board(Player &player);

    virtual ~Board();

    void addShip(Coordinate head, unsigned length, unsigned rotation);

    unsigned attack();

    void update(sf::Vector2i mousePosWindow);

    void render(sf::RenderTarget *target);

    float getStartX() const;

    float getStartY() const;

    const sf::Vector2i &getMousePosWindow() const;

    Player &getPlayer() const;

    unsigned int getSize() const;

private:
    sf::Vector2i mousePosWindow;
    Player &player;
    unsigned size;
    float startX;
    float startY;
    std::vector<Ship *> ships;
    Shadow *shadow;

    void drawGrid(sf::RenderTarget *target, Coordinate hoveredCell) const;

    Coordinate getHoveredCell() const;
};


#endif //BATTLESHIP_BOARD_H
