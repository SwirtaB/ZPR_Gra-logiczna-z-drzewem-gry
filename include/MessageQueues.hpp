//
// Created by swirta on 29.12.2020.
//
#pragma once

#include "Field.hpp"
#include <queue>
#include <memory>
#include <condition_variable>

namespace ox
{
    struct GameStateMessage
    {
        GameStateMessage(GameStateEnum gs, FieldBoard fb)
            : gameStateEnum(gs), fieldBoard(fb) {}

        GameStateEnum gameStateEnum;
        FieldBoard fieldBoard;
    };

    enum PlayerInputMessageType
    {
        EXIT,
        RESET_GAME,
        INPUT
    };

    class PlayerInputMessage
    {
    public:
        PlayerInputMessageType messageType;
        int x;
        int y;

        PlayerInputMessage(PlayerInputMessageType messageType_, int x_, int y_)
            : messageType(messageType_), x(x_), y(y_) {}
    };

    class MessageQueues
    {
    public:
        // MessageQueues() : playerInputMutex(), playerInputLock(playerInputMutex) {}

        void send_player_input(const PlayerInputMessage input);
        const PlayerInputMessage wait_for_player_input();

        void send_game_state(const GameStateMessage state);
        const std::optional<const GameStateMessage> check_for_game_state();

    private:
        std::queue<PlayerInputMessage> playerInputQueue;
        std::condition_variable playerInputWaitCondition;
        std::mutex playerInputQueueMutex;

        std::queue<GameStateMessage> gameStateQueue;
    };

} // namespace ox
