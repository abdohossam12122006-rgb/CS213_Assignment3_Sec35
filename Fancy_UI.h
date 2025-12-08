#ifndef FANCY_UI_H
#define FANCY_UI_H

#include "XO_Classes.h"
#include <iostream>
#include <vector>
#include <string>
#include <cstdlib>

using namespace std;
const string RESET = "\033[0m";
const string RED = "\033[31m";
const string GREEN = "\033[32m";
const string YELLOW = "\033[33m";
const string BLUE = "\033[34m";
const string MAGENTA = "\033[35m";
const string CYAN = "\033[36m";
const string BOLD = "\033[1m";

class Fancy_UI : public XO_UI {
public:
    Fancy_UI() {}

    void clear_screen() {
#ifdef _WIN32
        system("cls");
#else
        system("clear");
#endif
    }
    virtual void display_board_matrix(const vector<vector<char>>& board) {
        clear_screen();

        cout << BOLD << CYAN << "\n\t   --- GAME BOARD --- \n\n" << RESET;

        int rows = board.size();
        int cols = (rows > 0) ? board[0].size() : 0;
        cout << "\t     ";
        for (int j = 0; j < cols; ++j) {
            cout << YELLOW << j << "   " << RESET;
        }
        cout << "\n";

        for (int i = 0; i < rows; i++) {
            cout << "\t   " << CYAN << "-------------------------" << RESET << "\n";
            cout << YELLOW << "\t " << i << " " << RESET;

            for (int j = 0; j < cols; j++) {
                cout << CYAN << "| " << RESET;

                char cell = board[i][j];

                if (cell == 'X') cout << RED << BOLD << "X" << RESET;
                else if (cell == 'O') cout << BLUE << BOLD << "O" << RESET;
                else if (cell == 'S') cout << MAGENTA << BOLD << "S" << RESET;
                else if (cell == 'U') cout << GREEN << BOLD << "U" << RESET;
                else if (cell == '#' || cell == '*') cout << RED << "X" << RESET;
                else if (cell == 0 || cell == ' ') cout << " ";
                else cout << BOLD << cell << RESET;

                cout << " ";
            }
            cout << CYAN << "|" << RESET << "\n";
        }
        cout << "\t   " << CYAN << "-------------------------" << RESET << "\n\n";
    }

    void display_message(string msg) override {
        if (msg.find("Win") != string::npos || msg.find("win") != string::npos) {
            cout << "\n\t" << GREEN << BOLD << "  " << msg << "  " << RESET << "\n";
        }
        else if (msg.find("Draw") != string::npos) {
            cout << "\n\t" << YELLOW << BOLD << "  " << msg << "  " << RESET << "\n";
        }
        else {
            cout << "\n\t" << msg << "\n";
        }
    }
};

#endif