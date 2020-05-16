#include <memory>

#include "../include/GameState.h"
#include "../include/Board.h"
#include "../include/ShipFactory.h"
#include "../include/Client.h"

GameState::GameState(sf::RenderWindow *window, std::stack<State *> &states) : State(window, states) {
    this->player = new Player(this->window, 2);
    this->enemy = new Player(this->window, 1);

    Client::getInstance().setPlayerShadow(this->player->getBoard()->getShadow());
    Client::getInstance().setEnemyShadow(this->enemy->getBoard()->getShadow());

    std::unique_ptr<ShipFactory> shipFactory = std::make_unique<ShipFactory>(*this->player->getBoard());

    this->player->getBoard()->addShip(shipFactory->createShip(ShipTypes::DESTROYER));
    this->player->getBoard()->addShip(shipFactory->createShip(ShipTypes::CRUISER));
    this->player->getBoard()->addShip(shipFactory->createShip(ShipTypes::SUBMARINE));
    this->player->getBoard()->addShip(shipFactory->createShip(ShipTypes::BATTLESHIP));
    this->player->getBoard()->addShip(shipFactory->createShip(ShipTypes::CARRIER));
}

GameState::~GameState() {
    delete this->player;
    delete this->enemy;
};

void GameState::update(const double &deltaTime) {
    this->updateInput(deltaTime);
    this->updateMousePosition();
    if(Client::getInstance().readyToAttack())
    {
        std::cout << "It's your turn to attack!\n";
    }
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
