//
// Created by swirta on 28.12.2020.
//

#ifndef MODEL_HPP
#define MODEL_HPP

#include "../include/Queues.hpp"
#include "../include/Config.hpp"

namespace ox {

class Model{
private:
    GameStateEnum gameState;
    GameField gameField;
    std::shared_ptr<Queues> queuesHandler;
    Config config;
    PlayerEnum currentPlayer;

public:
    Model(Config& config, std::shared_ptr<Queues> queuesHandler_);
    void init();
    InputMessage read_input();
    bool send_state();
    bool select_field(int x, int y, PlayerEnum player);
    void flip_player();
    //dodana
    GameStateEnum check_winner(GameField&);
    void update_gameState();
    void set_winner(int x, int y);
    bool is_finished();
    bool is_playing();
    void play_game();
    void start();
    void reset_game();
    bool is_waiting_for_player_input();
    //zmodyfikowana
    bool is_board_full(GameField);

    std::pair<int, int> bot_move(PlayerEnum, int );
    /*Ffunkcja zwroci -4 gdy w rozpatrywanym stanie wygra CIRCLE
     *Funkcja zwraca 4 gdy w rozpatrywanym stanie wygra CROSS*/
    int estimate_move(GameField, PlayerEnum, int, int);
    /*algorytm budowania i przeszukiwania w glab drzewa gry, zastosowalem optymalizacje, dzieki czemu nie rozpatruje galezi dajacych gorszy wynik*/
    int minimax(int x, int y, int depth_, int alpha, int beta, GameField gameField, PlayerEnum player);
};

}
#endif //MODEL_HPP
/*Potrzebowalem sprawdzac stan gry na tymczasowych planszach, ktore ropzatruje algorytm, dlatego zmodyfikowalem is_board_full tak, ze jako argument przyjmuje plansze
 *Dodalem tez check_winner ktore jest wlasciwie klonem update_gameState, ale nie modyfikuje stanu gry w modelu, tylko zwraca ten stan - to mozna poprawic by bylo lepiej*/