//
// Created by swirta on 28.12.2020.
//

#ifndef FIELD_HPP
#define FIELD_HPP

#include "Utils.hpp"
#include <array>

namespace ox {

class Field{
private:
    FieldStateEnum fieldState;
public:
    Field(FieldStateEnum = EMPTY);
    void empty();
    void circle();
    void cross();
    bool is_empty();
    bool is_crossed();
    bool is_circled();
    FieldStateEnum get_state();
};

class GameField{
private:
    std::array<Field, 9> fieldArray;
public:
    void reset_game_fields();
    bool cross_field(int x, int y);
    bool circle_field(int x, int y);
    bool empty_field(int x, int y);
    FieldStateEnum get_field_state(int x, int y);
};

}
#endif //FIELD_HPP
