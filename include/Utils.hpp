/**
 * @file Utils.hpp
 * @author Bartosz Świrta
 * @brief Zawiera definicje GameStateEnum i PlayerEnum
 * @version 1.0
 * @date 2021-01-10
 * 
 * @copyright Copyright (c) 2021
 * 
 */
#pragma once

namespace ox
{
    /**
     * @brief Możliwe stany rozgrywki.
     * 
     */
    enum GameStateEnum
    {
        PREPARING,
        PLAYING,
        CIRCLE_WON,
        CROSS_WON,
        TIE,
    };

    /**
     * @brief Konkretny gracz lub jego brak.
     * 
     */
    enum PlayerEnum
    {
        CIRCLE_PLAYER,
        CROSS_PLAYER,
        NONE
    };

} // namespace ox
