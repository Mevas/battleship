//
// Created by tudor on 5/5/2020.
//

#ifndef BATTLESHIP_CLIENT_SERVER_H
#define BATTLESHIP_CLIENT_SERVER_H

#include <SFML/Network.hpp>
#include "ServerBoard.h"

const std::string SERVER_MESSAGE_PREFIX = "SERVER<<< ";

class Server {
private:
    sf::IpAddress serverIp;
    sf::TcpListener listener;
    sf::TcpSocket clientHost;
    sf::TcpSocket clientGuest;
    ServerBoard * hostBoard;
    ServerBoard * guestBoard;

    Server();
public:
    static Server& getInstance();

    Server(Server const&)          = delete;
    void operator=(Server const&)  = delete;

    sf::IpAddress getServerIp();

    void startListeningHost();

    void acceptHost();

    void startListeningGuest();

    void acceptGuest();

    void gameLoop();

    /**
     *
     *  @param client , the socket where you send data
     *  @param packet , address of the packet containing data for the client
     *  @param clear  , clear packet after information is sent
     */
    void sendPacket(sf::TcpSocket *client, sf::Packet *packet, bool clear = false);

    /**
     * @param client , the socket from which you receive data
     * @param packet , address of the packet you want to populate with client data
     */
    void receivePacket(sf::TcpSocket *client, sf::Packet *packet);
};

#endif //BATTLESHIP_CLIENT_SERVER_H
