//
// Created by tudor on 5/5/2020.
//

#include "../include/Constants.h"
#include "../include/Client.h"
#include <iostream>
#include <thread>

Client & Client::getInstance()
{
    static Client    instance; // Guaranteed to be destroyed.
    // Instantiated on first use.
    return instance;
}

void Client::hostGame() {

    sf::Packet packet;

    sf::Uint16 x;
    std::string s;
    double d;

    this->server = new Server();
    this->serverIp = server->getServerIp();
    std::thread thListenHost(&Server::startListeningHost, server);

    sf::Socket::Status status = socket.connect(this->serverIp, 53001);
    thListenHost.join();

    if(status != sf::Socket::Done) {
        std::cout << "Connection to server couldn't be make\n";
    }

    receivePacket(&packet);

    packet >> s;
    std::cout << s << std::endl;

    std::thread thListenGuest(&Server::startListeningGuest, server);
    receivePacket(&packet);
    packet >> s;
    std::cout << s << std::endl;
    thListenGuest.join();

    std::thread thGameLoop(&Server::gameLoop, server);
    playGame();
    thGameLoop.join();
}

void Client::joinGame() {
    sf::Packet packet;
    std::string s;

    std::cout << "Server Ip?\n";
    std::cin >> this->serverIp;

    sf::Socket::Status status = socket.connect(this->serverIp, 53002);

    if(status != sf::Socket::Done) {
        std::cout << "No Host for me:(\n";
    }
    receivePacket(&packet);
    packet >> s;
    std::cout << s << std::endl;

    sf::Packet packetToSend;
    s = "I am your Guest!";
    packetToSend << s;
    sendPacket(&packet);
    playGame();
}

void Client::playGame() {
    sf::Packet packet;
    short serverMessage;
    receivePacket(&packet);
    packet >> serverMessage;
    std::cout << serverMessage << std::endl;
    if(serverMessage == SERVER_MSG_FIRST_MOVE) {
        Attack();
    } else {
        Defend();
    }

    std::cout << "Game finished!\n";
}

void Client::Attack() {
    short x, y;
    char cmd;
    sf::Packet packetToSend;
    std::cout << "Want to disconnect? (Y/N)\n";
    std::cin >> cmd;
    if(cmd == 'Y') {
        //TODO: Actually disconnect...
        packetToSend << CLIENT_MSG_DISCONNECT;
        sendPacket(&packetToSend);
        return;
    }
    std::cout << "It's your turn to attack!\nAttack coordinate x (1 - 9):\n";
    std::cin >> x;
    std::cout << "Attack coordinate y (1 - 9):\n";
    std::cin >> y;
    packetToSend << CLIENT_ATTACK_COMMAND << x << y;
    sendPacket(&packetToSend);

    ResolveAttack();
}

void Client::Defend() {
    short serverMessage;
    sf::Packet packetToReceive;

    std::cout << "Now you are defending! Wait for enemy to attack.\n";
    receivePacket(&packetToReceive);
    packetToReceive >> serverMessage;
    std::cout << serverMessage << std::endl;
    switch(serverMessage) {
        case SERVER_MSG_END: {
            //TODO: disconnect...
            return;
        }
        case SERVER_HIT_RESOLVE: {
            bool shipHit;
            short x, y;
            packetToReceive >> x >> y >> shipHit;
            //TODO: update board based on what info we got
            std::cout << "You were hit at coord (" << x << ", " << y << "). It was a " << (shipHit ? "success" : "miss")
                      << std::endl;
            Attack();
            break;
        }
        case SERVER_MSG_LOSE: {
            std::cout << "You Lost. All your ship have sunken\n";
            //TODO: end the game
        }
        default: {
            //TODO: check server connection...
        }
    }
}

void Client::ResolveAttack() {
    short messageFromServer;
    sf::Packet packetToReceive;
    receivePacket(&packetToReceive);
    packetToReceive >> messageFromServer;
    switch(messageFromServer) {
        case SERVER_MSG_END: {
            std::cout << "server closed, end process...";
            //TODO: disconnect
            return;
        }
        case SERVER_ATTACK_RESOLVE: {
            bool shipHit;
            short x, y;
            packetToReceive >> x >> y >> shipHit;
            std::cout << "The attack at coord (" << x << ", " << y << ") was a " << (shipHit ? "success" : "miss")
                      << std::endl;
            //TODO: update board based on what info we got
            Defend();
            break;
        }
        case SERVER_MSG_WIN: {
            std::cout << "You won!!!! Congratulations.\n";
            //TODO: end the game
        }
        default: {
            std::cout << "HUH??";
            //TODO: check server connection...
        }
    }

}

void Client::sendPacket(sf::Packet *packet) {
    //std::cout << CLIENT_MESSAGE_PREFIX << "Sending package...\n";
    if(this->socket.send((*packet)) != sf::Socket::Done) {
        //std::cout << CLIENT_MESSAGE_PREFIX << "Can't Send Package to Server!\n";
        return;
    }

    //std::cout << CLIENT_MESSAGE_PREFIX << "Package Sent\n";
}

void Client::receivePacket(sf::Packet *packet) {
    //std::cout << CLIENT_MESSAGE_PREFIX << "Receiving package...\n";
    if(this->socket.receive((*packet)) != sf::Socket::Done) {
        //std::cout << CLIENT_MESSAGE_PREFIX << "Can't Receive Package from Server!\n";
        return;
    }

    //std::cout << CLIENT_MESSAGE_PREFIX << "Package Received\n";
}