//
// Created by swirta on 28.12.2020.
//
#pragma once

#include "Utils.hpp"
#include <array>
#include <iostream>
#include <optional>

namespace ox
{
    /// Możliwe stany pola w grze.
    enum FieldState
    {
        EMPTY,
        CIRCLED,
        CROSSED,
        FIELD_STATE_ERROR
    };

    /// Pojedyńcze pole w grze.
    class Field
    {
    public:
        /// Utworzenie pola o podanym stanie.
        Field(FieldState = EMPTY);
        /// Wyczyść pole.
        void empty();
        /// Zaznacz pole kółkiem.
        void circle();
        /// Zaznacz pole krzyżykiem.
        void cross();
        /// Czy pole jest puste.
        bool is_empty() const;
        /// Czy na polu jest krzyżyk.
        bool is_crossed() const;
        /// Czy na polu jest kółko.
        bool is_circled() const;
        /// Zwróć stan pola.
        const FieldState get_state() const;

    private:
        /// Stan pola.
        FieldState fieldState;
    };

    /// Plansza gry o rozmiarze 3x3.
    class FieldBoard
    {
    public:
        /// Resetowanie planszy - ustawia wszyskie pola na puste.
        void reset_game_fields();
        /// Postawienie krzyżyka na danym polu.
        bool cross_field(int x, int y);
        /// Postawnienie kółka na danym polu.
        bool circle_field(int x, int y);
        /// Wyczyszczenie danego pola.
        bool empty_field(int x, int y);

        /// Zwróć stan danego pola.
        const FieldState get_field_state(int x, int y) const;
        /// Czy plansza jest pełna - żadne pole nie jest puste.
        bool is_board_full() const;
        /// Sprawdź stan planszy - jeden z graczy wygrał / jest remis / gra trwa.
        const GameStateEnum check_state() const;

        /// Spróbuj odczytać zapisany wcześniej stan planszy ze strumienia.
        static std::optional<FieldBoard> try_read(std::istream &);
        /// \brief Zapisz stan planszy do strumienia.
        /// \details
        /// Zapisuje kolejne stany pól oddzielone spacjami i nowymi liniami tak,
        /// aby zapis był czytelny w tekście dla człowieka.
        void write(std::ostream &) const;

    private:
        /// Pola na planszy w tablicy interpretowanej później jako tablica dwuwymiarowa 3x3.
        std::array<Field, 9> fieldArray;
    };

} // namespace ox
