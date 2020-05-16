//
// Created by tudor on 5/8/2020.
//

#ifndef BATTLESHIP_CLIENT_CONSTANTS_H
#define BATTLESHIP_CLIENT_CONSTANTS_H

#include <string>
#include <SFML/Network/Packet.hpp>
#include <chrono>

//1-100 for server msg
const short SERVER_MSG_END = 1;
const short SERVER_MSG_WIN = 2;
const short SERVER_MSG_LOSE = 3;
const short SERVER_ATTACK_RESOLVE = 4;
const short SERVER_HIT_RESOLVE = 5;
const short SERVER_MSG_FIRST_MOVE = 6;
const short SERVER_MSG_SECOND_MOVE = 7;

//101-200 for client msg
const short CLIENT_MSG_DISCONNECT = 101;
const short CLIENT_ATTACK_COMMAND = 102;
const short CLIENT_SET_SHIP = 103;
const short CLIENT_ALL_SHIP_SET = 104;

const std::string CLIENT_MESSAGE_PREFIX = "CLIENT<<< ";
const std::chrono::seconds HEARTBEAT_RATE = static_cast<std::chrono::seconds> (3);

enum class Cardinals {
    NORTH, EAST, SOUTH, WEST
};

enum class HitTypes {
    HIT = 0, MISSED = 1, DESTROYED = 2, DENIED = 3
};

enum ShipTypes {
    DESTROYER,
    SUBMARINE,
    CRUISER,
    BATTLESHIP,
    CARRIER
};

template<typename T, typename = typename std::enable_if<std::is_enum<T>::value>::type>
sf::Packet& operator<<(sf::Packet& roPacket, const T& rkeMsgType)
{
    return roPacket << static_cast<typename std::underlying_type<T>::type>(rkeMsgType);
}

template<typename T, typename = typename std::enable_if<std::is_enum<T>::value>::type>
sf::Packet& operator>>(sf::Packet& roPacket, T& reMsgType)
{
    typename std::underlying_type<T>::type xMsgType;
    roPacket >> xMsgType;
    reMsgType = static_cast<T>(xMsgType);

    return roPacket;
}

#endif //BATTLESHIP_CLIENT_CONSTANTS_H
