#ifndef MEMORY_UI_H
#define MEMORY_UI_H

#include "Fancy_UI.h"
#include "MemoryMinimaxPlayer.h" 
#include <iostream>
#include <vector>

using namespace std;

class Memory_UI : public Fancy_UI {
public:
    Memory_UI() {}
    void display_board_matrix(const vector<vector<char>>& board) override {
        clear_screen();
        cout << BOLD << GREEN << "\n\t   --- MEMORY GAME (Bonus) --- \n" << RESET;
        cout << "\t   (Marks are hidden!)\n\n";

        cout << "\t      " << YELLOW << "0   1   2" << RESET << "\n";
        cout << "\t    " << CYAN << "-------------" << RESET << "\n";

        for (int i = 0; i < 3; i++) {
            cout << YELLOW << "\t " << i << " " << CYAN << "| " << RESET;
            for (int j = 0; j < 3; j++) {
                cout << BOLD << " " << RESET;
                cout << " " << CYAN << "|" << RESET;
            }
            cout << "\n\t    " << CYAN << "-------------" << RESET << "\n";
        }
        cout << "\n";
    }

    Move<char>* get_move(Player<char>* p) override {
        int x, y;

        if (auto aiPlayer = dynamic_cast<MemoryMinimaxPlayer<char>*>(p)) {
            cout << "\nAI is thinking...\n";
            aiPlayer->get_move(x, y); 
            return new Move<char>(x, y, p->get_symbol());
        }

        while (true) {
            cout << "\nPlayer " << p->get_name() << ", enter row (0-2) and col (0-2): ";
            if (cin >> x >> y) {
                if (x >= 0 && x <= 2 && y >= 0 && y <= 2) {
                    return new Move<char>(x, y, p->get_symbol());
                }
                cout << "Invalid coordinates!\n";
            }
            else {
                cin.clear(); cin.ignore(10000, '\n');
                cout << "Invalid input.\n";
            }
        }
    }
};

#endif