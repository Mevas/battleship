#include "Coordinate.h"

Coordinate::Coordinate(int x, int y) {
    this->x = x;
    this->y = y;
}

unsigned Coordinate::X() const {
    return this->x;
}

unsigned Coordinate::Y() const {
    return this->y;
}

std::ostream &operator<<(std::ostream &output, const Coordinate &C) {
    output << "(" << C.X() << ", " << C.Y() << ")";
    return output;
}
