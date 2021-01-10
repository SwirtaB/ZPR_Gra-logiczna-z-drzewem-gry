#pragma once

#include "../include/MessageQueues.hpp"
#include "../include/Config.hpp"

#include <Mahi/Gui.hpp>
#include <Mahi/Util.hpp>

#include <optional>

namespace ox
{

    class View : public mahi::gui::Application
    {
    public:
        View(ox::Config &config, std::shared_ptr<MessageQueues> messageQueues);
        virtual ~View();

        void update() override;

    private:
        std::shared_ptr<MessageQueues> messageQueues;
        std::optional<GameStateMessage> lastState;

        void update_preparing();
        void update_game_in_progress(FieldBoard &fields);
        void update_game_finished(PlayerEnum winner);
        void update_game_state_error();

        float get_font_scale() const;
        bool field_button(int x, int y, FieldState state) const;
        void check_for_new_state();
        void send_player_input(PlayerInputMessage message) const;
    };

} // namespace ox
