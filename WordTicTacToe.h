#ifndef WORDTICTACTOE_H
#define WORDTICTACTOE_H

#include "BoardGame_Classes.h"
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

class WordTicTacToe : public Board<char> {
private:
    vector<string> dictionary;

public:
    WordTicTacToe() : Board<char>(3, 3) {
        n_moves = 0;
        load_dictionary("dic.txt");

        for (int i = 0; i < rows; i++)
            for (int j = 0; j < columns; j++)
                board[i][j] = 0;
    }

    
    void load_dictionary(const string& filename) {
        ifstream file(filename);
        string word;
        while (file >> word) {
            if (word.size() == 3)
                dictionary.push_back(word);
        }
        file.close();
    }

    bool is_valid_word(const string& w) {
        string temp = w;
        transform(temp.begin(), temp.end(), temp.begin(), ::tolower);

        for (string d : dictionary) {
            transform(d.begin(), d.end(), d.begin(), ::tolower);
            if (temp == d) return true;
        }
        return false;
    }

    bool update_board(Move<char>* move) override {
        int r = move->get_x();
        int c = move->get_y();
        char letter = move->get_symbol();

        if (r < 0 || r >= 3 || c < 0 || c >= 3)
            return false;

        if (board[r][c] != 0)
            return false;

        board[r][c] = letter;
        n_moves++;
        return true;
    }

    bool check_word_line(string s) {
        return is_valid_word(s);
    }

    bool is_win(Player<char>* player) override {
       
        for (int i = 0; i < 3; i++) {
            string row = "";
            for (int j = 0; j < 3; j++)
                row += board[i][j];
            if (check_word_line(row)) return true;
        }

        for (int j = 0; j < 3; j++) {
            string col = "";
            for (int i = 0; i < 3; i++)
                col += board[i][j];
            if (check_word_line(col)) return true;
        }

        string diag1 = "";
        for (int i = 0; i < 3; i++)
            diag1 += board[i][i];
        if (check_word_line(diag1)) return true;

        string diag2 = "";
        for (int i = 0; i < 3; i++)
            diag2 += board[i][2 - i];
        if (check_word_line(diag2)) return true;

        return false;
    }

    bool is_draw(Player<char>* player) override {
        return (n_moves == 9 && !is_win(player));
    }

    bool is_lose(Player<char>* player) override {
        return false;
    }

    bool game_is_over(Player<char>* player) override {
        return is_win(player) || is_draw(player);
    }
};

#endif 
