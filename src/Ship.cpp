#include <iostream>
#include "../include/Ship.h"
#include "../include/Globals.h"
#include "../include/Board.h"

Ship::Ship(std::vector<Coordinate> coords, Board *board) {
    this->board = board;
    this->length = coords.size();
    this->coords = std::move(coords);
    std::cout << "Ship created at coord " << this->coords[0] << std::endl;
}

Ship::~Ship() = default;

void Ship::update() {

}

void Ship::render(sf::RenderTarget *target, Coordinate hoveredCell) {
    auto rect = sf::RectangleShape(sf::Vector2f(globals::cellSize, globals::cellSize));
    for(auto cell : this->coords) {
        rect.setPosition(this->board->getStartX() + globals::borderWidth +
                         (cell.X() * (globals::cellSize + globals::borderWidth)),
                         this->board->getStartY() + globals::borderWidth +
                         (cell.Y() * (globals::cellSize + globals::borderWidth)));
        if(hoveredCell == cell)
            rect.setFillColor(sf::Color(120, 120, 120, 255));
        else
            rect.setFillColor(sf::Color(80, 80, 80, 255));

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
