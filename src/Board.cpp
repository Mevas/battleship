#include "../include/Board.h"
#include "../include/Globals.h"
#include "../include/Ship.h"
#include "../include/Player.h"
#include "../include/Shadow.h"

Board::Board(Player &player) : player(player) {
    this->size = globals::boardNumCells;

    switch(this->player.getNumber()) {
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

    this->shadow = new Shadow(*this);
}

Board::~Board() {
    for(auto &ship : this->ships) {
        delete ship;
    }
    delete this->shadow;
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

    this->ships.push_back(new Ship(coords, this));
}

unsigned Board::attack() {
    return 0;
}

void Board::update(sf::Vector2i mousePosWindow) {
    this->mousePosWindow = mousePosWindow;
    Coordinate cell = Coordinate(0, 0);

    if(sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
        cell = this->getHoveredCell();
        if(cell.X() < 0 || cell.Y() < 0) {
            return;
        }

        std::cout << cell << std::endl;
        shadow->markHit(cell);
    }
}

void Board::render(sf::RenderTarget *target) {
    Coordinate hoveredCell = this->getHoveredCell();
    this->drawGrid(target, hoveredCell);

    for(auto ship : this->ships) {
        ship->render(target, hoveredCell);
    }

    shadow->render(target);
}

void Board::drawGrid(sf::RenderTarget *target, Coordinate hoveredCell) const {
    auto rect = sf::RectangleShape(sf::Vector2f(globals::cellSize, globals::cellSize));

    for(auto i = 0; i < this->size; ++i) {
        for(auto j = 0; j < this->size; ++j) {
            rect.setPosition(this->startX + globals::borderWidth + i * (globals::cellSize + globals::borderWidth),
                             this->startY + globals::borderWidth + j * (globals::cellSize + globals::borderWidth));

            if(hoveredCell.X() == i && hoveredCell.Y() == j)
                rect.setFillColor(sf::Color(0, 0, 255, 160));
            else
                rect.setFillColor(sf::Color(0, 0, 255, 100));

            rect.setOutlineColor(sf::Color(0, 0, 255, 128));
            rect.setOutlineThickness(globals::borderWidth);

            target->draw(rect);
        }
    }
}

Coordinate Board::getHoveredCell() const {
    if(this->startX > this->mousePosWindow.x || this->startY > this->mousePosWindow.y ||
       this->mousePosWindow.x > this->startX + globals::boardSize - 1 ||
       this->mousePosWindow.y > this->startY + globals::boardSize - 1) {
        return Coordinate(-1, -1);
    }
    return Coordinate(int(this->mousePosWindow.x - this->startX) / (globals::cellSize + globals::borderWidth),
                      int(mousePosWindow.y - this->startY) / (globals::cellSize + globals::borderWidth));
}

float Board::getStartX() const {
    return startX;
}

float Board::getStartY() const {
    return startY;
}

const sf::Vector2i &Board::getMousePosWindow() const {
    return mousePosWindow;
}

Player &Board::getPlayer() const {
    return player;
}

unsigned int Board::getSize() const {
    return size;
}
