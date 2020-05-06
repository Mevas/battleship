//
// Created by tudor on 5/5/2020.
//
#include "../includes/Server.h"
#include <iostream>
#include <SFML/Graphics.hpp>

Server::Server()
{
    this->serverIp = sf::IpAddress::getLocalAddress();
    std::cout << this->serverIp << std::endl;
}

sf::IpAddress Server::getServerIp()
{
    return this->serverIp;
}

void Server::startListeningHost()
{
    if(this->listener.listen(53001) != sf::Socket::Done)
    {
        std::cout << "Can't start listening host!\n";
    }
    else
    {
        std::cout << "Now I Listen for Host!\n";
        acceptHost();
    }
}

void Server::acceptHost()
{
    if (listener.accept(this->clientHost) != sf::Socket::Done)
    {
        std::cout << "Couldn't accept host\n";
        return;
    }

    sf::Uint16 x = 10;
    std::string s = "hello, Host";
    double d = 0.6;

    sf::Packet packet;
    packet << x << s << d;

    // TCP socket:
    if (clientHost.send(packet) != sf::Socket::Done)
    {
        // error...
    }
}

void Server::startListeningGuest()
{
    if(this->listener.listen(53002) != sf::Socket::Done)
    {
        std::cout << "Can't start listening guest!\n";
    }
    else
    {
        std::cout << "Now I Listen for Guest!\n";
        acceptGuest();
    }
}

void Server::acceptGuest()
{
    if (listener.accept(this->clientGuest) != sf::Socket::Done)
    {
        std::cout << "Couldn't accept guest\n";
        return;
    }

    sf::Uint16 x = 10;
    std::string s = "hello, Guest";
    double d = 0.6;

    sf::Packet packet;
    sf::Packet packetToReceive;
    sf::Packet packetToSend;
    packet << x << s << d;

    // TCP socket:
    if (this->clientGuest.send(packet) != sf::Socket::Done)
    {
        // error...
    }
    if (this->clientGuest.receive(packetToReceive) != sf::Socket::Done)
    {
        // error...
    }
    else
    {
        packetToReceive >> s;
        std::cout << s << std::endl;
        packetToSend << s;
        if (this->clientHost.send(packetToSend) != sf::Socket::Done)
        {
            //error...
        }
    }

}