#ifndef MISERE_UI_H
#define MISERE_UI_H

#include "BoardGame_Classes.h"
#include "MisereMinimaxPlayer.h"
#include <iostream>
#include <limits>

using namespace std;

class MisereUI : public UI<char> {
public:
    MisereUI() : UI<char>(3) {}

    void display_board(Board<char>* board) {
        cout << "\n  0   1   2\n";
        for (int i = 0; i < 3; i++) {
            cout << i << " ";
            for (int j = 0; j < 3; j++) {
                char cell = board->get_cell(i, j);
                cout << (cell == 0 ? '.' : cell);
                if (j < 2) cout << " | ";
            }
            cout << endl;
            if (i < 2) cout << "  ---------\n";
        }
        cout << endl;
    }

    Move<char>* get_move(Player<char>* player) override {
        MisereMinimaxPlayer<char>* smartPlayer = dynamic_cast<MisereMinimaxPlayer<char>*>(player);

        if (smartPlayer != nullptr) {
            cout << "\n" << player->get_name() << " (AI) is thinking..." << endl;
            Move<char>* aiMove = smartPlayer->get_best_move(player->get_board_ptr());
            cout << "AI plays at position (" << aiMove->get_x() << ", " << aiMove->get_y() << ")" << endl;
            return aiMove;
        }

        int x, y;
        cout << player->get_name() << " (" << player->get_symbol() << "), enter your move:" << endl;
        cout << "Row (0-2): ";
        cin >> x;
        cout << "Column (0-2): ";
        cin >> y;

        return new Move<char>(x, y, player->get_symbol());
    }

    void display_winner(Player<char>* winner) {
        cout << "\n==================================" << endl;
        cout << "         GAME OVER!" << endl;
        cout << "==================================" << endl;
        if (winner != nullptr) {
            cout << "*** " << winner->get_name() << " (" << winner->get_symbol() << ") LOSES! ***" << endl;
            cout << "(In Misere, making 3-in-a-row means you LOSE!)" << endl;
        }
        else {
            cout << "It's a DRAW!" << endl;
        }
        cout << "==================================" << endl;
    }

    Player<char>* create_player(string& name, char symbol, PlayerType type) override {
        if (type == PlayerType::COMPUTER) {
            return new MisereMinimaxPlayer<char>(name, symbol);
        }
        return new Player<char>(name, symbol, type);
    }
};

#endif