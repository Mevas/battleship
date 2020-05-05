#include <iostream>
#include "Ship.h"

Ship::Ship(std::vector<Coordinate> coords) {
    this->length = coords.size();
    this->coords = std::move(coords);
    std::cout << "Ship created at coord " << this->coords[0] << std::endl;
}

Ship::~Ship() = default;
