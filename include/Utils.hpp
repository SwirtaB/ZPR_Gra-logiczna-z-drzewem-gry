//
// Created by swirta on 28.12.2020.
//
#pragma once

namespace ox
{
    /// Możliwe stany rozgrywki.
    enum GameStateEnum
    {
        PREPARING,
        PLAYING,
        CIRCLE_WON,
        CROSS_WON,
        TIE,
    };

    /// Konkretny gracz lub jego brak.
    enum PlayerEnum
    {
        CIRCLE_PLAYER,
        CROSS_PLAYER,
        NONE
    };

} // namespace ox
