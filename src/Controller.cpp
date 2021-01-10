//
// Created by swirta on 28.12.2020.
//

#include "../include/Controller.hpp"
#include "../include/BotMove.hpp"

#include <chrono>
#include <thread>
#include <climits>
#include <fstream>

using namespace ox;

Controller::Controller(Config &config_, std::shared_ptr<MessageQueues> queuesHandler_)
    : gameState(PREPARING), messageQueues(queuesHandler_), config(config_)
{
    send_state();
}

void Controller::run()
{
    if (!try_load_saved_state())
    {
        init();
    }
    gameState = PLAYING;
    send_state();
    play_game();
}

void Controller::init()
{
    fieldBoard = FieldBoard();
    gameState = PLAYING;
    if (config.start == CROSS)
    {
        currentPlayer = CROSS_PLAYER;
    }
    else
    {
        currentPlayer = CIRCLE_PLAYER;
    }
}

PlayerInputMessage Controller::get_player_input()
{
    return messageQueues->wait_for_player_input();
}

bool Controller::need_player_input() const
{
    return gameState != PLAYING || currentPlayer == CROSS_PLAYER && !config.cross_is_bot || currentPlayer == CIRCLE_PLAYER && !config.circle_is_bot;
}

void Controller::send_state() const
{
    messageQueues->send_game_state(GameStateMessage(gameState, fieldBoard));
}

bool Controller::select_field(int x, int y, PlayerEnum player)
{
    switch (player)
    {
    case CIRCLE_PLAYER:
        return fieldBoard.circle_field(x, y);
    case CROSS_PLAYER:
        return fieldBoard.cross_field(x, y);
    default:
        return false;
    }
}

void Controller::flip_player()
{
    if (currentPlayer == CROSS_PLAYER)
    {
        currentPlayer = CIRCLE_PLAYER;
    }
    else
    {
        currentPlayer = CROSS_PLAYER;
    }
}

void Controller::exit()
{
    if (gameState == PLAYING)
    {
        try_save_state();
    }
}

void Controller::play_game()
{
    while (true)
    {
        if (need_player_input())
        {
            PlayerInputMessage message = get_player_input();
            switch (message.messageType)
            {
            case EXIT:
                return exit();
                break;

            case RESET_GAME:
                init();
                break;

            case INPUT:
                /*Weryfikacja czy wykonany przez gracza ruch byl poprawny*/
                if (select_field(message.x, message.y, currentPlayer))
                    flip_player();
                break;
            }
            gameState = fieldBoard.check_state();
            send_state();
        }
        else
        {
            std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();

            std::pair<int, int> move = bot::bot_move(fieldBoard, currentPlayer, config.bot_tactic, config.depth);

            std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
            std::cout << "Time difference = " << std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count() << "[µs]" << std::endl;

            std::this_thread::sleep_for(std::chrono::milliseconds(500));
            select_field(move.first, move.second, currentPlayer);
            flip_player();
            gameState = fieldBoard.check_state();
            send_state();
        }
    }
}

bool Controller::try_load_saved_state()
{
    try
    {
        std::ifstream save(config.save_path);
        std::optional<FieldBoard> loaded_gf = FieldBoard::try_read(save);
        if (!loaded_gf.has_value())
        {
            return false;
        }
        std::string player;
        PlayerEnum current_player;
        save >> player;
        if (player == "cross")
        {
            current_player = CROSS_PLAYER;
        }
        else if (player == "circle")
        {
            current_player = CIRCLE_PLAYER;
        }
        else
        {
            return false;
        }

        fieldBoard = loaded_gf.value();
        currentPlayer = current_player;
        gameState = PLAYING;
        return true;
    }
    catch (std::exception &e)
    {
        return false;
    }
}

bool Controller::try_save_state() const
{
    try
    {
        std::ofstream save(config.save_path);
        fieldBoard.write(save);
        if (currentPlayer == CROSS_PLAYER)
        {
            save << "cross\n";
        }
        else
        {
            save << "circle\n";
        }
        return true;
    }
    catch (std::exception &e)
    {
        return false;
    }
}