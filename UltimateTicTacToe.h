#pragma once
#ifndef ULTIMATE_TICTACTOE_H
#define ULTIMATE_TICTACTOE_H

#include "BoardGame_Classes.h"
#include <iostream>
#include <vector>

using namespace std;

/**
 * @brief Class representing the Ultimate Tic-Tac-Toe Board (9x9).
 * @details This game consists of a large 9x9 grid divided into nine 3x3 mini-boards.
 * Winning a mini-board marks the corresponding cell on the 3x3 meta-board.
 * The goal is to win 3 cells in a row on the meta-board.
 */
class UltimateBoard : public Board<char> {
private:
    /**
     * @brief A 3x3 array tracking the winner of each of the 9 mini-boards.
     * @details 0 means the mini-board is not won yet. 'X' or 'O' marks the winner.
     */
    char meta_board[3][3];

public:
    /**
     * @brief Constructor for Ultimate Tic-Tac-Toe.
     * @details Initializes the 9x9 main board and the 3x3 meta-board to 0 (empty).
     */
    UltimateBoard() : Board<char>(9, 9) {
        this->n_moves = 0;

        // Initialize main 9x9 board
        for (int i = 0; i < 9; i++) {
            for (int j = 0; j < 9; j++) {
                this->board[i][j] = 0;
            }
        }

        // Initialize meta 3x3 board
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                meta_board[i][j] = 0;
            }
        }
    }

    /**
     * @brief Updates the board with a valid move.
     * @details Checks bounds, ensures the specific cell is empty, and checks if the
     * corresponding mini-board is already won (locked). If valid, it places the symbol
     * and checks if this move won the mini-board.
     * @param move Pointer to the move to be executed (contains x, y, and symbol).
     * @return true if the move is valid and executed, false otherwise.
     */
    bool update_board(Move<char>* move) override {
        int x = move->get_x();
        int y = move->get_y();
        char symbol = move->get_symbol();

        // Check global bounds and if cell is empty
        if (x < 0 || x >= 9 || y < 0 || y >= 9 || this->board[x][y] != 0) {
            return false;
        }

        // Determine which mini-board this move belongs to
        int meta_r = x / 3;
        int meta_c = y / 3;

        // Check if this mini-board is already won (locked)
        if (meta_board[meta_r][meta_c] != 0) {
            return false;
        }

        // Execute move
        this->board[x][y] = symbol;
        this->n_moves++;

        // Check if this move wins the mini-board
        if (check_mini_board_win(meta_r, meta_c, symbol)) {
            meta_board[meta_r][meta_c] = symbol;
        }

        return true;
    }

    /**
     * @brief Helper function to check if a specific mini-board has been won.
     * @param mr Meta-row index (0-2) of the mini-board.
     * @param mc Meta-column index (0-2) of the mini-board.
     * @param symbol The symbol to check for (X or O).
     * @return true if the mini-board is won by the symbol.
     */
    bool check_mini_board_win(int mr, int mc, char symbol) {
        int start_r = mr * 3;
        int start_c = mc * 3;

        // Check rows of the mini-board
        for (int i = 0; i < 3; i++) {
            if (board[start_r + i][start_c] == symbol &&
                board[start_r + i][start_c + 1] == symbol &&
                board[start_r + i][start_c + 2] == symbol) return true;
        }
        // Check columns of the mini-board
        for (int j = 0; j < 3; j++) {
            if (board[start_r][start_c + j] == symbol &&
                board[start_r + 1][start_c + j] == symbol &&
                board[start_r + 2][start_c + j] == symbol) return true;
        }
        // Check diagonals of the mini-board
        if (board[start_r][start_c] == symbol &&
            board[start_r + 1][start_c + 1] == symbol &&
            board[start_r + 2][start_c + 2] == symbol) return true;

        if (board[start_r][start_c + 2] == symbol &&
            board[start_r + 1][start_c + 1] == symbol &&
            board[start_r + 2][start_c] == symbol) return true;

        return false;
    }

    /**
     * @brief Checks if the player has won the entire game.
     * @details Checks the 3x3 meta-board for any winning line (row, col, diagonal).
     * @param p Pointer to the player.
     * @return true if the player has won the Ultimate game.
     */
    bool is_win(Player<char>* p) override {
        char s = p->get_symbol();

        // Check meta-board rows
        for (int i = 0; i < 3; i++) {
            if (meta_board[i][0] == s && meta_board[i][1] == s && meta_board[i][2] == s) return true;
        }
        // Check meta-board columns
        for (int j = 0; j < 3; j++) {
            if (meta_board[0][j] == s && meta_board[1][j] == s && meta_board[2][j] == s) return true;
        }
        // Check meta-board diagonals
        if (meta_board[0][0] == s && meta_board[1][1] == s && meta_board[2][2] == s) return true;
        if (meta_board[0][2] == s && meta_board[1][1] == s && meta_board[2][0] == s) return true;

        return false;
    }

    /**
     * @brief Checks if the game is lost.
     * @details In this implementation, the game ends on a win or draw, not explicit loss logic.
     * @return false always.
     */
    bool is_lose(Player<char>* p) override { return false; }

    /**
     * @brief Checks for a draw.
     * @details Returns true if the board is theoretically full (81 moves) and no one has won.
     * @param p Pointer to the player.
     * @return true if it is a draw.
     */
    bool is_draw(Player<char>* p) override {
        return (this->n_moves == 81 && !is_win(p));
    }

    /**
     * @brief Checks if the game is over.
     * @param p Pointer to the player.
     * @return true if there is a winner or a draw.
     */
    bool game_is_over(Player<char>* p) override {
        return is_win(p) || is_draw(p);
    }
};

#endif
