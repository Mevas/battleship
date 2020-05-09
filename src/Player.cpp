#include "../include/Player.h"

Player::Player(sf::RenderWindow *window, unsigned player) {
    this->window = window;
    this->board = new Board(this->window, player);
    this->playerNumber = player;
}

Player::~Player() {
    delete this->board;
};

void Player::fire(Coordinate coords) {

}

void Player::update(sf::RenderWindow *window, sf::Vector2i mousePosWindow) {
    this->board->update(window, mousePosWindow);
    this->mousePosWindow = mousePosWindow;
}

void Player::render(sf::RenderTarget *target) {
    this->board->render(target);
}

Board *Player::getBoard() {
    return this->board;
}
