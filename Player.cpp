#include "Player.h"

Player::Player() {
    this->board = new Board();
}

Player::~Player() {
    delete this->board;
};

void Player::fire(Coordinate coords) {

}
