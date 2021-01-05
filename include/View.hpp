#pragma once

#include "../include/Queues.hpp"
#include "../include/Config.hpp"

#include <Mahi/Gui.hpp>
#include <Mahi/Util.hpp>

#include <optional>

namespace ox {

class View : public mahi::gui::Application {
public:
    View(ox::Config& config, std::shared_ptr<Queues> messageQueues);
    virtual ~View();

    void update() override;

private:
    std::shared_ptr<Queues> messageQueues;
    std::optional<std::pair<GameStateEnum, GameField>> lastState;
    ImVec2 fieldButtonSize;

    void update_preparing();
    void update_game_in_progress(GameField& fields);
    void update_game_finished(PlayerEnum winner);
    void update_game_state_error();
    bool field_button(int x, int y, FieldStateEnum state) const;
    void check_for_new_state();
    void send_input(InputMessage message) const;
};

}

