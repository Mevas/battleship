//
// Created by tudor on 5/5/2020.
//

#include "../include/Constants.h"
#include "../include/Client.h"
#include "../include/Game.h"
#include <iostream>
#include <thread>

Client::Client()
{
    this->is_attacking = false;
    this->defendThread = nullptr;
}

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

    //this->server = new Server();
    this->serverIp = Server::getInstance().getServerIp();
    std::thread thListenHost(&Server::startListeningHost, &Server::getInstance());

    sf::Socket::Status status = socket.connect(this->serverIp, 53001);

    if(status != sf::Socket::Done) {
        std::cout << "Connection to server couldn't be make\n";
    }

    receivePacket(&packet);

    packet >> s;
    std::cout << s << std::endl;

    receivePacket(&packet);
    packet >> s;
    std::cout << s << std::endl;
    thListenHost.join();
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

    //playGame();
}

void Client::playGame() {
    sf::Packet packet;
    short serverMessage;
    receivePacket(&packet);
    packet >> serverMessage;
    std::cout << serverMessage << std::endl;
    if(serverMessage == SERVER_MSG_FIRST_MOVE) {
        this->is_attacking = true;
    } else {
        startDefendingThread();
    }

    std::cout << "Game finished!\n";
}

void Client::Attack(Coordinate cell) {
    char cmd;
    sf::Packet packetToSend;
    //    std::cout << "Want to disconnect? (Y/N)\n";
    //    std::cin >> cmd;
//    if(cmd == 'Y') {
//        //TODO: Actually disconnect...
//        packetToSend << CLIENT_MSG_DISCONNECT;
//        sendPacket(&packetToSend);
//        return;
//    }
    packetToSend << CLIENT_ATTACK_COMMAND << cell.X() << cell.Y();
    sendPacket(&packetToSend);
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
            HitTypes hit;
            short x, y;
            packetToReceive >> x >> y >> hit;
            //TODO(Alex): update board based on what info we got
            std::cout << "You were hit at coord (" << x << ", " << y << "). It was a " << static_cast<int>(hit) << std::endl;
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

//return something like  HitTypes? Dunno...I think it's better for client obj to take action
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
            HitTypes hit;
            short x, y;
            packetToReceive >> x >> y >> hit;
            std::cout << "The attack at coord (" << x << ", " << y << ") was a " << static_cast<int>(hit) << std::endl;

            //TODO(Alex): update board based on what info we got
            startDefendingThread();
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

void Client::startDefendingThread(){
    //TODO(Alex): prevent attacking
    this->is_attacking = false;
    this->defendThread = new std::thread([this] {
        Defend();
        is_attacking = true;
    });
}

bool Client::readyToAttack()
{
    if(defendThread == nullptr) {
        return false;
    }

    if(this->is_attacking == true) {
        this->defendThread->join();
        delete this->defendThread;
        this->defendThread = nullptr;
        return true;
    }

    return false;
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