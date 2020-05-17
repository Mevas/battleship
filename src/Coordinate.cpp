#include "../include/Coordinate.h"

Coordinate::Coordinate() : x(0), y(0) {}

Coordinate::Coordinate(short x, short y) {
    this->x = x;
    this->y = y;
}

short Coordinate::X() const {
    return this->x;
}

short Coordinate::Y() const {
    return this->y;
}

sf::Packet &operator<<(sf::Packet &packet, const Coordinate &C) {
    return packet << C.x << C.y;
}

sf::Packet &operator>>(sf::Packet &packet, Coordinate &C) {
    return packet >> C.x >> C.y;
}

std::ostream &operator<<(std::ostream &output, const Coordinate &C) {
    output << "(" << C.X() << ", " << C.Y() << ")";
    return output;
}

bool Coordinate::operator==(const Coordinate &rhs) const {
    return x == rhs.x && y == rhs.y;
}

bool Coordinate::operator>=(const Coordinate &rhs) const {
    return x >= rhs.x && y >= rhs.y;
}

bool Coordinate::operator<(const Coordinate &rhs) const {
    return std::to_string(x) + std::to_string(y) < std::to_string(rhs.x) + std::to_string(rhs.y);
}
