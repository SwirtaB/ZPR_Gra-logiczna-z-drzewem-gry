//
// Created by swirta on 28.12.2020.
//

#include "../include/Model.hpp"

#include <chrono>
#include <thread>
#include <climits>

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

GameStateEnum Model::check_winner(GameField& gameField) {
    if(gameField.get_field_state(0, 0) == gameField.get_field_state(0, 1) && gameField.get_field_state(0, 1) == gameField.get_field_state(0, 2) && gameField.get_field_state(0, 0) != EMPTY){
        if(gameField.get_field_state(0, 0) == CROSSED) return CROSS_WON;
        else return CIRCLE_WON;
    }
    else if(gameField.get_field_state(1, 0) == gameField.get_field_state(1, 1) && gameField.get_field_state(1, 1) == gameField.get_field_state(1, 2) && gameField.get_field_state(1, 0) != EMPTY){
        if(gameField.get_field_state(1, 0) == CROSSED) return CROSS_WON;
        else return CIRCLE_WON;
    }
    else if(gameField.get_field_state(2, 0) == gameField.get_field_state(2, 1) && gameField.get_field_state(2, 1)== gameField.get_field_state(2, 2) && gameField.get_field_state(2, 0) != EMPTY){
        if(gameField.get_field_state(2, 0) == CROSSED) return CROSS_WON;
        else return CIRCLE_WON;
    }
    else if(gameField.get_field_state(0, 0) == gameField.get_field_state(1, 0) && gameField.get_field_state(1, 0) == gameField.get_field_state(2, 0) && gameField.get_field_state(0, 0) != EMPTY){
        if(gameField.get_field_state(0, 0) == CROSSED) return CROSS_WON;
        else return CIRCLE_WON;
    }
    else if(gameField.get_field_state(0, 1) == gameField.get_field_state(1, 1) && gameField.get_field_state(1, 1) == gameField.get_field_state(2, 1) && gameField.get_field_state(0, 1) != EMPTY){
        if(gameField.get_field_state(0, 1) == CROSSED) return CROSS_WON;
        else return CIRCLE_WON;
    }
    else if(gameField.get_field_state(0, 2) == gameField.get_field_state(1, 2) && gameField.get_field_state(1, 2) == gameField.get_field_state(2, 2) && gameField.get_field_state(0, 2) != EMPTY){
        if(gameField.get_field_state(0, 2) == CROSSED) return CROSS_WON;
        else return CIRCLE_WON;
    }
    else if(gameField.get_field_state(0, 0) == gameField.get_field_state(1, 1) && gameField.get_field_state(1, 1) == gameField.get_field_state(2, 2) && gameField.get_field_state(0, 0) != EMPTY){
        if(gameField.get_field_state(0, 0) == CROSSED) return CROSS_WON;
        else return CIRCLE_WON;
    }
    else if(gameField.get_field_state(2, 0) == gameField.get_field_state(1, 1) && gameField.get_field_state(1, 1) == gameField.get_field_state(0, 2) && gameField.get_field_state(2, 0) != EMPTY){
        if(gameField.get_field_state(2, 0) == CROSSED) return CROSS_WON;
        else return CIRCLE_WON;
    }
    else if (is_board_full(gameField)) {
        return TIE;
    }
    else return PLAYING;
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
    else if (is_board_full(gameField)) {
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
                /*Weryfikacja czy wykonany przez gracza ruch byl poprawny*/
                if(select_field(message.x, message.y, currentPlayer))
                    flip_player();
                break;
            }
            update_gameState();
            send_state();
        } else {
            std::pair<int, int> move = bot_move(currentPlayer, config.depth);
            select_field(move.first, move.second, currentPlayer);
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

//modyfikuje
bool Model::is_board_full(GameField gameField) {
    for (int x = 0; x < 3; ++x) {
        for (int y = 0; y < 3; ++y) {
            if (gameField.get_field_state(x, y) == EMPTY) {
                return false;
            }
        }
    }
    return true;
}

std::pair<int, int> Model::bot_move(PlayerEnum player, int depth) {
    GameField tmpField = gameField;
    std::pair<int, int> bestMove;
    int bestScore = 0, score = 0;

    switch (player) {
        case CIRCLE_PLAYER:
            bestScore = INT_MAX;
            for(int y = 0; y < 3; ++y) {
                for (int x = 0; x < 3; ++x) {
                    if (gameField.get_field_state(x, y) == EMPTY) {
                        if(config.bot_tactic == HEURISTIC){
                            tmpField.circle_field(x, y);
                            score = estimate_move(tmpField, player, x, y);
                            tmpField.empty_field(x, y);
                        }
                        else{
                            tmpField.circle_field(x, y);
                            score = minimax(x, y, depth - 1, INT_MIN, INT_MAX, tmpField, CROSS_PLAYER);
                            tmpField.empty_field(x, y);
                        }
                        if (bestScore > score) {
                            bestScore = score;
                            bestMove.first = x;
                            bestMove.second = y;
                        }
                    }
                }
            }
            break;
        case CROSS_PLAYER:
            bestScore = INT_MIN;
            for(int y = 0; y < 3; ++y) {
                for (int x = 0; x < 3; ++x) {
                    if (gameField.get_field_state(x, y) == EMPTY) {
                        if(config.bot_tactic == HEURISTIC){
                            tmpField.cross_field(x, y);
                            score = estimate_move(tmpField, player, x, y);
                            tmpField.empty_field(x, y);
                        }
                        else{
                            tmpField.cross_field(x, y);
                            /*alpha = INT_MIN, beta = INT_MAX do alpha-beta pruning'u*/
                            score = minimax(x, y, depth - 1, INT_MIN, INT_MAX, tmpField, CIRCLE_PLAYER);
                            tmpField.empty_field(x, y);
                        }
                        if (bestScore < score) {
                            bestScore = score;
                            bestMove.first = x;
                            bestMove.second = y;
                        }
                    }
                }
            }
            break;
        default: break;
    }
    return bestMove;
}

//ten estymator nie jest najbardziej wyszukany, ale dziala.
int Model::estimate_move(GameField gameField, PlayerEnum player, int x, int y) {
    switch (check_winner(gameField)) {
        case CIRCLE_WON:
            return -4;
        case CROSS_WON:
            return 4;
        case TIE:
            return 0;
        default: break;
    }

    int bestScore = 0, score = 0, xCounter = 0, oCounter = 0, eCounter = 0;
    switch (player) {
        case CIRCLE_PLAYER:
            score = INT_MAX;
            /*sprawdzam wiersz*/
            for(int i = 0; i < 3; ++i){
                switch (gameField.get_field_state(i, y)) {
                    case EMPTY: ++eCounter;
                        break;
                    case CIRCLED: ++oCounter;
                        break;
                    case CROSSED: ++xCounter;
                        break;
                    default: break;
                }
            }
            if(oCounter == 1 && xCounter == 0) score = -1;
            else if(oCounter == 2 && xCounter == 0) score = -2;
            else if(xCounter == 2) score = -3;
            else score = 0;
            bestScore = std::min(bestScore, score);
            eCounter = 0;
            oCounter = 0;
            xCounter = 0;

            /*sprawdzam kolumne*/
            for(int i = 0; i < 3; ++i){
                switch (gameField.get_field_state(x, i)) {
                    case EMPTY: ++eCounter;
                        break;
                    case CIRCLED: ++oCounter;
                        break;
                    case CROSSED: ++xCounter;
                        break;
                    default: break;
                }
            }
            if(oCounter == 1 && xCounter == 0) score = -1;
            else if(oCounter == 2 && xCounter == 0) score = -2;
            else if(xCounter == 2) score = -3;
            else score = 0;
            bestScore = std::min(bestScore, score);
            eCounter = 0;
            oCounter = 0;
            xCounter = 0;

            /*sprawdzam przekatne*/
            if(x == 0 && y == 0 || x == 1 && y == 1 || x == 2 && y == 2){
                for(int i = 0, j = 0; i < 3; ++i, ++j){
                    switch (gameField.get_field_state(i, j)) {
                        case EMPTY: ++eCounter;
                            break;
                        case CIRCLED: ++oCounter;
                            break;
                        case CROSSED: ++xCounter;
                            break;
                        default: break;
                    }
                }
                if(oCounter == 1 && xCounter == 0) score = -1;
                else if(oCounter == 2 && xCounter == 0) score = -2;
                else if(xCounter == 2) score = -3;
                else score = 0;
                bestScore = std::min(bestScore, score);
                eCounter = 0;
                oCounter = 0;
                xCounter = 0;
            }

            if(x == 2 && y == 0 || x == 1 && y == 1 || x == 0 && y == 2) {
                for (int i = 2, j = 0; i >= 0; --i, ++j) {
                    switch (gameField.get_field_state(i, j)) {
                        case EMPTY:
                            ++eCounter;
                            break;
                        case CIRCLED:
                            ++oCounter;
                            break;
                        case CROSSED:
                            ++xCounter;
                            break;
                        default:
                            break;
                    }
                }
                if (oCounter == 1 && xCounter == 0) score = -1;
                else if (oCounter == 2 && xCounter == 0) score = -2;
                else if (xCounter == 2) score = -3;
                else score = 0;
                bestScore = std::min(bestScore, score);
            }
            break;

        case CROSS_PLAYER:
            score = INT_MIN;
            /*sprawdzam wiersz*/
            for(int i = 0; i < 3; ++i){
                switch (gameField.get_field_state(i, y)) {
                    case EMPTY: ++eCounter;
                        break;
                    case CIRCLED: ++oCounter;
                        break;
                    case CROSSED: ++xCounter;
                        break;
                    default: break;
                }
            }
            if(xCounter == 1 && oCounter == 0) score = 1;
            else if(xCounter == 2 && oCounter == 0) score = 2;
            else if(oCounter == 2) score = 3;
            else score = 0;
            bestScore = std::max(bestScore, score);
            eCounter = 0;
            oCounter = 0;
            xCounter = 0;

            /*sprawdzam kolumne*/
            for(int i = 0; i < 3; ++i){
                switch (gameField.get_field_state(x, i)) {
                    case EMPTY: ++eCounter;
                        break;
                    case CIRCLED: ++oCounter;
                        break;
                    case CROSSED: ++xCounter;
                        break;
                    default: break;
                }
            }
            if(xCounter == 1 && oCounter == 0) score = 1;
            else if(xCounter == 2 && oCounter == 0) score = 2;
            else if(oCounter == 2) score = 3;
            else score = 0;
            bestScore = std::max(bestScore, score);
            eCounter = 0;
            oCounter = 0;
            xCounter = 0;

            /*sprawdzam przekatne*/
            if(x == 0 && y == 0 || x == 1 && y == 1 || x == 2 && y == 2){
                for(int i = 0, j = 0; i < 3; ++i, ++j){
                    switch (gameField.get_field_state(i, j)) {
                        case EMPTY: ++eCounter;
                            break;
                        case CIRCLED: ++oCounter;
                            break;
                        case CROSSED: ++xCounter;
                            break;
                        default: break;
                    }
                }
                if(xCounter == 1 && oCounter == 0) score = 1;
                else if(xCounter == 2 && oCounter == 0) score = 2;
                else if(oCounter == 2) score = 3;
                else score = 0;
                bestScore = std::max(bestScore, score);
                eCounter = 0;
                oCounter = 0;
                xCounter = 0;
            }

            if(x == 2 && y == 0 || x == 1 && y == 1 || x == 0 && y == 2) {
                for (int i = 2, j = 0; i >= 0; --i, ++j) {
                    switch (gameField.get_field_state(i, j)) {
                        case EMPTY:
                            ++eCounter;
                            break;
                        case CIRCLED:
                            ++oCounter;
                            break;
                        case CROSSED:
                            ++xCounter;
                            break;
                        default:
                            break;
                    }
                }
                if (xCounter == 1 && oCounter == 0) score = 1;
                else if (xCounter == 2 && oCounter == 0) score = 2;
                else if (oCounter == 2) score = 3;
                else score = 0;
                bestScore = std::max(bestScore, score);
            }
            break;
        default:
            break;
    }
    return bestScore;
}
int Model::minimax(int x, int y, int depth, int alpha, int beta, GameField gameField, PlayerEnum player) {
    if(!depth || check_winner(gameField) != PLAYING){
        return estimate_move(gameField, player, x, y);
    }
    int bestScore = 0, score = 0;
    switch (player) {
        case CIRCLE_PLAYER:
            bestScore = INT_MAX;
            for(int y = 0; y < 3; ++y) {
                for (int x = 0; x < 3; ++x) {
                    if (gameField.get_field_state(x, y) == EMPTY) {
                        gameField.circle_field(x, y);
                        score = minimax(x, y, depth - 1, alpha, beta, gameField, CROSS_PLAYER);
                        gameField.empty_field(x, y);
                        //alpha-beta pruning (dwie linie)
                        beta = std::min(beta, score);
                        if(beta <= alpha) return bestScore;
                        bestScore = std::min(score, bestScore);
                    }
                }
            }
            break;
        case CROSS_PLAYER:
            bestScore = INT_MIN;
            for(int y = 0; y < 3; ++y) {
                for (int x = 0; x < 3; ++x) {
                    if (gameField.get_field_state(x, y) == EMPTY) {
                        gameField.cross_field(x, y);
                        score = minimax(x, y, depth - 1, alpha, beta, gameField, CIRCLE_PLAYER);
                        gameField.empty_field(x, y);
                        //alpha-beta pruning (dwie linie)
                        alpha = std::max(alpha, score);
                        if(beta <= alpha) return bestScore;
                        bestScore = std::max(score, bestScore);
                    }
                }
            }
            break;
        default: break;
    }
    return bestScore;
}