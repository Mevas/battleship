#include "../include/Shadow.h"
#include "../include/Board.h"
#include "../include/Globals.h"

Shadow::Shadow(Board &board) : board(board) {

}

void Shadow::markHit(Coordinate coords) {
    hit.insert(coords);
}

void Shadow::markMissed(Coordinate coords) {
    missed.insert(coords);
}

void Shadow::markDestroyed(Coordinate coords) {
    destroyed.insert(coords);
}

void Shadow::render(sf::RenderTarget *target) {
    auto rect = sf::RectangleShape(sf::Vector2f(globals::cellSize, globals::cellSize));

    for(auto cell : hit) {
        rect.setPosition(
                board.getStartX() + globals::borderWidth + cell.X() * (globals::cellSize + globals::borderWidth),
                board.getStartY() + globals::borderWidth + cell.Y() * (globals::cellSize + globals::borderWidth)
        );

        rect.setFillColor(sf::Color(0, 255, 0, 100));

        rect.setOutlineColor(sf::Color(0, 255, 0, 128));
        rect.setOutlineThickness(globals::borderWidth);

        target->draw(rect);
    }

    for(auto cell : missed) {
        rect.setPosition(
                board.getStartX() + globals::borderWidth + cell.X() * (globals::cellSize + globals::borderWidth),
                board.getStartY() + globals::borderWidth + cell.Y() * (globals::cellSize + globals::borderWidth)
        );

        rect.setFillColor(sf::Color(255, 0, 0, 100));

        rect.setOutlineColor(sf::Color(255, 0, 0, 128));
        rect.setOutlineThickness(globals::borderWidth);

        target->draw(rect);
    }

    for(auto cell : destroyed) {
        rect.setPosition(
                board.getStartX() + globals::borderWidth + cell.X() * (globals::cellSize + globals::borderWidth),
                board.getStartY() + globals::borderWidth + cell.Y() * (globals::cellSize + globals::borderWidth)
        );

        rect.setFillColor(sf::Color(255, 165, 0, 100));

        rect.setOutlineColor(sf::Color(255, 165, 0, 128));
        rect.setOutlineThickness(globals::borderWidth);

        target->draw(rect);
    }
}

const std::set<Coordinate> &Shadow::getHit() const {
    return hit;
}

const std::set<Coordinate> &Shadow::getMissed() const {
    return missed;
}

void Shadow::mark(Coordinate coords, HitTypes hitType) {
    if(hitType == HitTypes::MISSED) {
        markMissed(coords);
        return;
    }

    if(hitType == HitTypes::HIT) {
        markHit(coords);
        return;
    }

    if(hitType == HitTypes::DESTROYED) {
        markDestroyed(coords);
        return;
    }
}
