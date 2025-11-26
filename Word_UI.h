#ifndef WORD_UI_H
#define WORD_UI_H

#include "BoardGame_Classes.h"
#include "XO_Classes.h" 
#include <iostream>
#include <limits>
#include <cctype>

using namespace std;
class Word_UI : public XO_UI {
public:
    Word_UI() {}
    Move<char>* get_move(Player<char>* p) override {
        int x, y;
        char c;

        while (true) {
            cout << "Player " << p->get_name() << ", enter row (0-2), col (0-2) and Letter: ";
            if (cin >> x >> y >> c) {
                if (isalpha(c)) {
                    return new Move<char>(x, y, toupper(c));
                }
                else {
                    cout << "Invalid char! Please enter a letter (A-Z).\n";
                }
            }
            else {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Invalid input. Please enter numbers for row/col and a character.\n";
            }
        }
    }
};

#endif