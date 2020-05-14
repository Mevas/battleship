#include "../include/GameState.h"
#include "../include/Board.h"

GameState::GameState(sf::RenderWindow *window, std::stack<State *> &states) : State(window, states) {
    this->player = new Player(this->window, 2);
    this->enemy = new Player(this->window, 1);
//    this->player->getBoard()->addShip(Coordinate(5, 4), 5, Cardinals::EAST);
    this->player->getBoard()->addShip(4);
    this->player->getBoard()->addShip(3);
//    this->enemy->getBoard()->addShip(Coordinate(2, 4), 3, Cardinals::SOUTH);
}

GameState::~GameState() {
    delete this->player;
    delete this->enemy;
};

void GameState::update(const double &deltaTime) {
    this->updateInput(deltaTime);
    this->updateMousePosition();
    this->player->update(this->window, this->mousePosWindow);
    this->enemy->update(this->window, this->mousePosWindow);
}

void GameState::updateInput(const double &deltaTime) {
    this->checkForQuit();
}

void GameState::render(sf::RenderTarget *target) {
    this->player->render(target);
    this->enemy->render(target);
}

Board *GameState::getClickedBoard() const {
    if(player->getBoard()->isMouseInBounds())
        return player->getBoard();
    return enemy->getBoard();
}

Player *GameState::getPlayer() {
    return player;
}

Player *GameState::getEnemy() {
    return enemy;
}

bool GameState::isPlacingShips() const {
    return !player->getBoard()->getHeldShips().empty();
}
