#pragma once
#ifndef WORD_TicTacToe_UI_H
#define WORD_TicTacToe_UI_H

#include "BoardGame_Classes.h"
#include <iostream>

using namespace std;

class Word_TicTacToe_UI : public UI<char> {
public:
    Word_TicTacToe_UI() {}

    // ⁄—÷ «·»Ê—œ
    void display_board(Board<char>* b) override {
        // ⁄—÷ »”Ìÿ ··»Ê—œ
        int rows = b->get_rows();
        int cols = b->get_cols(); // √Ê get_columns Õ”»  ”„Ì… «·ﬂ·«” ⁄‰œﬂ
        // ·Ê „›Ì‘ get_cols «” Œœ„ 3 Ê 3

        cout << "\n-------------\n";
        for (int i = 0; i < 3; i++) {
            cout << "| ";
            for (int j = 0; j < 3; j++) {
                
            }
        }
    }

    Move<char>* get_move(Player<char>* p) override {
        int x, y;
        char c;

        cout << "Player " << p->get_name() << ", enter row (0-2), col (0-2), and Letter: ";
        // Â‰« »‰ÿ·» «·Õ—› “Ì«œ…
        while (true) {
            cin >> x >> y >> c;
            if (cin.fail()) {
                cin.clear(); cin.ignore(10000, '\n');
                cout << "Invalid input. Try again: ";
            }
            else {
                break;
            }
        }

        // »‰—Ã⁄ Õ—ﬂ… ÃœÌœ… ›ÌÂ« «·Õ—› «··Ì «·„” Œœ„ œŒ·Â° „‘ —„“ «··«⁄» «·√’·Ì
        return new Move<char>(x, y, c);
    }

    // ·«“„ ‰⁄„· implementation ·»«ﬁÌ «·‹ pure virtual functions ·Ê „ÊÃÊœ…
    // “Ì display_board_matrix .. «·Œ° »” „„ﬂ‰ ‰Ê—À „‰ XO_UI √”Â·
};
#endif