//
// Created by swirta on 28.12.2020.
//

#ifndef MODEL_HPP
#define MODEL_HPP

#include "../include/Queues.hpp"
#include "../include/Config.hpp"

namespace ox {

class Model{
private:
    GameStateEnum gameState;
    GameField gameField;
    std::shared_ptr<Queues> queuesHandler;
    Config config;
    PlayerEnum currentPlayer;

public:
    Model(Config& config, std::shared_ptr<Queues> queuesHandler_);
    void init();
    InputMessage read_input();
    bool send_state();
    bool select_field(int x, int y, PlayerEnum player);
    void flip_player();
    void update_gameState();
    void set_winner(int x, int y);
    bool is_finished();
    void play_game();
    void start();
    void reset_game();
    bool is_waiting_for_player_input();
    bool is_board_full();
};

}


#endif //MODEL_HPP
