#ifndef BATTLESHIP_COORDINATE_H
#define BATTLESHIP_COORDINATE_H

#include <iostream>

#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>


class Coordinate {
public:
    Coordinate();

    Coordinate(short x, short y);

    [[nodiscard]] short X() const;

    [[nodiscard]] short Y() const;

    friend std::ostream &operator<<(std::ostream &output, const Coordinate &C);

    friend sf::Packet &operator<<(sf::Packet &packet, const Coordinate &C);

    friend sf::Packet &operator>>(sf::Packet &packet, Coordinate &C);

    bool operator==(Coordinate const &rhs) const;

    bool operator>=(const Coordinate &rhs) const;

    bool operator<(const Coordinate &rhs) const;

private:
    short x;
    short y;
};


#endif //BATTLESHIP_COORDINATE_H
