#ifndef WORDTICTACTOE_H
#define WORDTICTACTOE_H

#include "BoardGame_Classes.h"
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <cctype>
#include <iostream>

using namespace std;

class WordTicTacToe : public Board<char> {
private:
    vector<string> dictionary;
    string winningWord = "";
    bool useDictionary = true;  

    static string to_lower(const string& s) {
        string out = s;
        for (char& c : out) c = char(tolower((unsigned char)c));
        return out;
    }

public:
    WordTicTacToe(const string& dict_filename = "dic.txt")
        : Board<char>(3, 3)
    {
        n_moves = 0;

        for (int i = 0; i < rows; ++i)
            for (int j = 0; j < columns; ++j)
                board[i][j] = 0;

        ifstream fin(dict_filename);
        if (fin) {
            string w;
            while (fin >> w) {
                if (w.size() == 3) {
                    dictionary.push_back(to_lower(w));
                }
            }
            fin.close();

            sort(dictionary.begin(), dictionary.end());
            dictionary.erase(unique(dictionary.begin(), dictionary.end()), dictionary.end());
        }
        else {
            cerr << "Warning: dictionary file \"" << dict_filename << "\" not found.\n";
            useDictionary = false;  // if no dictionary, accept any 3-letter word
        }
    }

    bool is_valid_word(const string& w) const {
        if (w.size() != 3) return false;
        if (!useDictionary) return true;  // accept any word
        string lw = to_lower(w);
        return binary_search(dictionary.begin(), dictionary.end(), lw);
    }

    bool update_board(Move<char>* move) override {
        int r = move->get_x();
        int c = move->get_y();
        char ch = move->get_symbol();

        if (r < 0 || r >= rows || c < 0 || c >= columns) return false;
        if (board[r][c] != 0) return false;

        ch = toupper(ch);
        board[r][c] = ch;

        ++n_moves;
        return true;
    }

    bool is_win(Player<char>* /*player*/) override {
        winningWord = "";

        // rows
        for (int i = 0; i < 3; ++i) {
            if (board[i][0] && board[i][1] && board[i][2]) {
                string s = { board[i][0], board[i][1], board[i][2] };
                if (is_valid_word(s)) {
                    winningWord = s;
                    return true;
                }
            }
        }

        // columns
        for (int j = 0; j < 3; ++j) {
            if (board[0][j] && board[1][j] && board[2][j]) {
                string s = { board[0][j], board[1][j], board[2][j] };
                if (is_valid_word(s)) {
                    winningWord = s;
                    return true;
                }
            }
        }

        // main diagonal
        if (board[0][0] && board[1][1] && board[2][2]) {
            string s = { board[0][0], board[1][1], board[2][2] };
            if (is_valid_word(s)) {
                winningWord = s;
                return true;
            }
        }

        // anti diagonal
        if (board[0][2] && board[1][1] && board[2][0]) {
            string s = { board[0][2], board[1][1], board[2][0] };
            if (is_valid_word(s)) {
                winningWord = s;
                return true;
            }
        }

        return false;
    }

    string getWinningWord() const {
        return winningWord;
    }

    bool is_draw(Player<char>* /*player*/) override {
        return (n_moves == 9 && !is_win(nullptr));
    }

    bool is_lose(Player<char>* /*player*/) override { return false; }

    bool game_is_over(Player<char>* player) override {
        return is_win(player) || is_draw(player);
    }

    char get_cell(int r, int c) const {
        if (r < 0 || r >= rows || c < 0 || c >= columns) return 0;
        return board[r][c];
    }
};

// ================= UI =================

class WordUI : public UI<char> {
public:
    WordUI() : UI<char>("Word Tic-Tac-Toe", 3) {}

    Player<char>* create_player(string& name, char symbol, PlayerType type) override {
        return new Player<char>(name, symbol, type);
    }

    Move<char>* get_move(Player<char>* player) override {
        char ch;
        int r, c;

        cout << player->get_name() << " enter letter and coordinates\n";

        cout << "Letter (A-Z): ";
        cin >> ch;
        ch = toupper(ch);

        cout << "Row (0-2): ";
        cin >> r;

        cout << "Col (0-2): ";
        cin >> c;

        return new Move<char>(r, c, ch);
    }
};

#endif // WORDTICTACTOE_H

