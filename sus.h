#pragma once
#ifndef SUS_CLASSES_H
#define SUS_CLASSES_H

#include "BoardGame_Classes.h"
#include <vector>
#include <string>
#include <iostream>
using namespace std;

class SUS_Board : public Board<char> {
private:
    char blank_symbol = '.';

public:
    SUS_Board();
    static int count_sequences_in_matrix(const std::vector<std::vector<char>>& mat, char symbol);

    bool update_board(Move<char>* move);
    bool is_win(Player<char>* player) { return false; }
    bool is_lose(Player<char>* player) { return false; }
    bool is_draw(Player<char>* player);
    bool game_is_over(Player<char>* player);
    int count_sequences(char s);
};

//  AI player
class SUS_AI : public Player<char> {
public:
    SUS_AI(string name, char symbol)
        : Player<char>(name, symbol, PlayerType::AI) {}

    Move<char>* get_best_move() {
        auto mat = this->boardPtr->get_board_matrix();
        int bestX = -1, bestY = -1;
        int bestValue = -999;

        for (int i = 0; i < this->boardPtr->get_rows(); i++) {
            for (int j = 0; j < this->boardPtr->get_columns(); j++) {

                if (mat[i][j] == '.') {

                    mat[i][j] = this->symbol;
                    int gain = evaluate(mat, this->symbol);
                    mat[i][j] = '.'; 

                    if (gain > bestValue) {
                        bestValue = gain;
                        bestX = i;
                        bestY = j;
                    }
                }
            }
        }
        if (bestX == -1) return nullptr;
        return new Move<char>(bestX, bestY, this->symbol);
    }

private:
    int evaluate(const std::vector<std::vector<char>>& mat, char me);
};
class SUS_UI : public UI<char> {
public:
    SUS_UI() : UI<char>("Welcome to SUS Game", 3) {}
    Player<char>* create_player(string& name, char symbol, PlayerType type) override {
        if (type == PlayerType::AI)
            return new SUS_AI(name, symbol);
        return new Player<char>(name, symbol, type);
    }

    Player<char>** setup_players() override;

    Move<char>* get_move(Player<char>* player) override {
        if (player->get_type() == PlayerType::AI) {
            cout << player->get_name() << " (AI) is thinking...\n";
            return static_cast<SUS_AI*>(player)->get_best_move();
        }

        int x, y;
        cout << player->get_name() << " Enter x y: ";
        cin >> x >> y;
        return new Move<char>(x, y, player->get_symbol());
    }
};

#endif
