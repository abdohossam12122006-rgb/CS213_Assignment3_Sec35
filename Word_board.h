#ifndef WORD_BOARD_H
#define WORD_BOARD_H

#include "BoardGame_Classes.h"
#include <iostream>
#include <vector>
#include <fstream>
#include <set>
#include <algorithm>

using namespace std;

class WordBoard : public Board<char> {
private:
    set<string> dictionary;

public:
    WordBoard() : Board<char>(3, 3) {
        this->n_moves = 0;
        load_dictionary("dic.txt");

        for (int i = 0; i < 3; i++)
            for (int j = 0; j < 3; j++)
                this->board[i][j] = 0;
    }

    void load_dictionary(string filename) {
        ifstream file(filename);
        string word;
        if (file.is_open()) {
            while (file >> word) {
                transform(word.begin(), word.end(), word.begin(), ::toupper);
                if (word.length() == 3) {
                    dictionary.insert(word);
                }
            }
            file.close();
        }
        else {
            cout << "Warning: dic.txt not found! Game logic might fail." << endl;
        }
    }

    bool update_board(Move<char>* move) override {
        int x = move->get_x();
        int y = move->get_y();

        if (x < 0 || x >= 3 || y < 0 || y >= 3 || this->board[x][y] != 0) {
            return false;
        }

        this->board[x][y] = toupper(move->get_symbol());
        this->n_moves++;
        return true;
    }

    bool is_word_valid(string s) {
        return dictionary.count(s);
    }

    bool is_win(Player<char>* p) override {
        for (int i = 0; i < 3; i++) {
            string s = "";
            s += board[i][0]; s += board[i][1]; s += board[i][2];
            if (s.find((char)0) == string::npos && is_word_valid(s)) return true;
        }

        for (int j = 0; j < 3; j++) {
            string s = "";
            s += board[0][j]; s += board[1][j]; s += board[2][j];
            if (s.find((char)0) == string::npos && is_word_valid(s)) return true;
        }

        string d1 = "";
        d1 += board[0][0]; d1 += board[1][1]; d1 += board[2][2];
        if (d1.find((char)0) == string::npos && is_word_valid(d1)) return true;

        string d2 = "";
        d2 += board[0][2]; d2 += board[1][1]; d2 += board[2][0];
        if (d2.find((char)0) == string::npos && is_word_valid(d2)) return true;

        return false;
    }

    bool is_draw(Player<char>* p) override {
        return (this->n_moves == 9 && !is_win(p));
    }

    bool game_is_over(Player<char>* p) override {
        return is_win(p) || is_draw(p);
    }

    bool is_lose(Player<char>* p) override {
        return !is_win(p) && game_is_over(p);
    }
};

#endif
