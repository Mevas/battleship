#include "../include/Player.h"

Player::Player(unsigned player) {
    this->board = new Board(player);
    this->playerNumber = player;
}

Player::~Player() {
    delete this->board;
};

void Player::fire(Coordinate coords) {

}

void Player::update(sf::RenderWindow *window) {
    this->board->update(window);
}

void Player::render(sf::RenderTarget *target) {
    this->board->render(target);
}