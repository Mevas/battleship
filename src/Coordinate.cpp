#include "../include/Coordinate.h"

Coordinate::Coordinate(int x, int y) {
    this->x = x;
    this->y = y;
}

int Coordinate::X() const {
    return this->x;
}

int Coordinate::Y() const {
    return this->y;
}

std::ostream &operator<<(std::ostream &output, const Coordinate &C) {
    output << "(" << C.X() << ", " << C.Y() << ")";
    return output;
}
