//
// Created by tudor on 5/5/2020.
//

#include <iostream>
#include <thread>
#include "../includes/Client.h"

void Client::hostGame()
{
    sf::Packet packet;

    sf::Uint16 x;
    std::string s;
    double d;

    this->server = new Server();
    this->serverIp = server->getServerIp();
    std::thread thListenHost(&Server::startListeningHost, server);

    sf::Socket::Status status = socket.connect(this->serverIp, 53001);
    thListenHost.join();

    if (status != sf::Socket::Done)
    {
        std::cout << "Connection to server couldn't be make\n";
    }
    else if (socket.receive(packet) != sf::Socket::Done)
    {
        std::cout << "No Package received!\n";
    }
    else
    {
        packet >> x >> s >> d;

        std::cout << s << std::endl;
    }

    std::thread thListenGuest(&Server::startListeningGuest, server);
    if(socket.receive(packet) != sf::Socket::Done)
    {
        std::cout<< "Guest couldn't connect!\n";
    }
    packet >> s;
    std::cout << packet << std::endl;
    thListenGuest.join();
}

void Client::joinGame()
{
    sf::Packet packet;

    sf::Uint16 x;
    std::string s;
    double d;

    std::cout << "Server Ip?\n";
    std::cin >> this->serverIp;

    sf::Socket::Status status = socket.connect(this->serverIp, 53002);

    if (status != sf::Socket::Done)
    {
        std::cout << "No Host for me:(\n";
    }
    else if (socket.receive(packet) != sf::Socket::Done)
    {
        std::cout << "No Package received from Server!\n";
    }
    else
    {
        packet >> x >> s >> d;
        std::cout << s << std::endl;
        sf::Packet packetToSend;
        s = "I am your Guest!";
        packetToSend << s;
        //sendPacket(packet);
        std::cout << "Sending package...\n";
        if (this->socket.send(packetToSend) != sf::Socket::Done)
        {
            std::cout << "Can't Send Package to Server!\n";
        }
        std::cout << "Package Sent!\n";
    }
}

void Client::sendPacket(sf::Packet packet)
{
    std::cout << "Sending package...\n";
    if (this->socket.send(packet) != sf::Socket::Done)
    {
        std::cout << "Can't Send Package to Server!\n";
    }
}