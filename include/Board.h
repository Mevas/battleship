#ifndef BATTLESHIP_BOARD_H
#define BATTLESHIP_BOARD_H

#include <stack>
#include "Coordinate.h"

enum class Cardinals;

enum class HitTypes {
    HIT = 0, MISSED = 1, DESTROYED = 2, DENIED = 3
};

class Ship;

class Shadow;

class Player;

class Board {
public:
    explicit Board(Player &player);

    virtual ~Board();

    void addShip(Ship *ship);

    void addShip(Coordinate head, unsigned length, Cardinals direction);

    HitTypes attack(Coordinate cell);

    void update(sf::Vector2i mousePosWindow);

    void render(sf::RenderTarget *target);

    float getStartX() const;

    float getStartY() const;

    const sf::Vector2i &getMousePosWindow() const;

    Player &getPlayer() const;

    unsigned int getSize() const;

    std::stack<Ship *> &getHeldShips();

    Coordinate getHoveredCell() const;

    std::vector<Ship *> &getShips();

    void click();

    bool isMouseInBounds() const;

    bool isInBounds(Coordinate coords) const;

    bool wouldCollide(std::vector<Coordinate> coords) const;

private:
    sf::Vector2i mousePosWindow;
    Player &player;
    unsigned size;
    float startX;
    float startY;
    std::vector<Ship *> ships;
    Shadow *shadow;
    std::stack<Ship *> heldShips;

    void drawGrid(sf::RenderTarget *target, Coordinate hoveredCell) const;
};


#endif //BATTLESHIP_BOARD_H
