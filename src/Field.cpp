//
// Created by swirta on 28.12.2020.
//

#include "../include/Field.hpp"

using namespace ox;

bool in_range(int low, int high, int value)
{
    return (value - low) * (value - high) <= 0;
}

/*----------------------------------Field----------------------------------*/
Field::Field(FieldState initState) : fieldState(initState) {}
void Field::empty()
{
    fieldState = EMPTY;
}

void Field::circle()
{
    fieldState = CIRCLED;
}

void Field::cross()
{
    fieldState = CROSSED;
}

bool Field::is_empty() const
{
    if (fieldState == EMPTY)
        return true;
    else
        return false;
}

bool Field::is_crossed() const
{
    if (fieldState == CROSSED)
        return true;
    else
        return false;
}

bool Field::is_circled() const
{
    if (fieldState == CIRCLED)
        return true;
    else
        return false;
}

const FieldState Field::get_state() const
{
    return fieldState;
}

/*--------------------------------GameField--------------------------------*/
void FieldBoard::reset_game_fields()
{
    for (int i = 0; i < 9; ++i)
    {
        fieldArray[i].empty();
    }
}

bool FieldBoard::cross_field(int x, int y)
{
    if (!in_range(0, 3, x) || !in_range(0, 3, y))
        return false;
    int it = 3 * y + x;
    if (!fieldArray[it].is_empty())
        return false;
    fieldArray[it].cross();
    return true;
}

bool FieldBoard::circle_field(int x, int y)
{
    if (!in_range(0, 3, x) || !in_range(0, 3, y))
        return false;
    int it = 3 * y + x;
    if (!fieldArray[it].is_empty())
        return false;
    fieldArray[it].circle();
    return true;
}

bool FieldBoard::empty_field(int x, int y)
{
    if (!in_range(0, 3, x) || !in_range(0, 3, y))
        return false;
    int it = 3 * y + x;
    fieldArray[it].empty();
    return true;
}

bool FieldBoard::is_board_full() const
{
    for (int x = 0; x < 3; ++x)
    {
        for (int y = 0; y < 3; ++y)
        {
            if (get_field_state(x, y) == EMPTY)
            {
                return false;
            }
        }
    }
    return true;
}

const GameStateEnum FieldBoard::check_state() const
{
    if (get_field_state(0, 0) == get_field_state(0, 1) && get_field_state(0, 1) == get_field_state(0, 2) && get_field_state(0, 0) != EMPTY)
    {
        if (get_field_state(0, 0) == CROSSED)
            return CROSS_WON;
        else
            return CIRCLE_WON;
    }
    else if (get_field_state(1, 0) == get_field_state(1, 1) && get_field_state(1, 1) == get_field_state(1, 2) && get_field_state(1, 0) != EMPTY)
    {
        if (get_field_state(1, 0) == CROSSED)
            return CROSS_WON;
        else
            return CIRCLE_WON;
    }
    else if (get_field_state(2, 0) == get_field_state(2, 1) && get_field_state(2, 1) == get_field_state(2, 2) && get_field_state(2, 0) != EMPTY)
    {
        if (get_field_state(2, 0) == CROSSED)
            return CROSS_WON;
        else
            return CIRCLE_WON;
    }
    else if (get_field_state(0, 0) == get_field_state(1, 0) && get_field_state(1, 0) == get_field_state(2, 0) && get_field_state(0, 0) != EMPTY)
    {
        if (get_field_state(0, 0) == CROSSED)
            return CROSS_WON;
        else
            return CIRCLE_WON;
    }
    else if (get_field_state(0, 1) == get_field_state(1, 1) && get_field_state(1, 1) == get_field_state(2, 1) && get_field_state(0, 1) != EMPTY)
    {
        if (get_field_state(0, 1) == CROSSED)
            return CROSS_WON;
        else
            return CIRCLE_WON;
    }
    else if (get_field_state(0, 2) == get_field_state(1, 2) && get_field_state(1, 2) == get_field_state(2, 2) && get_field_state(0, 2) != EMPTY)
    {
        if (get_field_state(0, 2) == CROSSED)
            return CROSS_WON;
        else
            return CIRCLE_WON;
    }
    else if (get_field_state(0, 0) == get_field_state(1, 1) && get_field_state(1, 1) == get_field_state(2, 2) && get_field_state(0, 0) != EMPTY)
    {
        if (get_field_state(0, 0) == CROSSED)
            return CROSS_WON;
        else
            return CIRCLE_WON;
    }
    else if (get_field_state(2, 0) == get_field_state(1, 1) && get_field_state(1, 1) == get_field_state(0, 2) && get_field_state(2, 0) != EMPTY)
    {
        if (get_field_state(2, 0) == CROSSED)
            return CROSS_WON;
        else
            return CIRCLE_WON;
    }
    else if (is_board_full())
    {
        return TIE;
    }
    else
        return PLAYING;
}

const FieldState FieldBoard::get_field_state(int x, int y) const
{
    if (!in_range(0, 3, x) || !in_range(0, 3, y))
        return FIELD_STATE_ERROR;
    return fieldArray[3 * y + x].get_state();
}

std::optional<FieldBoard> FieldBoard::try_read(std::istream &in)
{
    FieldBoard gd;
    std::string input;
    for (int y = 0; y < 3; ++y)
    {
        for (int x = 0; x < 3; ++x)
        {
            in >> input;
            if (input.length() != 1)
            {
                return std::optional<FieldBoard>();
            }
            switch (input[0])
            {
            case '_':
                gd.empty_field(x, y);
                break;

            case 'x':
                gd.cross_field(x, y);
                break;

            case 'o':
                gd.circle_field(x, y);
                break;

            default:
                return std::optional<FieldBoard>();
            }
        }
    }
    return gd;
}

void FieldBoard::write(std::ostream &out) const
{
    for (int y = 0; y < 3; ++y)
    {
        for (int x = 0; x < 3; ++x)
        {
            switch (get_field_state(x, y))
            {
            case EMPTY:
                out << '_';
                break;

            case CROSSED:
                out << 'x';
                break;

            case CIRCLED:
                out << 'o';
                break;

            case FIELD_STATE_ERROR:
                out << 'e';
                break;
            }

            if (x != 2 || y != 2)
            {
                out << ' ';
            }
        }
        out << '\n';
    }
}