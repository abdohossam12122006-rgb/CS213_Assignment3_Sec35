#pragma once
#ifndef NUMERICAL_UI_H
#define NUMERICAL_UI_H

#include "BoardGame_Classes.h"
#include "XO_Classes.h" 
#include <iostream>

using namespace std;

class Numerical_UI : public XO_UI {
public:
    Numerical_UI() {}

    Move<char>* get_move(Player<char>* p) override {
        int x, y;
        int number;

        cout << "Player " << p->get_name() << ", enter row (0-2), col (0-2) and Number: ";

        while (true) {
            if (cin >> x >> y >> number) {
                return new Move<char>(x, y, number + '0');
            }
            else {
                cin.clear();
                cin.ignore(10000, '\n');
                cout << "Invalid input. Try again: ";
            }
        }
    }
};

#endif