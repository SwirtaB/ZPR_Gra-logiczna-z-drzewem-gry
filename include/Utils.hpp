//
// Created by swirta on 28.12.2020.
//

#ifndef UTILS_HPP
#define UTILS_HPP

namespace ox {

enum FieldStateEnum{
    EMPTY, CIRCLED, CROSSED, FIELD_STATE_ERROR
};
enum GameStateEnum{
    PREPARING, PLAYING, CIRCLE_WON, CROSS_WON, TIE, GAME_STATE_ERROR
};
enum PlayerEnum{
    CIRCLE_PLAYER, CROSS_PLAYER, NONE
};
enum MessageTypeEnum{
    EXIT, RESET_GAME, INPUT
};

}

#endif //UTILS_HPP
