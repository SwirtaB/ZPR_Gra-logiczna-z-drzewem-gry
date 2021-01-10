//
// Created by swirta on 28.12.2020.
//
#pragma once

namespace ox
{
    enum GameStateEnum
    {
        PREPARING,
        PLAYING,
        CIRCLE_WON,
        CROSS_WON,
        TIE,
        GAME_STATE_ERROR
    };

    enum PlayerEnum
    {
        CIRCLE_PLAYER,
        CROSS_PLAYER,
        NONE
    };

} // namespace ox
