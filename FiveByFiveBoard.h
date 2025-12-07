#ifndef FIVEBYFIVEBOARD_H
#define FIVEBYFIVEBOARD_H

#include "BoardGame_Classes.h"
#include <vector>
using namespace std;

class FiveByFiveBoard : public Board<char> {
public:
    FiveByFiveBoard() : Board<char>(5, 5) {
        this->n_moves = 0;
        for (int i = 0; i < rows; i++)
            for (int j = 0; j < columns; j++)
                board[i][j] = 0;
    }

    bool update_board(Move<char>* move) override {
        int r = move->get_x();
        int c = move->get_y();
        char sym = move->get_symbol();

        if (r < 0 || r >= 5 || c < 0 || c >= 5) return false;
        if (board[r][c] != 0) return false;

        board[r][c] = sym;
        n_moves++;
        return true;
    }


    int count_threes(char symbol) {
        int total = 0;

        // rows
        for (int i = 0; i < 5; i++)
            for (int j = 0; j < 3; j++)
                if (board[i][j] == symbol &&
                    board[i][j + 1] == symbol &&
                    board[i][j + 2] == symbol)
                    total++;

        // columns
        for (int j = 0; j < 5; j++)
            for (int i = 0; i < 3; i++)
                if (board[i][j] == symbol &&
                    board[i + 1][j] == symbol &&
                    board[i + 2][j] == symbol)
                    total++;

        // Diagonals (main)
        for (int i = 0; i < 3; i++)
            for (int j = 0; j < 3; j++)
                if (board[i][j] == symbol &&
                    board[i + 1][j + 1] == symbol &&
                    board[i + 2][j + 2] == symbol)
                    total++;

        // Diagonals (anti)
        for (int i = 0; i < 3; i++)
            for (int j = 2; j < 5; j++)
                if (board[i][j] == symbol &&
                    board[i + 1][j - 1] == symbol &&
                    board[i + 2][j - 2] == symbol)
                    total++;

        return total;
    }

    bool is_win(Player<char>* player) override {
        char sym = player->get_symbol();
        char opp = (sym == 'X' ? 'O' : 'X');

        int myScore = count_threes(sym);
        int oppScore = count_threes(opp);


        if (n_moves == 24)
            return myScore > oppScore;

        return false;
    }

    bool is_draw(Player<char>* player) override {
        if (n_moves < 24) return false;

        char sym = player->get_symbol();
        char opp = (sym == 'X' ? 'O' : 'X');

        return count_threes(sym) == count_threes(opp);
    }

    bool is_lose(Player<char>* player) override {
        return false;
    }

    bool game_is_over(Player<char>* player) override {
        return n_moves == 24;
    }
};
// ==========================================
// ============  AI PLAYER  =================
// ==========================================

class AIPlayer : public Player<char> {
public:
    AIPlayer(string name, char symbol)
        : Player<char>(name, symbol, PlayerType::COMPUTER)
    {
    }

    Move<char>* get_move(Board<char>* board) /*override*/ {
        int r, c;

        while (true) {
            r = rand() % board->get_rows();
            c = rand() % board->get_columns();

            if (board->get_cell(r, c) == 0)
                break;
        }

        return new Move<char>(r, c, this->symbol);
    }
};


#endif

