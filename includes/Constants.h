//
// Created by tudor on 5/8/2020.
//

#ifndef BATTLESHIP_CLIENT_CONSTANTS_H
#define BATTLESHIP_CLIENT_CONSTANTS_H

#include <string>
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
const short CLIENT_SET_BOAT = 103;

const std::string CLIENT_MESSAGE_PREFIX = "CLIENT<<< ";
#endif //BATTLESHIP_CLIENT_CONSTANTS_H
