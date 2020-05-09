//
// Created by tudor on 5/5/2020.
//

#ifndef BATTLESHIP_CLIENT_SERVER_H
#define BATTLESHIP_CLIENT_SERVER_H

#include <SFML/Network.hpp>

const std::string SERVER_MESSAGE_PREFIX = "SERVER<<< ";

class Server {
private:
    sf::IpAddress serverIp;
    sf::TcpListener listener;
    sf::TcpSocket clientHost;
    sf::TcpSocket clientGuest;
public:
    Server();

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
     */
    void sendPacket(sf::TcpSocket *client, sf::Packet *packet);

    /**
     * @param client , the socket from which you receive data
     * @param packet , address of the packet you want to populate with client data
     */
    void receivePacket(sf::TcpSocket *client, sf::Packet *packet);
};

#endif //BATTLESHIP_CLIENT_SERVER_H
