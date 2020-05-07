#include "../include/Board.h"
#include "../include/Globals.h"

Board::Board(unsigned player) {
    this->size = globals::boardNumCells;
    this->playerNumber = player;

    switch(this->playerNumber) {
        case 1:
            this->startX = 0;
            this->startY = 0;
            break;
        case 2:
            this->startX = 0;
            this->startY = globals::spaceBetweenBoards + globals::boardSize;
            break;
        default:
            return;
    }

    this->addShip(Coordinate(5, 5), 2, 0);
}

void Board::addShip(Coordinate head, unsigned length, unsigned rotation) {
    std::vector<Coordinate> coords;
    for(int i = 0; i < length; i++) {
        switch(rotation) {
            case 0: // North
                coords.emplace_back(head.X(), head.Y() + i);
                break;
            case 1: // East
                coords.emplace_back(head.X() - i, head.Y());
                break;
            case 2: // South
                coords.emplace_back(head.X(), head.Y() - i);
                break;
            case 3: // West
                coords.emplace_back(head.X() + i, head.Y());
                break;
            default:
                continue;
        }
    }

    this->ships.emplace_back(coords, this);
}

unsigned Board::attack() {
    return 0;
}

void Board::update(sf::RenderWindow *window) {
    if(sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
        sf::Vector2i position = sf::Mouse::getPosition(*(sf::Window *) window);
        std::cout << position.x << ", " << position.y << std::endl;
    }
}

void Board::render(sf::RenderTarget *target) {
    this->drawGrid(target);

    for(auto ship : this->ships) {
        ship.render(target);
    }
}

void Board::drawGrid(sf::RenderTarget *target) const {
    auto rect = sf::RectangleShape(sf::Vector2f(globals::cellSize, globals::cellSize));
    for(auto i = 0; i < this->size; ++i) {
        for(auto j = 0; j < this->size; ++j) {
            rect.setPosition(this->startX + globals::borderWidth + i * (globals::cellSize + globals::borderWidth),
                             this->startY + globals::borderWidth + j * (globals::cellSize + globals::borderWidth));
            rect.setFillColor(sf::Color(0, 0, 255, 100));
            rect.setOutlineColor(sf::Color(0, 0, 255, 128));
            rect.setOutlineThickness(globals::borderWidth);

            target->draw(rect);
        }
    }
}

float Board::getStartX() const {
    return this->startX;
}

float Board::getStartY() const {
    return this->startY;
}
