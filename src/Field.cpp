//
// Created by swirta on 28.12.2020.
//

#include "../include/Field.hpp"

using namespace ox;

bool in_range(int low, int high, int value){
    return (value-low)*(value-high) <= 0;
}

/*----------------------------------Field----------------------------------*/
Field::Field(FieldStateEnum initState) : fieldState(initState) {}
void Field::empty() {
    fieldState = EMPTY;
}
void Field::circle() {
    fieldState = CIRCLED;
}
void Field::cross() {
    fieldState = CROSSED;
}
bool Field::is_empty(){
    if(fieldState == EMPTY) return true;
    else return false;
}
bool Field::is_crossed(){
    if(fieldState == CROSSED) return true;
    else return false;
}
bool Field::is_circled(){
    if(fieldState == CIRCLED) return true;
    else return false;
}
FieldStateEnum Field::get_state() {
    return fieldState;
}
/*--------------------------------GameField--------------------------------*/
void GameField::reset_game_fields() {
    for(int i = 0; i < 9; ++i){
        fieldArray[i].empty();
    }
}
bool GameField::cross_field(int x, int y) {
    if(!in_range(0,3,x) || !in_range(0,3,y))
        return false;
    int it = 3*y + x;
    if(!fieldArray[it].is_empty())
        return false;
    fieldArray[it].cross();
    return true;
}
bool GameField::circle_field(int x, int y) {
    if(!in_range(0,3,x) || !in_range(0,3,y))
        return false;
    int it = 3*y + x;
    if(!fieldArray[it].is_empty())
        return false;
    fieldArray[it].circle();
    return true;
}
bool GameField::empty_field(int x, int y) {
    if(!in_range(0,3,x) || !in_range(0,3,y))
        return false;
    int it = 3*y + x;
    fieldArray[it].empty();
    return true;
}
FieldStateEnum GameField::get_field_state(int x, int y) {
    if(!in_range(0,3,x) || !in_range(0,3,y))
        return FIELD_STATE_ERROR;
    return fieldArray[3*y + x].get_state();
}

std::optional<GameField> GameField::try_read(std::istream& in) {
    GameField gd;
    std::string input;
    for (int y = 0; y < 3; ++y) {
        for (int x = 0; x < 3; ++x) {
            in >> input;
            if (input.length() != 1) {
                return std::optional<GameField>();
            }
            switch (input[0]) {
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
                return std::optional<GameField>();
            }
        }
    }
    return gd;
}

void GameField::write(std::ostream& out) {
    for (int y = 0; y < 3; ++y) {
        for (int x = 0; x < 3; ++x) {
            switch (get_field_state(x, y)) {
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

            if (x != 2 || y != 2) {
                out << ' ';
            }
        }
        out << '\n';
    }
}