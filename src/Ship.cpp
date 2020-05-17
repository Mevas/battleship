#include "../include/Ship.h"
#include "../include/Globals.h"
#include "../include/Board.h"
#include "../include/Player.h"
#include "../include/Client.h"

Ship::Ship(Board *board, Cardinals direction, unsigned length) : board(board), direction(direction), length(length) {

}

Ship::Ship(std::vector<Coordinate> coords, Board *board, Cardinals direction) : board(board), direction(direction) {
    this->length = coords.size();
    this->coords = std::move(coords);
}

Ship::~Ship() = default;

void Ship::update() {

}

void Ship::render(sf::RenderTarget *target, Coordinate hoveredCell, bool onCursor) {
    auto rect = sf::RectangleShape(sf::Vector2f(globals::cellSize, globals::cellSize));
    for(auto i = 0; i < length; i++) {
        rect.setFillColor(sf::Color(80, 80, 80, 255));
        if(!onCursor) {
            rect.setPosition(this->board->getStartX() + globals::borderWidth +
                             (coords[i].X() * (globals::cellSize + globals::borderWidth)),
                             this->board->getStartY() + globals::borderWidth +
                             (coords[i].Y() * (globals::cellSize + globals::borderWidth)));
            if(hoveredCell == coords[i])
                rect.setFillColor(sf::Color(120, 120, 120, 255));
        } else {
            auto mousePos = this->board->getMousePosWindow();

            int offsetX, offsetY;
            switch(direction) {
                case Cardinals::NORTH:
                    offsetX = 0;
                    offsetY = 1;
                    break;
                case Cardinals::EAST:
                    offsetX = -1;
                    offsetY = 0;
                    break;
                case Cardinals::SOUTH:
                    offsetX = 0;
                    offsetY = -1;
                    break;
                case Cardinals::WEST:
                    offsetX = 1;
                    offsetY = 0;
                    break;
            }

            rect.setPosition(mousePos.x + offsetX * (i) *
                                          (globals::cellSize + globals::borderWidth) - globals::cellSize / 2,
                             mousePos.y + offsetY * (i) *
                                          (globals::cellSize + globals::borderWidth) - globals::cellSize / 2);
        }

        rect.setOutlineColor(sf::Color::White);
        rect.setOutlineThickness(globals::borderWidth);

        target->draw(rect);
    }
}

const std::vector<Coordinate> &Ship::getCoords() const {
    return coords;
}

void Ship::rotate() {
    switch(direction) {
        case Cardinals::NORTH:
            direction = Cardinals::EAST;
            break;
        case Cardinals::EAST:
            direction = Cardinals::SOUTH;
            break;
        case Cardinals::SOUTH:
            direction = Cardinals::WEST;
            break;
        case Cardinals::WEST:
            direction = Cardinals::NORTH;
            break;
    }
}

bool Ship::place(Coordinate center) {
    Coordinate cell;
    std::vector<Coordinate> coords;
    for(int i = 0; i < length; i++) {
        switch(direction) {
            case Cardinals::NORTH:
                cell = Coordinate(center.X(), center.Y() + i);
                break;
            case Cardinals::EAST:
                cell = Coordinate(center.X() - i, center.Y());
                break;
            case Cardinals::SOUTH:
                cell = Coordinate(center.X(), center.Y() - i);
                break;
            case Cardinals::WEST:
                cell = Coordinate(center.X() + i, center.Y());
                break;
        }

        if(!board->isInBounds(cell)) {
            return false;
        }

        coords.push_back(cell);
    }

    if(board->wouldCollide(coords)) {
        return false;
    }

    this->coords = coords;
    
    Client::getInstance().addShip(this->coords[0], this->length, this->direction);

    return true;
}
