#ifndef SUS_UI_H
#define SUS_UI_H

#include "BoardGame_Classes.h"
#include "XO_Classes.h"
#include <iostream>
#include <limits>

using namespace std;

class SUS_UI : public XO_UI {
public:
    SUS_UI() : XO_UI() {}

    Move<char>* get_move(Player<char>* player) override {
        int x, y;
        char c;
        cout << "\n" << player->get_name() << "'s Turn. Enter coordinate (x y) and char (S or U): ";
        while (true) {
            if (cin >> x >> y >> c) {
                c = toupper(c);
                if (c == 'S' || c == 'U') {
                    return new Move<char>(x, y, c);
                }
            }
            cout << "Invalid input! Try again (0-2 and S/U): ";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
    }
};

#endif