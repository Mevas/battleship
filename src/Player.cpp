#include "../include/Player.h"
#include "../include/Board.h"

Player::Player(sf::RenderWindow *window, unsigned number) {
    this->window = window;
    this->number = number;
    this->board = new Board(*this);
}

Player::~Player() {
    delete this->board;
}

void Player::update(sf::Vector2i mousePosWindow) {
    this->board->update(mousePosWindow);
}

void Player::render(sf::RenderTarget *target) {
    this->board->render(target);
}

unsigned int Player::getNumber() const {
    return number;
}

Board *Player::getBoard() const {
    return board;
}

