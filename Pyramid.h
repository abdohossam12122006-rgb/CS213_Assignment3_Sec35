#ifndef PYRAMID_H
#define PYRAMID_H

#include "BoardGame_Classes.h"
#include <iostream>
#include <iomanip>
#include <algorithm>
using namespace std;

// === PYRAMID BOARD===
class Pyramid_Board : public Board<char> {
public:
    Pyramid_Board() : Board<char>(3, 5) {
        for (int i = 0; i < 3; i++)
            for (int j = 0; j < 5; j++)
                board[i][j] = 0;

        n_moves = 0;
    }

    bool update_board(Move<char>* move) override {
        int r = move->get_x();
        int c = move->get_y();
        char symbol = move->get_symbol();

        if (r < 0 || r >= 3 || c < 0 || c >= 5)
            return false;

        bool valid = (r == 0 && c == 2) || (r == 1 && (c >= 1 && c <= 3)) || (r == 2);
        if (!valid) return false;

        if (board[r][c] == 0) {
            board[r][c] = symbol;
            n_moves++;
            return true;
        }
        return false;
    }

    //===win function===
    bool is_win(Player<char>* p)override {
        char symbol = p->get_symbol();
        //===vertical ===
        if (this->board[0][2] == symbol &&
            this->board[1][2] == symbol &&
            this->board[2][2] == symbol) {
            return true;
        }
        //===Diagonal down right ===
        if (this->board[0][2] == symbol &&
            this->board[1][1] == symbol &&
            this->board[2][0] == symbol) {
            return true;
        }
        //===Diagonal down left ===
        if (this->board[0][2] == symbol &&
            this->board[1][3] == symbol &&
            this->board[2][4] == symbol) {
            return true;
        }
        //===HORIZONTAL 1===
        if (this->board[1][1] == symbol &&
            this->board[1][2] == symbol &&
            this->board[1][3] == symbol) {
            return true;
        }
        //===HORIZONTAL2 ===
        for (int c = 0; c <= 2; ++c) {
            if (this->board[2][c] == symbol &&
                this->board[2][c + 1] == symbol &&
                this->board[2][c + 2] == symbol) {
                return true;
            }
        }
        return false;
    }

    bool is_draw(Player<char>* p) override {
        return (n_moves == 9 && !is_win(p));
    }

    bool game_is_over(Player<char>* p) override {
        return is_win(p) || is_draw(p);
    }

    bool is_lose(Player<char>* p) override {
        return false;
    }

    // ---------- Public getters and setters ----------
    char get_cell(int r, int c) const {
        return board[r][c];
    }

    int get_n_moves() const {
        return n_moves;
    }

    bool set_cell(int r, int c, char s) {
        bool valid = (r == 0 && c == 2) || (r == 1 && (c >= 1 && c <= 3)) || (r == 2);
        if (!valid || board[r][c] != 0) return false;
        board[r][c] = s;
        n_moves++;
        return true;
    }

    void reset_cell(int r, int c) {
        board[r][c] = 0;
        n_moves--;
    }
};

//=== PYRAMID UI + AI
class Pyramid_UI : public UI<char> {
public:
    Pyramid_UI() : UI<char>("Welcome to Pyramid Tic-Tac-Toe (Game 8)!", 3) {}

    Player<char>* create_player(string& name, char symbol, PlayerType type) override {
        return new Player<char>(name, symbol, type);
    }

    // ---------- Check Win (for AI) ----------
    bool check_win(Pyramid_Board* b, char s) {
        if (b->get_cell(0, 2) == s && b->get_cell(1, 2) == s && b->get_cell(2, 2) == s) return true;
        if (b->get_cell(0, 2) == s && b->get_cell(1, 1) == s && b->get_cell(2, 0) == s) return true;
        if (b->get_cell(0, 2) == s && b->get_cell(1, 3) == s && b->get_cell(2, 4) == s) return true;
        if (b->get_cell(1, 1) == s && b->get_cell(1, 2) == s && b->get_cell(1, 3) == s) return true;
        for (int c = 0; c <= 2; c++)
            if (b->get_cell(2, c) == s && b->get_cell(2, c + 1) == s && b->get_cell(2, c + 2) == s)
                return true;
        return false;
    }

    // ---------- MiniMax Algorithm ----------
    int minimax(Pyramid_Board* b, bool maximizing, char ai, char human) {
        if (check_win(b, ai)) return +10;
        if (check_win(b, human)) return -10;
        if (b->get_n_moves() == 9) return 0;

        int best = maximizing ? -1000 : 1000;

        for (int r = 0; r < 3; r++) {
            for (int c = 0; c < 5; c++) {
                bool valid = (r == 0 && c == 2) || (r == 1 && (c >= 1 && c <= 3)) || (r == 2);
                if (!valid) continue;

                if (b->get_cell(r, c) == 0) {
                    b->set_cell(r, c, maximizing ? ai : human);
                    int score = minimax(b, !maximizing, ai, human);
                    b->reset_cell(r, c);

                    if (maximizing) best = max(best, score);
                    else best = min(best, score);
                }
            }
        }
        return best;
    }

    // ---------- Best Move for AI ----------
    Move<char>* get_best_move(Pyramid_Board* b, char ai, char human) {
        int bestScore = -1000;
        int bestR = -1, bestC = -1;

        for (int r = 0; r < 3; r++) {
            for (int c = 0; c < 5; c++) {
                bool valid = (r == 0 && c == 2) || (r == 1 && (c >= 1 && c <= 3)) || (r == 2);
                if (!valid) continue;

                if (b->get_cell(r, c) == 0) {
                    b->set_cell(r, c, ai);
                    int score = minimax(b, false, ai, human);
                    b->reset_cell(r, c);

                    if (score > bestScore) {
                        bestScore = score;
                        bestR = r;
                        bestC = c;
                    }
                }
            }
        }
        return new Move<char>(bestR, bestC, ai);
    }

   
    Move<char>* get_move(Player<char>* p) override {
        if (p->get_type() == PlayerType::HUMAN) {
            int x, y;
            cout << "\n" << p->get_name() << " (" << p->get_symbol()
                << "), enter your move (row 0-2, col 0-4): ";
            cin >> x >> y;
            return new Move<char>(x, y, p->get_symbol());
        }

        // AI move
        Pyramid_Board* b = dynamic_cast<Pyramid_Board*>(p->get_board_ptr());
        char ai = p->get_symbol();
        char human = (ai == 'X' ? 'O' : 'X');

        return get_best_move(b, ai, human);
    }
};

#endif
