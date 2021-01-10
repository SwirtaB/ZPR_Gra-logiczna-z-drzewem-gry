#include "../include/MessageQueues.hpp"

#include <chrono>

using namespace ox;

void MessageQueues::send_player_input(const PlayerInputMessage input)
{
    {
        std::lock_guard<std::mutex> lg(playerInputQueueMutex);
        playerInputQueue.push(input);
    }
    playerInputWaitCondition.notify_one();
}

const PlayerInputMessage MessageQueues::wait_for_player_input()
{
    std::unique_lock<std::mutex> lk(playerInputQueueMutex);
    std::queue<PlayerInputMessage> *queue = &this->playerInputQueue;
    playerInputWaitCondition.wait(lk, [queue] { return !queue->empty(); });

    const PlayerInputMessage pi = playerInputQueue.front();
    playerInputQueue.pop();
    return pi;
}

void MessageQueues::send_game_state(const GameStateMessage state)
{
    gameStateQueue.push(state);
}

const std::optional<const GameStateMessage> MessageQueues::check_for_game_state()
{
    if (gameStateQueue.empty())
    {
        return std::optional<GameStateMessage>();
    }
    else
    {
        const GameStateMessage gs = gameStateQueue.front();
        gameStateQueue.pop();
        return gs;
    }
}
