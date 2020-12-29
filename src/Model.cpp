//
// Created by swirta on 28.12.2020.
//

#include "../include/Model.hpp"

Model::Model(std::shared_ptr<Queues> queuesHandler_) : gameState(PREPARING), queuesHandler(queuesHandler_) {}
bool Model::send_state() {
    queuesHandler->gameStateQueue.push(std::make_pair(gameState, gameField));
    //ewentualnie jakieś dodatkowe operacje synchronizujące
}
InputMessage Model::read_input() {
    InputMessage message;
    if (!queuesHandler->messageQueue.empty()) {
        message = queuesHandler->messageQueue.front();
        queuesHandler->messageQueue.pop();
    }
    else message.messageType = MESSAGE_ERROR;
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
    gameState = PLAYING;
    play_game();
    //oczekiwanie na zresetowanie gry lub zamkniecie programu
}
void Model::play_game() {
    while(gameState == PLAYING){
        //chwilowo badanie warunku jest na aktywnym oczekiwaniu
        InputMessage message = read_input();
        while(message.messageType == MESSAGE_ERROR){
            message = read_input();
        }
        select_field(message.x, message.y, message.whoPerformedAction);
        update_gameState();
        send_state();
        if(is_finished()) return;
    }
}
