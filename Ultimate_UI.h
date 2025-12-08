#ifndef ULTIMATE_UI_H
#define ULTIMATE_UI_H

#include "Fancy_UI.h"
#include "UltimateSmartPlayer.h" 
#include <iostream>
#include <vector>

using namespace std;

class Ultimate_UI : public Fancy_UI {
public:
    Ultimate_UI() {}

    void display_board_matrix(const vector<vector<char>>& board) override {
        Fancy_UI::display_board_matrix(board);
    }

    Move<char>* get_move(Player<char>* p) override {
        int x, y;
        if (auto aiPlayer = dynamic_cast<UltimateSmartPlayer<char>*>(p)) {
            // ÇáÜ AI åíÍÓÈ ÇáÜ x æ y
            aiPlayer->get_move(x, y);
            return new Move<char>(x, y, p->get_symbol());
        }

        while (true) {
            cout << "\nPlayer " << p->get_name() << ", enter row (0-8) and col (0-8): ";

            if (cin >> x >> y) {
                if (x >= 0 && x <= 8 && y >= 0 && y <= 8) {
                    return new Move<char>(x, y, p->get_symbol());
                }
                else {
                    cout << "Invalid coordinates! Please enter numbers between 0 and 8.\n";
                }
            }
            else {
                cin.clear();
                cin.ignore(10000, '\n');
                cout << "Invalid input. Try again.\n";
            }
        }
    }
};

#endif