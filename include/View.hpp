#pragma once

#include "../include/MessageQueues.hpp"
#include "../include/Config.hpp"

#include <Mahi/Gui.hpp>
#include <Mahi/Util.hpp>

#include <optional>

namespace ox
{

    /// \brief Widok gry.
    /// Wyświetla interfejs gracza i wysyła wykonywane przez niego akcje do kontrolera.
    class View : public mahi::gui::Application
    {
    public:
        /// \brief Konstruktor widoku z podaną konfiguracją.
        /// Komunikuje się z widokiem za pomocą podanego wspólnego pośrednika.
        View(ox::Config &config, std::shared_ptr<MessageQueues> messageQueues);
        virtual ~View();
        /// Uruchamia widok, przejmuje wątek na czas działania.
        void run() { mahi::gui::Application::run(); }

    private:
        /// Pośrednik komunikacji z kontrolerem.
        std::shared_ptr<MessageQueues> messageQueues;
        /// Ostatni stan gry otrzymany od kontrolera.
        std::optional<GameStateMessage> lastState;
        
        /// \brief Funkcja aktualizacji interfejsu gracza.
        /// Jest wykonywana w pętli, ponieważ jest to interfejs typu immidiate mode GUI
        void update() override;
        /// \brief Aktualizacja interfejsu w stanie gry PREPARING.
        /// Wyświetla pust panel.
        void update_preparing();
        /// \brief Aktualizacja interfejsu w stanie gry IN_PROGRESS.
        /// Wyświetla planszę gry i pozwala graczowi wybierać pole.
        void update_game_in_progress(FieldBoard &fields);
        /// \brief Aktualizacja interfejsu w stanie gry FINISHED.
        /// Wyświetla informację o zwycięzcy i pozwala wywołac kolejną rozgrywkę.
        void update_game_finished(PlayerEnum winner);

        /// Oblicza współczynnik skalowania tekstu w zależności od rozmiaru okna.
        float get_font_scale() const;
        /// Wyświetla guzik na planszy w podanym stanie.
        bool field_button(FieldState state) const;
        /// Sprawdza czy przyszedł nowy stan od kontrolera.
        void check_for_new_state();
        /// Wysyła akcję gracza do kontrolera.
        void send_player_input(PlayerInputMessage message) const;
    };

} // namespace ox
