//
// Created by swirta on 28.12.2020.
//

#ifndef UTILS_HPP
#define UTILS_HPP

enum FieldStateEnum{
    EMPTY, CIRCLED, CROSSED, FIELD_STATE_ERROR
};
enum GameStateEnum{
    PREPARING, PLAYING, CIRCLE_WON, CROSS_WON, GAME_STATE_ERROR
};
enum PlayerEnum{
    CIRCLE_PLAYER, CROSS_PLAYER, NONE
};
enum MessageTypeEnum{
    RESET_GAME, INPUT, MESSAGE_ERROR
};
#endif //UTILS_HPP
