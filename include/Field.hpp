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
    enum FieldState
    {
        EMPTY,
        CIRCLED,
        CROSSED,
        FIELD_STATE_ERROR
    };

    class Field
    {
    public:
        Field(FieldState = EMPTY);
        void empty();
        void circle();
        void cross();
        bool is_empty() const;
        bool is_crossed() const;
        bool is_circled() const;
        const FieldState get_state() const;

    private:
        FieldState fieldState;
    };

    class FieldBoard
    {
    public:
        void reset_game_fields();
        bool cross_field(int x, int y);
        bool circle_field(int x, int y);
        bool empty_field(int x, int y);

        const FieldState get_field_state(int x, int y) const;
        bool is_board_full() const;
        const GameStateEnum check_state() const;

        static std::optional<FieldBoard> try_read(std::istream &);
        void write(std::ostream &) const;

    private:
        std::array<Field, 9> fieldArray;
    };

} // namespace ox
