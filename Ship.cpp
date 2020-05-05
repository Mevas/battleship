#include "Ship.h"

Ship::Ship(std::vector<Coordinate> coords) {
    this->length = coords.size();
    this->coords = std::move(coords);
}

Ship::~Ship() = default;
