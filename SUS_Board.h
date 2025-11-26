#ifndef SUS_BOARD_H
#define SUS_BOARD_H

#include "BoardGame_Classes.h"
#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;

class SUS_Board : public Board<char> {
private:
    int player_scores[2]; 

public:
    SUS_Board() : Board<char>(3, 3) {
        this->n_moves = 0;
        player_scores[0] = 0;
        player_scores[1] = 0;
        for (int i = 0; i < 3; i++)
            for (int j = 0; j < 3; j++) this->board[i][j] = 0;
    }

    int count_new_sus(int r, int c) {
        char current = this->board[r][c];
        int count = 0;
        int dr[] = { 0, 0, 1, -1, 1, -1, 1, -1 };
        int dc[] = { 1, -1, 0, 0, 1, -1, -1, 1 };

        if (current == 'U') {
            for (int i = 0; i < 8; i += 2) {
                int r1 = r + dr[i], c1 = c + dc[i];
                int r2 = r + dr[i + 1], c2 = c + dc[i + 1];
                if (is_valid(r1, c1) && is_valid(r2, c2)) {
                    if (this->board[r1][c1] == 'S' && this->board[r2][c2] == 'S') count++;
                }
            }
        }
        else if (current == 'S') {
            for (int i = 0; i < 8; i++) {
                int r1 = r + dr[i], c1 = c + dc[i];
                int r2 = r + dr[i] * 2, c2 = c + dc[i] * 2;
                if (is_valid(r1, c1) && is_valid(r2, c2)) {
                    if (this->board[r1][c1] == 'U' && this->board[r2][c2] == 'S') count++;
                }
            }
        }
        return count;
    }

    bool is_valid(int r, int c) {
        return r >= 0 && r < 3 && c >= 0 && c < 3;
    }

    bool update_board(Move<char>* move) override {
        int x = move->get_x();
        int y = move->get_y();
        if (x < 0 || x >= 3 || y < 0 || y >= 3 || this->board[x][y] != 0) return false;

        this->board[x][y] = move->get_symbol();

        int points = count_new_sus(x, y);
        int currentPlayerIndex = this->n_moves % 2;
        player_scores[currentPlayerIndex] += points;

        this->n_moves++;
        return true;
    }

    int get_score(int playerIndex) {
        if (playerIndex >= 0 && playerIndex < 2)
            return player_scores[playerIndex];
        return 0;
    }

    bool is_win(Player<char>* player) override { return false; }
    bool is_lose(Player<char>* player) override { return false; }
    bool is_draw(Player<char>* player) override { return (this->n_moves == 9); }
    bool game_is_over(Player<char>* player) override { return (this->n_moves == 9); }
};

#endif