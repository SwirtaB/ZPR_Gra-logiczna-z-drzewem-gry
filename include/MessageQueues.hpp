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
    /// Wiadomość wysyłana od kontrolera do widoku.
    struct GameStateMessage
    {
        GameStateMessage(GameStateEnum gs, FieldBoard fb)
            : gameStateEnum(gs), fieldBoard(fb) {}

        GameStateEnum gameStateEnum;
        FieldBoard fieldBoard;
    };

    /// Typy wiadomości od widoku do kontrolera.
    enum PlayerInputMessageType
    {
        EXIT,
        RESET_GAME,
        INPUT
    };

    /// Wiadomość od widoku do kontrolera.
    class PlayerInputMessage
    {
    public:
        /// Typ wysyłanej wiadomości
        PlayerInputMessageType messageType;
        /// Współrzędne pola gdy typem wiadomości jest INPUT.
        int x;
        /// Współrzędne pola gdy typem wiadomości jest INPUT.
        int y;

        PlayerInputMessage(PlayerInputMessageType messageType_, int x_, int y_)
            : messageType(messageType_), x(x_), y(y_) {}
    };

    /// \brief Współdzielony pośrednik komunikacji pomiędzy widokiem a kontrolerem.
    /// \details
    /// Widok wysyła tylko PlayerInputMessage i odbiera tylko GameStateMessage.
    /// Kontroler tylko wysyła tylko GameStateMessage i odbiera tylko PlayerInputMessage.
    class MessageQueues
    {
    public:
        /// \brief Wysłanie wiadomości o akcji gracza do kolejki.
        /// \details
        /// Wkłada do kolejki podaną akcję i sygnalizuje condvar
        /// czekający na to aż kolejka przestanie być pusta.
        void send_player_input(const PlayerInputMessage input);
        /// \brief Odebranie wiadomości o akcji gracza z kolejki.
        /// \details
        /// Jeśli kolejka jest pusta czeka na condvarze aż kolejka nie będzie pusta.
        const PlayerInputMessage wait_for_player_input();

        /// Wysłanie nowego stanu gry do kolejki.
        void send_game_state(const GameStateMessage state);
        /// Wyciągnięcie nowego stanu gry z kolejki stanów gry jeśli nie jest pusta.
        const std::optional<const GameStateMessage> check_for_game_state();

    private:
        /// Kolejka z wiadomościami o akcjach gracza od widoku do kontrolera.
        std::queue<PlayerInputMessage> playerInputQueue;
        /// Condvar do oczekiwania na niepustą kolejkę akcji gracza.
        std::condition_variable playerInputWaitCondition;
        /// Mutex do oczekiwania na niepustą kolejkę akcji gracza.
        std::mutex playerInputQueueMutex;

        /// Kolejka z wiadmościami o stanie gry od kontorlera do widoku.
        std::queue<GameStateMessage> gameStateQueue;
    };

} // namespace ox
