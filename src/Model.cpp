//
// Created by swirta on 28.12.2020.
//

#include "../include/Model.hpp"

#include <chrono>
#include <thread>

using namespace ox;

Model::Model(Config& config_, std::shared_ptr<Queues> queuesHandler_)
: gameState(PREPARING)
, queuesHandler(queuesHandler_)
, config(config_)
{
    send_state();
}

void Model::init() {
    gameField = GameField();
    gameState = PLAYING;
    if (config.start == CROSS) {
        currentPlayer = CROSS_PLAYER;
    } else {
        currentPlayer = CIRCLE_PLAYER;
    }
}

bool Model::send_state() {
    queuesHandler->gameStateQueue.push(std::make_pair(gameState, gameField));
    //ewentualnie jakieś dodatkowe operacje synchronizujące
    return true;
}

InputMessage Model::read_input() {
    InputMessage message;
    while (queuesHandler->messageQueue.empty()) {
        std::this_thread::sleep_for(std::chrono::milliseconds(10));
    }
    message = queuesHandler->messageQueue.front();
    queuesHandler->messageQueue.pop();
    return message;
}

bool Model::select_field(int x, int y, PlayerEnum player) {
    switch (player) {
        case CIRCLE_PLAYER:
            return gameField.circle_field(x, y);
        case CROSS_PLAYER:
            return gameField.cross_field(x, y);
        default:
            return false;
    }
}

void Model::flip_player() {
    if (currentPlayer == CROSS_PLAYER) {
        currentPlayer = CIRCLE_PLAYER;
    } else {
        currentPlayer = CROSS_PLAYER;
    }
}

void Model::update_gameState() {
    if(gameField.get_field_state(0, 0) == gameField.get_field_state(0, 1) && gameField.get_field_state(0, 1) == gameField.get_field_state(0, 2) && gameField.get_field_state(0, 0) != EMPTY){
        set_winner(0, 0);
    }
    else if(gameField.get_field_state(1, 0) == gameField.get_field_state(1, 1) && gameField.get_field_state(1, 1) == gameField.get_field_state(1, 2) && gameField.get_field_state(1, 0) != EMPTY){
        set_winner(1, 0);
    }
    else if(gameField.get_field_state(2, 0) == gameField.get_field_state(2, 1) && gameField.get_field_state(2, 1)== gameField.get_field_state(2, 2) && gameField.get_field_state(2, 0) != EMPTY){
        set_winner(2, 0);
    }
    else if(gameField.get_field_state(0, 0) == gameField.get_field_state(1, 0) && gameField.get_field_state(1, 0) == gameField.get_field_state(2, 0) && gameField.get_field_state(0, 0) != EMPTY){
        set_winner(0, 0);
    }
    else if(gameField.get_field_state(0, 1) == gameField.get_field_state(1, 1) && gameField.get_field_state(1, 1) == gameField.get_field_state(2, 1) && gameField.get_field_state(0, 1) != EMPTY){
        set_winner(0, 1);
    }
    else if(gameField.get_field_state(0, 2) == gameField.get_field_state(1, 2) && gameField.get_field_state(1, 2) == gameField.get_field_state(2, 2) && gameField.get_field_state(0, 2) != EMPTY){
        set_winner(0, 2);
    }
    else if(gameField.get_field_state(0, 0) == gameField.get_field_state(1, 1) && gameField.get_field_state(1, 1) == gameField.get_field_state(2, 2) && gameField.get_field_state(0, 0) != EMPTY){
        set_winner(0, 0);
    }
    else if(gameField.get_field_state(2, 0) == gameField.get_field_state(1, 1) && gameField.get_field_state(1, 1) == gameField.get_field_state(0, 2) && gameField.get_field_state(2, 0) != EMPTY){
        set_winner(2, 0);
    }
    else if (is_board_full()) {
        gameState = TIE;
    }
}

void Model::set_winner(int x, int y) {
    if(gameState != PLAYING){
        return;
    }
    if(gameField.get_field_state(x, y) == CROSSED)
        gameState = CROSS_WON;
    else gameState = CIRCLE_WON;
}

bool Model::is_finished() {
    if(gameState == CIRCLE_WON || gameState == CIRCLE_WON)
        return true;
    else return false;
}

void Model::start() {
    init();
    gameState = PLAYING;
    send_state();
    play_game();
}

void Model::play_game() {
    bool exit = false;
    while (!exit) {
        if (is_waiting_for_player_input()) {
            InputMessage message = read_input();
            switch (message.messageType) {
            case EXIT:
                // tutaj zapis stanu gry
                exit = true;
                break;
            
            case RESET_GAME:
                init();
                break;

            case INPUT:
                select_field(message.x, message.y, currentPlayer);
                flip_player();
                break;
            }
            update_gameState();
            send_state();
        } else {
            // tutaj wczytamy ruch bota
            // move = bot_move(x, y, currentPlayer);
            // select_field(move.x, move.y, currentPlayer);
            flip_player();
            std::this_thread::sleep_for(std::chrono::milliseconds(500));
            update_gameState();
            send_state();
        }
    }
}

bool Model::is_waiting_for_player_input() {
    return  gameState != PLAYING
        || currentPlayer == CROSS_PLAYER && !config.cross_is_bot
        || currentPlayer == CIRCLE_PLAYER && !config.circle_is_bot;
}

bool Model::is_board_full() {
    for (int x = 0; x < 3; ++x) {
        for (int y = 0; y < 3; ++y) {
            if (gameField.get_field_state(x, y) == EMPTY) {
                return false;
            }
        }
    }
    return true;
}