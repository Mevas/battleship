#include <iostream>
#include "../include/Ship.h"
#include "../include/Globals.h"
#include "../include/Board.h"
#include "../include/Player.h"

Ship::Ship(Board *board, Cardinals direction, unsigned length) : board(board), direction(direction), length(length) {

}

Ship::Ship(std::vector<Coordinate> coords, Board *board, Cardinals direction) : board(board), direction(direction) {
    this->length = coords.size();
    this->coords = std::move(coords);
    std::cout << "Ship created at coord " << this->coords[0] << std::endl;
}

Ship::~Ship() = default;

void Ship::update() {

}

void Ship::render(sf::RenderTarget *target, Coordinate hoveredCell, bool onCursor) {
    auto rect = sf::RectangleShape(sf::Vector2f(globals::cellSize, globals::cellSize));
    for(auto i = 0; i < length; i++) {
        rect.setFillColor(sf::Color(80, 80, 80, 255));
        if(!onCursor) {
            rect.setPosition(this->board->getStartX() + globals::borderWidth +
                             (coords[i].X() * (globals::cellSize + globals::borderWidth)),
                             this->board->getStartY() + globals::borderWidth +
                             (coords[i].Y() * (globals::cellSize + globals::borderWidth)));
            if(hoveredCell == coords[i])
                rect.setFillColor(sf::Color(120, 120, 120, 255));
        } else {
            auto mousePos = this->board->getMousePosWindow();
            rect.setPosition(mousePos.x + (int(direction) % 2) * (i - int(length / 2)) *
                                          (globals::cellSize + globals::borderWidth) - globals::cellSize / 2,
                             mousePos.y + (int(direction) % 2 - 1) * (i - int(length / 2)) *
                                          (globals::cellSize + globals::borderWidth) - globals::cellSize / 2);
        }

        rect.setOutlineColor(sf::Color::White);
        rect.setOutlineThickness(globals::borderWidth);

        target->draw(rect);
    }
}

const std::vector<Coordinate> &Ship::getCoords() const {
    return coords;
}

bool Ship::isDestroyed() {
    return hitCoords.size() == length;
}

void Ship::markHit(Coordinate cell) {
    hitCoords.insert(cell);
}

void Ship::rotate() {
    switch(direction) {
        case Cardinals::NORTH:
            direction = Cardinals::EAST;
            break;
        case Cardinals::EAST:
            direction = Cardinals::SOUTH;
            break;
        case Cardinals::SOUTH:
            direction = Cardinals::WEST;
            break;
        case Cardinals::WEST:
            direction = Cardinals::NORTH;
            break;
    }
}

bool Ship::place(Coordinate center) {
    Coordinate cell;
    std::vector<Coordinate> coords;
    for(int i = -length / 2; i <= length / 2; i++) {
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

        if(!board->isInBounds(cell)) {
            return false;
        }

        coords.push_back(cell);
    }

    if(board->wouldCollide(coords)) {
        return false;
    }

    this->coords = coords;
    return true;
}
