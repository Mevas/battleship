#include <iostream>
#include "../include/Ship.h"

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
    auto rect = sf::RectangleShape(sf::Vector2f(50.f, 50.f));
    const auto border = 1.f;

    for(auto cell : this->coords) {
        rect.setPosition(this->parent->getStartX() + border + (cell.X() * 51),
                         this->parent->getStartY() + border + (cell.Y() * 51));
        rect.setFillColor(sf::Color(80, 80, 80, 255));
        rect.setOutlineColor(sf::Color::White);
        rect.setOutlineThickness(border);

        target->draw(rect);
    }
}
