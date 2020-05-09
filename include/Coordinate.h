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

    Coordinate(int x, int y);

    [[nodiscard]] int X() const;

    [[nodiscard]] int Y() const;

    friend std::ostream &operator<<(std::ostream &output, const Coordinate &C);

    bool operator==(Coordinate const &rhs) const;

    bool operator<(const Coordinate &rhs) const;

private:
    int x;
    int y;
};


#endif //BATTLESHIP_COORDINATE_H
