
#ifndef OBSTACLESBOARD_H
#define OBSTACLESBOARD_H

#include "BoardGame_Classes.h"
#include <algorithm>
#include <random>
#include <chrono>
/**
 * @class ObstaclesBoard
 * @brief A 6x6 board that adds random obstacles every two moves.
 */

class ObstaclesBoard : public Board<char> {
    static const int SIZE = 6;
    static const int TO_WIN = 4;
    int roundMoves;   
    std::mt19937 rng;

public:
    ObstaclesBoard() : Board<char>(SIZE, SIZE), roundMoves(0) {
        rng.seed((unsigned)std::chrono::high_resolution_clock::now().time_since_epoch().count());
        for (int i = 0; i < SIZE; i++)
            for (int j = 0; j < SIZE; j++)
                board[i][j] = '.';
    }

    bool update_board(Move<char>* move) override {
        int r = move->get_x();
        int c = move->get_y();
        char sym = move->get_symbol();

        if (r < 0 || r >= SIZE || c < 0 || c >= SIZE)
            return false;

        if (board[r][c] != '.')     // occupied or obstacle
            return false;

        board[r][c] = sym;
        n_moves++;
        roundMoves++;

        // ??? ?? ???? (X ? O)
        if (roundMoves == 2) {
            roundMoves = 0;
            add_obstacles(2);
        }

        return true;
    }

    bool is_win(Player<char>* p) override {
        char sym = p->get_symbol();

        // check every cell
        for (int r = 0; r < SIZE; r++) {
            for (int c = 0; c < SIZE; c++) {
                if (board[r][c] == sym) {
                    if (check_dir(r, c, 1, 0, sym)) return true; // horizontal
                    if (check_dir(r, c, 0, 1, sym)) return true; // vertical
                    if (check_dir(r, c, 1, 1, sym)) return true; // diag down-right
                    if (check_dir(r, c, 1, -1, sym)) return true; // diag down-left
                }
            }
        }
        return false;
    }

    bool is_lose(Player<char>* p) override {
        return false; // ????? lose ?? ?????? ??
    }

    bool is_draw(Player<char>* p) override {
        return (n_moves == SIZE * SIZE); // full board
    }

    bool game_is_over(Player<char>* p) override {
        return is_win(p) || is_draw(p);
    }

private:
    bool check_dir(int r, int c, int dr, int dc, char sym) {
        int count = 0;
        for (int k = 0; k < TO_WIN; k++) {
            int rr = r + dr * k;
            int cc = c + dc * k;
            if (rr < 0 || rr >= SIZE || cc < 0 || cc >= SIZE)
                return false;
            if (board[rr][cc] != sym)
                return false;
        }
        return true;
    }

    void add_obstacles(int count) {
        vector<pair<int, int>> empties;

        for (int r = 0; r < SIZE; r++)
            for (int c = 0; c < SIZE; c++)
                if (board[r][c] == '.')
                    empties.push_back({ r, c });

        if (empties.empty()) return;

        shuffle(empties.begin(), empties.end(), rng);

        for (int i = 0; i < count && i < (int)empties.size(); i++) {
            auto& cell = empties[i];
            board[cell.first][cell.second] = '#';
        }
    }
};

#endif
