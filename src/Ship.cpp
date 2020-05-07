#include <iostream>
#include "../include/Ship.h"
#include "../include/Globals.h"

Ship::Ship(std::vector<Coordinate> coords, Board *parent) {
    this->parent = parent;
    this->length = coords.size();
    this->coords = std::move(coords);
    std::cout << "Ship created at coord " << this->coords[0] << std::endl;
}

Ship::~Ship() = default;

void Ship::update() {

}

void Ship::render(sf::RenderTarget *target) {
    auto rect = sf::RectangleShape(sf::Vector2f(globals::cellSize, globals::cellSize));
    for(auto cell : this->coords) {
        rect.setPosition(this->parent->getStartX() + globals::borderWidth +
                         (cell.X() * (globals::cellSize + globals::borderWidth)),
                         this->parent->getStartY() + globals::borderWidth +
                         (cell.Y() * (globals::cellSize + globals::borderWidth)));
        rect.setFillColor(sf::Color(80, 80, 80, 255));
        rect.setOutlineColor(sf::Color::White);
        rect.setOutlineThickness(globals::borderWidth);

        target->draw(rect);
    }
}
