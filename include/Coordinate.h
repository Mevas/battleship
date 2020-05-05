#ifndef BATTLESHIP_COORDINATE_H
#define BATTLESHIP_COORDINATE_H

#include <iostream>

#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>


class Coordinate {
public:
    Coordinate(int x, int y);

    [[nodiscard]] unsigned X() const;

    [[nodiscard]] unsigned Y() const;

    friend std::ostream &operator<<( std::ostream &output, const Coordinate &C );
private:
    unsigned x;
    unsigned y;
};


#endif //BATTLESHIP_COORDINATE_H
