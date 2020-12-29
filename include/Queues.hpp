//
// Created by swirta on 29.12.2020.
//

#ifndef QUEUES_HPP
#define QUEUES_HPP

#include "Field.hpp"
#include <queue>
#include <memory>

class InputMessage {
public:
    MessageTypeEnum messageType;
    PlayerEnum whoPerformedAction;
    int x;
    int y;

    InputMessage() {}
    InputMessage(MessageTypeEnum messageType_, PlayerEnum whoPerformedAction_ , int x_, int y_) : messageType(messageType_), whoPerformedAction(whoPerformedAction_), x(x_), y(y_) {}
};

typedef struct Queues{
    std::queue<InputMessage> messageQueue;
    std::queue<std::pair<GameStateEnum, GameField>> gameStateQueue;
}Queues;
#endif //QUEUES_HPP
