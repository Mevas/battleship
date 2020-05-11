#include "../include/Board.h"
#include "../include/Globals.h"
#include "../include/Ship.h"
#include "../include/Player.h"
#include "../include/Shadow.h"
#include "../include/Client.h"

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

void Board::addShip(unsigned length) {
    heldShips.push(new Ship(this, Cardinals::NORTH, length));
}

void Board::addShip(Coordinate head, unsigned length, Cardinals direction) {
    std::vector<Coordinate> coords;
    for(int i = 0; i < length; i++) {
        switch(direction) {
            case Cardinals::NORTH:
                coords.emplace_back(head.X(), head.Y() - i);
                break;
            case Cardinals::EAST:
                coords.emplace_back(head.X() + i, head.Y());
                break;
            case Cardinals::SOUTH:
                coords.emplace_back(head.X(), head.Y() + i);
                break;
            case Cardinals::WEST:
                coords.emplace_back(head.X() - i, head.Y());
                break;
        }
    }

    this->ships.push_back(new Ship(coords, this, direction));
}

HitTypes Board::attack(Coordinate cell) {
    if(shadow->getHit().count(cell) || shadow->getMissed().count(cell)) {
        return HitTypes::DENIED;
    }
    std::cout << cell.X() << " " << cell.Y() << std::endl;
    Client::getInstance().Attack(cell);
    Client::getInstance().ResolveAttack();
/// check is happening on the server side, should just update board here or in the resolveAttack() call
//    for(auto ship : ships) {
//        for(auto shipCell : ship->getCoords()) {
//            if(cell == shipCell) {
//                shadow->markHit(cell);
//                ship->markHit(cell);
//                if(ship->isDestroyed()) {
//                    return HitTypes::DESTROYED;
//                }
//                return HitTypes::HIT;
//            }
//        }
//    }

    shadow->markMissed(cell);
    return HitTypes::MISSED;
}

void Board::update(sf::Vector2i mousePosWindow) {
    for(auto ship : ships) {
        ship->update();
    }

    this->mousePosWindow = mousePosWindow;
}

void Board::render(sf::RenderTarget *target) {
    Coordinate hoveredCell = this->getHoveredCell();
    this->drawGrid(target, hoveredCell);

    for(auto ship : this->ships) {
        ship->render(target, hoveredCell);
    }

    if(!heldShips.empty()) {
        heldShips.top()->render(target, hoveredCell, true);
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
    auto cell = Coordinate(int(this->mousePosWindow.x - this->startX) / (globals::cellSize + globals::borderWidth),
                           int(mousePosWindow.y - this->startY) / (globals::cellSize + globals::borderWidth));

    if(!isInBounds(cell)) {
        return Coordinate(-1, -1);
    }

    return cell;
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

std::stack<Ship *> &Board::getHeldShips() {
    return heldShips;
}

std::vector<Ship *> &Board::getShips() {
    return ships;
}

void Board::click() {
    Coordinate cell = this->getHoveredCell();

    if(cell.X() < 0 || cell.Y() < 0) {
        return;
    }

//    Placing new ship behaviour
    if(!heldShips.empty()) {
        auto placed = heldShips.top()->place(cell);
        if(!placed) {
            return;
        }

        ships.push_back(heldShips.top());
        heldShips.pop();

        return;
    }

//    Attacking behaviour
    auto result = attack(cell);
    switch(result) {
        case HitTypes::HIT:
            std::cout << "Hit!\n";
            break;
        case HitTypes::MISSED:
            std::cout << "Missed...\n";
            break;
        case HitTypes::DESTROYED:
            std::cout << "Destroyed!\n";
            break;
    }
}

bool Board::isInBounds(Coordinate coords) const {
    return coords.X() >= 0 && coords.Y() >= 0 && coords.X() < globals::boardNumCells &&
           coords.Y() < globals::boardNumCells;
}

bool Board::wouldCollide(std::vector<Coordinate> coords) const {
    for(auto ship : ships) {
        for(auto cell : ship->getCoords()) {
            for(auto coord : coords) {
                if(coord == cell) {
                    return true;
                }
            }
        }
    }

    return false;
}

bool Board::isMouseInBounds() const {
    return mousePosWindow.x > startX && mousePosWindow.y > startY && mousePosWindow.x < startX + globals::boardSize &&
           mousePosWindow.y < startY + globals::boardSize;
}

