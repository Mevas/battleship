#include "include/Game.h"

#include "include/Server.h"
#include "include/Client.h"
#include <iostream>
#include <string.h>
#include <thread>
#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>

int main() {
    Game game;

    game.run();

    //Client *client = new Client();
    //Client::getInstance();

    char action;
    std::cout << "Host game or Join Game?(H/J)\n";
    std::cin >> action;
    if(action == 'H') {
        Client::getInstance().hostGame();
    } else {
        Client::getInstance().joinGame();
    }

    std::cout << "Do you Love the game?";
    std::cin >> action;

    return 0;
}
