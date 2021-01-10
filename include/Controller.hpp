//
// Created by swirta on 28.12.2020.
//
#pragma once

#include "../include/MessageQueues.hpp"
#include "../include/Config.hpp"

namespace ox
{
    /// \brief Kontroler gry.
    /// Przyjmuje ruchy graczy, wywołuje ruchy botów i rozgrywa grę.
    class Controller
    {
    public:
        /// \brief Konstruktor kontrolera z podaną konfiguracją.
        /// Komunikuje się z widokiem za pomocą podanego wspólnego pośrednika.
        Controller(Config &config, std::shared_ptr<MessageQueues> queuesHandler_);
        /// Uruchamia kontroler, przejmuje wątek na czas działania.
        void run();

    private:
        /// Stan/faza razgrywki.
        GameStateEnum gameState;
        /// Obecny stan planszy gry.
        FieldBoard fieldBoard;
        /// Pośrednik komunikacji z widokiem.
        std::shared_ptr<MessageQueues> messageQueues;
        /// Konfiguracja gry.
        Config config;
        /// Który gracz ma wykonać teraz ruch.
        PlayerEnum currentPlayer;

        /// Zainicjuj rozgrywkę z pustą planszą.
        void init();
        /// Czy ruch ma wykonać gracz który nie jest botem.
        bool need_player_input() const;
        /// Odbierz akcję gracza od widoku.
        PlayerInputMessage get_player_input();
        /// Wyślij obacny stan gry do widoku.
        void send_state() const;
        /// Spróbuj wykonać ruch podanego gracza na danym polu.
        /// \return Zwraca true jeśli ruch został przyjęty, false jeśli nie.
        bool select_field(int x, int y, PlayerEnum player);
        /// Zamień gracza który będzie teraz wykonywał ruch. 
        void flip_player();
        /// Pętla rozgryki.
        void play_game();
        /// Zakończ pracę kontrolera, zapisz stan gry jeśli była w trakcie.
        void exit();

        /// Spróbuj wczytać stan gry z pliku o ścieżce podanej w pliku konfiguracyjnym.
        bool try_load_saved_state();
        /// Spróbuj zapisać stan gry do pliku o ścieżce podanej w pliku konfiguracyjnym.
        bool try_save_state() const;
    };

} // namespace ox