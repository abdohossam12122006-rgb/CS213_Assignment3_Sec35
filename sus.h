#pragma once
#ifndef SUS_CLASSES_H
#define SUS_CLASSES_H
#include "BoardGame_Classes.h" 
using namespace std;

class SUS_Board : public Board<char> {
private:
    char blank_symbol = '.';
    int score_p1 = 0;
    int score_p2 = 0;

public:
    SUS_Board();

    bool update_board(Move<char>* move);

    bool is_win(Player<char>* player);
    bool is_lose(Player<char>* player) { return false; }
    bool is_draw(Player<char>* player);
    bool game_is_over(Player<char>* player);

    int count_sequences(char s);
    int get_score(Player<char>* player);
};
#endif
class SUS_UI : public UI<char> {
public:
    SUS_UI() : UI<char>("Welcome to SUS Game  ", 3) {}
    Player<char>* create_player(string& name, char symbol, PlayerType type) {
        return new Player<char>(name, symbol, type);
    }

    Move<char>* get_move(Player<char>* player) {
        int x, y;
        cout << player->get_name() << " Enter x y: ";
        cin >> x >> y;
        return new Move<char>(x, y, player->get_symbol());
    }

};

