//
// Created by swirta on 29.12.2020.
//

#ifndef QUEUES_HPP
#define QUEUES_HPP

#include "Field.hpp"
#include <queue>
#include <memory>

namespace ox {

class InputMessage {
public:
    MessageTypeEnum messageType;
    int x;
    int y;

    InputMessage() {}
    InputMessage(MessageTypeEnum messageType_, int x_, int y_) : messageType(messageType_), x(x_), y(y_) {}
};

struct Queues {
    std::queue<InputMessage> messageQueue;
    std::queue<std::pair<GameStateEnum, GameField>> gameStateQueue;
};

}

#endif //QUEUES_HPP
