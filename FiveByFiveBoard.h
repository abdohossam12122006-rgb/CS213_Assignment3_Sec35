#ifndef FIVEBYFIVEBOARD_H
#define FIVEBYFIVEBOARD_H

#include "BoardGame_Classes.h"
#include <vector>
using namespace std;

/**
 * @class FiveByFiveBoard
 * @brief A 5x5 Tic-Tac-Toe variant where scoring counts the number of 3-in-a-row.
 *
 * The game ends when all 24 valid moves are played.  
 * Winner = player with highest number of 3-symbol sequences.
 */
class FiveByFiveBoard : public Board<char> {
public:

    /**
     * @brief Constructor initializes a 5x5 empty board.
     */
    FiveByFiveBoard() : Board<char>(5, 5) {
        this->n_moves = 0;
        for (int i = 0; i < rows; i++)
            for (int j = 0; j < columns; j++)
                board[i][j] = 0;
    }

    /**
     * @brief Places a move on the board if cell is valid and empty.
     * @param move Pointer to Move containing (row, col, symbol)
     * @return true if move is applied, false otherwise
     */
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

    /**
     * @brief Counts number of 3-in-a-row sequences for a symbol.
     * @param symbol Character ('X' or 'O')
     * @return Total number of threes
     */
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

    /**
     * @brief Determines if player wins by having more threes when board is full.
     */
    bool is_win(Player<char>* player) override {
        char sym = player->get_symbol();
        char opp = (sym == 'X' ? 'O' : 'X');

        int myScore = count_threes(sym);
        int oppScore = count_threes(opp);

        if (n_moves == 24)
            return myScore > oppScore;

        return false;
    }

    /**
     * @brief Game is a draw when both players have equal number of threes.
     */
    bool is_draw(Player<char>* player) override {
        if (n_moves < 24) return false;

        char sym = player->get_symbol();
        char opp = (sym == 'X' ? 'O' : 'X');

        return count_threes(sym) == count_threes(opp);
    }

    /**
     * @brief This game mode has no losing condition (only win or draw).
     */
    bool is_lose(Player<char>* player) override {
        return false;
    }

    /**
     * @brief Ends when 24 moves are played.
     */
    bool game_is_over(Player<char>* player) override {
        return n_moves == 24;
    }
};

// ==========================================
// ============  AI PLAYER  =================
// ==========================================

/**
 * @class AIPlayer
 * @brief Simple AI that selects random valid empty cells.
 */
class AIPlayer : public Player<char> {
public:

    /**
     * @brief Constructor for AIPlayer.
     * @param name Player name
     * @param symbol 'X' or 'O'
     */
    AIPlayer(string name, char symbol)
        : Player<char>(name, symbol, PlayerType::COMPUTER)
    {
    }

    /**
     * @brief Generates a random valid move.
     */
    Move<char>* get_move(Board<char>* board) {
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
