#ifndef INFINITY_H
#define INFINITY_H

#include <iostream>
#include <iomanip>
#include <algorithm>
#include <vector>
#include <deque>
#include <limits>
#include "BoardGame_Classes.h"
using namespace std;

/**
 * @class Infinity_Board
 * @brief A variant of Tic-Tac-Toe where only the last 6 moves remain on the board.
 * 
 * Rules:
 * - 3x3 board
 * - Only the last 6 moves are kept; older moves disappear.
 * - Win: 3 in a row horizontally, vertically, or diagonally.
 * - Draw: if 100 moves reached without a winner.
 */
class Infinity_Board : public Board<char> {
    /**
     * @struct MoveDetail
     * @brief Stores a move's coordinates and symbol for history tracking
     */
    struct MoveDetail {
        int x, y;
        char symbol;
    };

    std::deque<MoveDetail> history; ///< Tracks the last 6 moves

public:
    /**
     * @brief Constructor: initialize 3x3 board with empty cells.
     */
    Infinity_Board() : Board<char>(3, 3) {
        for (int i = 0; i < 3; ++i)
            for (int j = 0; j < 3; ++j)
                this->board[i][j] = 0;
        this->n_moves = 0;
    }

    /**
     * @brief Update the board with a new move.
     * 
     * Keeps only the last 6 moves on the board.
     * 
     * @param move Pointer to Move object
     * @return true if move was applied successfully
     * @return false if move is invalid
     */
    bool update_board(Move<char>* move) override {
        int x = move->get_x();
        int y = move->get_y();
        char symbol = move->get_symbol();

        if (x < 0 || x >= this->rows || y < 0 || y >= this->columns || this->board[x][y] != 0) {
            return false;
        }

        this->board[x][y] = symbol;
        this->n_moves++;
        history.push_back({ x, y, symbol });

        if (history.size() > 6) {
            MoveDetail oldest = history.front();
            this->board[oldest.x][oldest.y] = 0;
            history.pop_front();
        }
        return true;
    }

    /**
     * @brief Check if a player has won.
     * 
     * @param p Pointer to player
     * @return true if player has 3 in a row
     */
    bool is_win(Player<char>* p) override {
        char s = p->get_symbol();
        for (int i = 0; i < 3; i++) {
            if (this->board[0][i] == s && this->board[1][i] == s && this->board[2][i] == s) return true;
            if (this->board[i][0] == s && this->board[i][1] == s && this->board[i][2] == s) return true;
        }
        if (this->board[0][0] == s && this->board[1][1] == s && this->board[2][2] == s) return true;
        if (this->board[0][2] == s && this->board[1][1] == s && this->board[2][0] == s) return true;
        return false;
    }

    /**
     * @brief Check if a player has lost.
     * 
     * Always false in Infinity Tic-Tac-Toe.
     */
    bool is_lose(Player<char>* p) override {
        return false;
    }

    /**
     * @brief Check if the game is a draw.
     * 
     * Draw occurs if 100 moves were made without a winner.
     */
    bool is_draw(Player<char>* player) override {
        return (this->n_moves >= 100);
    }

    /**
     * @brief Check if the game is over.
     * 
     * Game is over if player won, draw occurred, or lose condition (never) occurs.
     */
    bool game_is_over(Player<char>* player) override {
        return is_win(player) || is_draw(player) || is_lose(player);
    }
};

/**
 * @class InfinityUI
 * @brief Handles user interface for Infinity Tic-Tac-Toe.
 */
class InfinityUI : public UI<char> {
public:
    /**
     * @brief Constructor: displays welcome message and initializes UI
     */
    InfinityUI() : UI<char>("Welcome to Infinity Tic-Tac-Toe!", 3) {}

    /**
     * @brief Create a player (human or computer)
     */
    Player<char>* create_player(string& name, char symbol, PlayerType type) override {
        return new Player<char>(name, symbol, type);
    }

    /**
     * @brief Get the next move from the player.
     * 
     * For computer, generates random valid move.
     * For human, reads coordinates from input.
     * 
     * @param p Pointer to player
     * @return Move<char>* Pointer to move
     */
    Move<char>* get_move(Player<char>* p) override {
        int x, y;

        if (p->get_type() == PlayerType::COMPUTER) {
            cout << "\n" << p->get_name() << " (Computer) is thinking..." << endl;
            do {
                x = std::rand() % 3;
                y = std::rand() % 3;
            } while (p->get_board_ptr()->get_cell(x, y) != 0);
            cout << "Computer plays at (" << x << ", " << y << ")" << endl;
            return new Move<char>(x, y, p->get_symbol());
        } else {
            cout << "\n" << p->get_name() << " (" << p->get_symbol() << "), enter row (0-2) and col (0-2): ";
            while (!(std::cin >> x >> y)) {
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                cout << "Invalid input. Please enter numbers: ";
            }
            return new Move<char>(x, y, p->get_symbol());
        }
    }
};

#endif
