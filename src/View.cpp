#include "../include/View.hpp"

using namespace ox;

View::View(ox::Config& config, std::shared_ptr<Queues> messageQueues_)
: Application(640, 480, "OX")
, messageQueues(messageQueues_)
, lastState()
, fieldButtonSize(ImVec2(640 / 3, 480 / 3))
{
}

View::~View() {
    send_input(InputMessage(EXIT, 0, 0));
}

const int IMGUI_NO_TITLE_BAR = 1 << 0;
const int IMGUI_NO_RESIZE = 1 << 1;
const int IMGUI_NO_MOVE = 0 << 2;
const int IMGUI_NO_SCROLLBAR = 1 << 3;
const int IMGUI_NO_SCROLL_MOUSE = 1 << 4;

const int IMGUI_WINDOW_FLAGS =
    IMGUI_NO_TITLE_BAR |
    IMGUI_NO_RESIZE |
    IMGUI_NO_MOVE |
    IMGUI_NO_SCROLLBAR |
    IMGUI_NO_SCROLL_MOUSE;

void View::update() {
    ImGui::SetNextWindowSize(get_window_size());
    ImGui::SetNextWindowPos(get_window_pos());
    ImGui::Begin("window", nullptr,  IMGUI_WINDOW_FLAGS);

    check_for_new_state();

    if (lastState.has_value()) {
        GameStateEnum& state = std::get<GameStateEnum>(lastState.value());
        GameField& fields = std::get<GameField>(lastState.value());

        switch (state) {
        case PREPARING:
            update_preparing();
            break;

        case PLAYING:
            update_game_in_progress(fields);
            break;
        
        case CIRCLE_WON:
            update_game_finished(PlayerEnum::CIRCLE_PLAYER);
            break;

        case CROSS_WON:
            update_game_finished(PlayerEnum::CROSS_PLAYER);
            break;
        
        case TIE:
            update_game_finished(PlayerEnum::NONE);
            break;

        case GAME_STATE_ERROR:
            update_game_state_error();
            break;
        }
    } else {
        update_preparing();
    }

    ImGui::End();
}

void View::update_preparing() {
}

void View::update_game_in_progress(GameField& fields) {
    ImGui::Columns(3, nullptr, false);

    for (int y = 0; y < 3; ++y) {
        for (int x = 0; x < 3; ++x) {
            if (field_button(x, y, fields.get_field_state(x, y))) {
                send_input(InputMessage(INPUT, x, y));
                std::cout << x << " " << y << std::endl;
            }
            if (y != 3) ImGui::NextColumn();
            ImGui::PushID("b");
        }
    }
    for (int i = 0; i < 9; ++i) ImGui::PopID();
}

void View::update_game_finished(PlayerEnum player) {
    if (player == CIRCLE_PLAYER && ImGui::Button("Circle won!", get_window_size())
    || player == CROSS_PLAYER && ImGui::Button("Cross won!", get_window_size())
    || player == NONE && ImGui::Button("Tie!", get_window_size())) {
        send_input(InputMessage(RESET_GAME, 0, 0));
    }
}

void View::update_game_state_error() {
    ImGui::Text("Game State Error", get_window_size());
}

bool View::field_button(int x, int y, FieldStateEnum state) const {
    switch (state) {
        case EMPTY:
            return ImGui::Button("", fieldButtonSize);
        case CIRCLED:
            return ImGui::Button("O", fieldButtonSize);
        case CROSSED:
            return ImGui::Button("X", fieldButtonSize);
        default:
            return ImGui::Button("Error", fieldButtonSize);
    }
}

void View::check_for_new_state() {
    if (!messageQueues->gameStateQueue.empty()) {
        lastState = messageQueues->gameStateQueue.front();
        messageQueues->gameStateQueue.pop();
    }
}

void View::send_input(InputMessage message) const {
    messageQueues->messageQueue.push(message);
}