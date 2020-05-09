#include "../include/GameState.h"
#include "../include/Board.h"

GameState::GameState(sf::RenderWindow *window) : State(window) {
    this->player1 = new Player(this->window, 1);
    this->player2 = new Player(this->window, 2);
    this->player1->getBoard()->addShip(Coordinate(5, 4), 5, Cardinals::EAST);
    this->player2->getBoard()->addShip(Coordinate(2, 4), 3, Cardinals::SOUTH);
}

GameState::~GameState() {
    delete this->player1;
    delete this->player2;
};

void GameState::update(const double &deltaTime) {
    this->updateInput(deltaTime);
    this->updateMousePosition();
    this->player1->update(this->window, this->mousePosWindow);
    this->player2->update(this->window, this->mousePosWindow);
}

void GameState::updateInput(const double &deltaTime) {
    this->checkForQuit();
}

void GameState::render(sf::RenderTarget *target) {
    this->player1->render(target);
    this->player2->render(target);
}
