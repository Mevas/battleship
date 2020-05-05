#ifndef BATTLESHIP_COORDINATE_H
#define BATTLESHIP_COORDINATE_H


class Coordinate {
public:
    Coordinate(int x, int y);

    [[nodiscard]] unsigned X() const;

    [[nodiscard]] unsigned Y() const;

private:
    unsigned x;
    unsigned y;
};


#endif //BATTLESHIP_COORDINATE_H
