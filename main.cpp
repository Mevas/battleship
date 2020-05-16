#include "include/Game.h"

#include "include/Server.h"
#include "include/Client.h"
#include <iostream>
#include <string.h>
#include <thread>
#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>

int main() {
    //Client *client = new Client();
    //Client::getInstance();
    Game game;
    game.run();

//    char action;
//    std::cout << "Host game or Join Game?(H/J)\n";
//    std::cin >> action;
//    if(action == 'H') {
//        Client::getInstance().hostGame();
//        std::thread thGameLoop(&Server::gameLoop, &Server::getInstance());
//        Client::getInstance().playGame();
//        Game game;
//        game.run();
//        thGameLoop.join();
//    } else {
//        char now;
//        Client::getInstance().joinGame();
//        Client::getInstance().playGame();
//        //! Just to differentiate interfaces in testing
//        std::cout<<"Say when...\n";
//        std::cin >> now;
//        Game game;
//        game.run();
//    }
//
//    std::cout << "Do you Love the game?";
//    std::cin >> action;

    return 0;
}
