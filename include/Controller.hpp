//
// Created by swirta on 28.12.2020.
//
#pragma once

#include "../include/MessageQueues.hpp"
#include "../include/Config.hpp"

namespace ox
{

    class Controller
    {
    private:
        GameStateEnum gameState;
        FieldBoard fieldBoard;
        std::shared_ptr<MessageQueues> messageQueues;
        Config config;
        PlayerEnum currentPlayer;

        void init();
        bool need_player_input() const;
        PlayerInputMessage get_player_input();
        void send_state() const;
        bool select_field(int x, int y, PlayerEnum player);
        void flip_player();
        void play_game();
        void exit();

        bool try_load_saved_state();
        bool try_save_state() const;

    public:
        Controller(Config &config, std::shared_ptr<MessageQueues> queuesHandler_);
        void run();
    };

} // namespace ox