#include "../include/Player.h"
#include "../include/Board.h"

Player::Player(sf::RenderWindow *window, unsigned number) {
    this->window = window;
    this->number = number;
    this->board = new Board(*this);
}

Player::~Player() {
    delete this->board;
};

void Player::fire(Coordinate coords) {

}

void Player::update(sf::RenderWindow *window, sf::Vector2i mousePosWindow) {
    this->board->update(mousePosWindow);
    this->mousePosWindow = mousePosWindow;
}

void Player::render(sf::RenderTarget *target) {
    this->board->render(target);
}

unsigned int Player::getNumber() const {
    return number;
}

sf::RenderWindow *Player::getWindow() const {
    return window;
}

const sf::Vector2i &Player::getMousePosWindow() const {
    return mousePosWindow;
}

Board *Player::getBoard() const {
    return board;
}

