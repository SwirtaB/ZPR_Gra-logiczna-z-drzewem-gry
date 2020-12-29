//
// Created by swirta on 28.12.2020.
//

#ifndef MODEL_HPP
#define MODEL_HPP

#include "../include/Queues.hpp"

class Model{
private:
    GameStateEnum gameState;
    GameField gameField;
    std::shared_ptr<Queues> queuesHandler;

public:
    Model(std::shared_ptr<Queues> queuesHandler_);
    InputMessage read_input();
    bool send_state();
    bool select_field(int x, int y, PlayerEnum player);
    void update_gameState();
    void set_winner(int x, int y);
    bool is_finished();
    void play_game();
    void start();
    void reset_game();
};

#endif //MODEL_HPP
