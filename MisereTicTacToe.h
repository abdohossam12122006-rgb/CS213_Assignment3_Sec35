#ifndef MISERE_TIC_TAC_TOE_H
#define MISERE_TIC_TAC_TOE_H

#include "BoardGame_Classes.h"
#include <vector>
#include <iostream>

using namespace std;

/**
 * @brief Class representing the Misere Tic-Tac-Toe game board.
 * @details This class inherits from the generic Board class. The rules are inverted:
 * the player who forms a line of 3 symbols loses the game.
 */
class MisereBoard : public Board<char> {
public:
    /**
     * @brief Constructor to initialize the 3x3 Misere board.
     * @details Sets the dimensions to 3x3 and initializes the board with 0.
     */
    MisereBoard() : Board<char>(3, 3) {
        this->n_moves = 0;
        for (int i = 0; i < this->rows; i++) {
            for (int j = 0; j < this->columns; j++) {
                this->board[i][j] = 0;
            }
        }
    }
    void undo_move(int x, int y) {
        if (x >= 0 && x < this->rows && y >= 0 && y < this->columns) {
            this->board[x][y] = 0;
            this->n_moves--;
        }
    }

    /**
     * @brief Updates the board with a player's move.
     * @param move Pointer to the move object containing coordinates and symbol.
     * @return true if the move is valid and executed, false otherwise.
     */
    bool update_board(Move<char>* move) override {
        int x = move->get_x();
        int y = move->get_y();
        if (x < 0 || x >= this->rows || y < 0 || y >= this->columns || this->board[x][y] != 0) {
            return false;
        }
        this->board[x][y] = move->get_symbol();
        this->n_moves++;
        return true;
    }

    /**
     * @brief Checks if the current player has won.
     * @details In standard Misere logic, you win if the opponent loses.
     * However, this function returns false because the losing condition is what defines the game end.
     * @param p Pointer to the player object.
     * @return false (Win logic is handled by opponent losing).
     */
    bool is_win(Player<char>* player) override {
        return false;
    }

    /**
     * @brief Checks if the current player has lost.
     * @details The player loses if they form a line of 3 symbols.
     * @param player Pointer to the player object.
     * @return true if the player has 3 in a row.
     */
    bool is_lose(Player<char>* player) override {
        char symbol = player->get_symbol();

        for (int i = 0; i < this->rows; i++) {
            if (this->board[i][0] == symbol &&
                this->board[i][1] == symbol &&
                this->board[i][2] == symbol) {
                return true;
            }
        }

        for (int j = 0; j < this->columns; j++) {
            if (this->board[0][j] == symbol &&
                this->board[1][j] == symbol &&
                this->board[2][j] == symbol) {
                return true;
            }
        }

        if (this->board[0][0] == symbol &&
            this->board[1][1] == symbol &&
            this->board[2][2] == symbol) {
            return true;
        }

        if (this->board[0][2] == symbol &&
            this->board[1][1] == symbol &&
            this->board[2][0] == symbol) {
            return true;
        }

        return false;
    }

    /**
     * @brief Checks for a draw condition.
     * @details A draw occurs if the board is full and no one has lost yet.
     * @param p Pointer to the player object.
     * @return true if the game is a draw.
     */
    bool is_draw(Player<char>* player) override {
        return (this->n_moves == 9 && !is_lose(player));
    }

    /**
     * @brief Checks if the game is over.
     * @param p Pointer to the player object.
     * @return true if someone lost or it is a draw.
     */
    bool game_is_over(Player<char>* player) override {
        return is_lose(player) || is_draw(player);
    }
};

#endif
