#ifndef PYRAMID_H
#define PYRAMID_H

#include "BoardGame_Classes.h"
#include <iostream>
#include <iomanip>
#include <algorithm>
using namespace std;

/**
 * @class Pyramid_Board
 * @brief Class representing a Pyramid-shaped Tic-Tac-Toe board.
 * 
 * The board layout is a pyramid:
 * - Row 0: 1 cell (column 2)
 * - Row 1: 3 cells (columns 1-3)
 * - Row 2: 5 cells (columns 0-4)
 * 
 * Inherits from Board<char>.
 */
class Pyramid_Board : public Board<char> {
public:
    /**
     * @brief Constructor that initializes the board with empty cells (0) and move counter.
     */
    Pyramid_Board() : Board<char>(3, 5) {
        for (int i = 0; i < 3; i++)
            for (int j = 0; j < 5; j++)
                board[i][j] = 0;
        n_moves = 0;
    }

    /**
     * @brief Update the board with a player's move.
     * 
     * @param move Pointer to the Move object containing row, column, and symbol.
     * @return true if move is valid and applied.
     * @return false if move is invalid or cell occupied.
     */
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

    /**
     * @brief Check if a player has won the game.
     * 
     * @param p Pointer to the player.
     * @return true if the player has won.
     * @return false otherwise.
     */
    bool is_win(Player<char>* p) override {
        char symbol = p->get_symbol();
        // Vertical
        if (board[0][2] == symbol && board[1][2] == symbol && board[2][2] == symbol) return true;
        // Diagonal down right
        if (board[0][2] == symbol && board[1][1] == symbol && board[2][0] == symbol) return true;
        // Diagonal down left
        if (board[0][2] == symbol && board[1][3] == symbol && board[2][4] == symbol) return true;
        // Horizontal middle
        if (board[1][1] == symbol && board[1][2] == symbol && board[1][3] == symbol) return true;
        // Horizontal bottom
        for (int c = 0; c <= 2; ++c)
            if (board[2][c] == symbol && board[2][c + 1] == symbol && board[2][c + 2] == symbol) return true;
        return false;
    }

    /**
     * @brief Check if the game is a draw.
     * 
     * @param p Pointer to the player.
     * @return true if the game is a draw.
     * @return false otherwise.
     */
    bool is_draw(Player<char>* p) override {
        return (n_moves == 9 && !is_win(p));
    }

    /**
     * @brief Check if the game is over (win or draw).
     * 
     * @param p Pointer to the player.
     * @return true if game is over.
     * @return false otherwise.
     */
    bool game_is_over(Player<char>* p) override {
        return is_win(p) || is_draw(p);
    }

    /**
     * @brief Placeholder for losing condition (not used in this game).
     */
    bool is_lose(Player<char>* p) override {
        return false;
    }

    /**
     * @brief Get the symbol at a specific cell.
     * 
     * @param r Row index.
     * @param c Column index.
     * @return char Symbol at cell.
     */
    char get_cell(int r, int c) const {
        return board[r][c];
    }

    /**
     * @brief Get the number of moves made so far.
     * 
     * @return int Number of moves.
     */
    int get_n_moves() const {
        return n_moves;
    }

    /**
     * @brief Set a cell with a symbol.
     * 
     * @param r Row index.
     * @param c Column index.
     * @param s Symbol to place.
     * @return true if successful.
     * @return false if cell is invalid or already occupied.
     */
    bool set_cell(int r, int c, char s) {
        bool valid = (r == 0 && c == 2) || (r == 1 && (c >= 1 && c <= 3)) || (r == 2);
        if (!valid || board[r][c] != 0) return false;
        board[r][c] = s;
        n_moves++;
        return true;
    }

    /**
     * @brief Reset a cell to empty.
     * 
     * @param r Row index.
     * @param c Column index.
     */
    void reset_cell(int r, int c) {
        board[r][c] = 0;
        n_moves--;
    }
};

/**
 * @class Pyramid_UI
 * @brief Class for handling Pyramid Tic-Tac-Toe UI and AI logic.
 */
class Pyramid_UI : public UI<char> {
public:
    /**
     * @brief Constructor for Pyramid_UI.
     */
    Pyramid_UI() : UI<char>("Welcome to Pyramid Tic-Tac-Toe (Game 8)!", 3) {}

    /**
     * @brief Create a new player.
     * 
     * @param name Player name.
     * @param symbol Player symbol.
     * @param type Player type (HUMAN or AI).
     * @return Player<char>* Pointer to the player object.
     */
    Player<char>* create_player(string& name, char symbol, PlayerType type) override {
        return new Player<char>(name, symbol, type);
    }

    /**
     * @brief Check if a symbol has won on the given board.
     * 
     * @param b Pointer to Pyramid_Board.
     * @param s Symbol to check.
     * @return true if symbol has won.
     * @return false otherwise.
     */
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

    /**
     * @brief Minimax algorithm to evaluate the best move for AI.
     * 
     * @param b Current board.
     * @param maximizing true if AI's turn, false if human's turn.
     * @param ai AI symbol.
     * @param human Human symbol.
     * @return int Score for the board.
     */
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

    /**
     * @brief Determine the best move for AI.
     * 
     * @param b Current board.
     * @param ai AI symbol.
     * @param human Human symbol.
     * @return Move<char>* Pointer to the best move.
     */
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

    /**
     * @brief Get the next move from a player (human or AI).
     * 
     * @param p Pointer to player.
     * @return Move<char>* Pointer to the move.
     */
    Move<char>* get_move(Player<char>* p) override {
        if (p->get_type() == PlayerType::HUMAN) {
            int x, y;
            cout << "\n" << p->get_name() << " (" << p->get_symbol()
                << "), enter your move (row 0-2, col 0-4): ";
            cin >> x >> y;
            return new Move<char>(x, y, p->get_symbol());
        }

        Pyramid_Board* b = dynamic_cast<Pyramid_Board*>(p->get_board_ptr());
        char ai = p->get_symbol();
        char human = (ai == 'X' ? 'O' : 'X');

        return get_best_move(b, ai, human);
    }
};

#endif
