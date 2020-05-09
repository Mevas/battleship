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

bool Coordinate::operator==(const Coordinate &rhs) const {
    return x == rhs.x && y == rhs.y;
}

bool Coordinate::operator<(const Coordinate &rhs) const {
    return std::to_string(x) + std::to_string(y) < std::to_string(rhs.x) + std::to_string(rhs.y);
}
