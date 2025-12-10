#ifndef GAME_7__H
#define GAME_7__H

#include "BoardGame_Classes.h"
#include <iostream>
#include <iomanip>
#include <algorithm>
#include <vector>
#include <cmath>
using namespace std;

// Forward declarations
class Game7_AI_Player;
class Game7_Board;

/**
 * @class Game7_Board
 * @brief Class representing a 4x4 Tic-Tac-Toe board where players move existing tokens.
 * 
 * Special rules:
 * - Players start with predefined positions.
 * - Goal: make 3 in a row by moving tokens to adjacent empty cells.
 */
class Game7_Board : public Board<char> {
private:
    /**
     * @brief Check if a symbol has three in a row (horizontal, vertical, diagonal).
     * 
     * @param symbol Symbol to check ('X' or 'O')
     * @return true if symbol has three in a row
     * @return false otherwise
     */
    bool check_three_in_a_row(char symbol) {
        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j <= columns - 3; ++j) {
                if (board[i][j] == symbol && board[i][j + 1] == symbol && board[i][j + 2] == symbol) return true;
            }
        }
        for (int j = 0; j < columns; ++j) {
            for (int i = 0; i <= rows - 3; ++i) {
                if (board[i][j] == symbol && board[i + 1][j] == symbol && board[i + 2][j] == symbol) return true;
            }
        }
        for (int i = 0; i <= rows - 3; ++i) {
            for (int j = 0; j <= columns - 3; ++j) {
                if (board[i][j] == symbol && board[i + 1][j + 1] == symbol && board[i + 2][j + 2] == symbol) return true;
            }
            for (int j = 2; j < columns; ++j) {
                if (board[i][j] == symbol && board[i + 1][j - 1] == symbol && board[i + 2][j - 2] == symbol) return true;
            }
        }
        return false;
    }

    /**
     * @brief Decode an encoded move symbol into player symbol and old coordinates.
     * 
     * @param encoded_symbol Encoded character representing the move
     * @param player_symbol Output: 'X' or 'O'
     * @param old_x Output: old row
     * @param old_y Output: old column
     */
    void decode_move(char encoded_symbol, char& player_symbol, int& old_x, int& old_y) {
        if (encoded_symbol >= 'Q') {
            player_symbol = 'O';
            int offset = encoded_symbol - 'Q';
            old_x = offset / 4;
            old_y = offset % 4;
        } else {
            player_symbol = 'X';
            int offset = encoded_symbol - 'A';
            old_x = offset / 4;
            old_y = offset % 4;
        }
    }

public:
    /**
     * @brief Constructor: initialize the 4x4 board with starting positions.
     */
    Game7_Board() : Board<char>(4, 4) {
        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < columns; ++j) {
                board[i][j] = ' ';
            }
        }
        board[0][0] = board[0][2] = board[3][1] = board[3][3] = 'X';
        board[3][0] = board[3][2] = board[0][3] = board[0][1] = 'O';
    }

    /**
     * @brief Update the board with a move.
     * 
     * @param move Pointer to Move object
     * @return true if move applied successfully
     * @return false if move is invalid
     */
    bool update_board(Move<char>* move) override {
        int new_x = move->get_x();
        int new_y = move->get_y();
        char encoded_symbol = move->get_symbol();

        char symbol;
        int old_x, old_y;
        decode_move(encoded_symbol, symbol, old_x, old_y);

        if (old_x < 0 || old_x >= rows || old_y < 0 || old_y >= columns ||
            new_x < 0 || new_x >= rows || new_y < 0 || new_y >= columns) {
            return false;
        }

        if (board[old_x][old_y] != symbol) return false;
        if (board[new_x][new_y] != ' ') return false;

        int dx = abs(new_x - old_x);
        int dy = abs(new_y - old_y);
        if (!((dx == 1 && dy == 0) || (dx == 0 && dy == 1))) return false;

        board[old_x][old_y] = ' ';
        board[new_x][new_y] = symbol;
        n_moves++;
        return true;
    }

    /**
     * @brief Check if a player has won.
     * 
     * @param player Pointer to Player
     * @return true if player has 3 in a row
     */
    bool is_win(Player<char>* player) override {
        return check_three_in_a_row(player->get_symbol());
    }

    /**
     * @brief Check if a player has lost.
     * 
     * @param player Pointer to Player
     * @return true if opponent has 3 in a row
     */
    bool is_lose(Player<char>* player) override {
        char opponent_symbol = (player->get_symbol() == 'X') ? 'O' : 'X';
        return check_three_in_a_row(opponent_symbol);
    }

    /**
     * @brief Check if the game is a draw (always false in this game).
     */
    bool is_draw(Player<char>*) override { return false; }

    /**
     * @brief Check if the game is over (win or lose).
     */
    bool game_is_over(Player<char>* player) override {
        return is_win(player) || is_lose(player);
    }

    /**
     * @brief Get all valid moves for a given symbol.
     * 
     * @param symbol Symbol ('X' or 'O')
     * @return vector<Move<char>*> List of valid moves
     */
    vector<Move<char>*> get_valid_moves(char symbol) const {
        vector<Move<char>*> valid_moves;
        int dr[] = { -1, 1, 0, 0 };
        int dc[] = { 0, 0, -1, 1 };

        for (int r = 0; r < rows; ++r) {
            for (int c = 0; c < columns; ++c) {
                if (board[r][c] == symbol) {
                    for (int i = 0; i < 4; ++i) {
                        int nr = r + dr[i];
                        int nc = c + dc[i];
                        if (nr >= 0 && nr < rows && nc >= 0 && nc < columns && board[nr][nc] == ' ') {
                            char base = (symbol == 'X') ? 'A' : 'Q';
                            char encoded_symbol = base + (r * 4) + c;
                            valid_moves.push_back(new Move<char>(nr, nc, encoded_symbol));
                        }
                    }
                }
            }
        }
        return valid_moves;
    }
};

/**
 * @class Game7_Player
 * @brief Represents a human or generic player in Game 7.
 */
class Game7_Player : public Player<char> {
public:
    Game7_Player(string n, char s, PlayerType t) : Player<char>(n, s, t) {}
};

/**
 * @class Game7_AI_Player
 * @brief AI-controlled player for Game 7 using minimax algorithm.
 */
class Game7_AI_Player : public Game7_Player {
private:
    char opponent_symbol;
    const int SEARCH_DEPTH = 5;

    /**
     * @brief Get the board casted to Game7_Board.
     */
    Game7_Board* get_game_board() {
        return static_cast<Game7_Board*>(boardPtr);
    }

    /**
     * @brief Evaluate the board for minimax.
     */
    int evaluate(Game7_Board* board) {
        if (board->is_win(this)) return 10000;
        if (board->is_lose(this)) return -10000;
        return 0;
    }

    /**
     * @brief Minimax algorithm with depth limit.
     */
    int minimax(Game7_Board* board, int depth, bool is_maximizing_player) {
        if (depth == 0 || board->game_is_over(this)) return evaluate(board);

        char current_player_symbol = is_maximizing_player ? symbol : opponent_symbol;
        int best_eval = is_maximizing_player ? -100000 : 100000;

        vector<Move<char>*> moves = board->get_valid_moves(current_player_symbol);
        if (moves.empty()) return evaluate(board);

        for (Move<char>* move : moves) {
            Game7_Board next_board = *board;
            if (next_board.update_board(move)) {
                int eval = minimax(&next_board, depth - 1, !is_maximizing_player);
                if (is_maximizing_player) best_eval = max(best_eval, eval);
                else best_eval = min(best_eval, eval);
            }
            delete move;
        }
        return best_eval;
    }

public:
    Game7_AI_Player(string n, char s) : Game7_Player(n, s, PlayerType::AI) {
        opponent_symbol = (s == 'X') ? 'O' : 'X';
    }

    /**
     * @brief Compute the best move for AI using minimax.
     * 
     * @return Move<char>* Pointer to the best move
     */
    Move<char>* get_best_move() {
        Game7_Board* current_board = get_game_board();
        if (!current_board) return nullptr;

        vector<Move<char>*> valid_moves = current_board->get_valid_moves(symbol);
        if (valid_moves.empty()) return nullptr;

        int best_eval = -100000;
        Move<char>* best_move = nullptr;

        for (Move<char>* move : valid_moves) {
            Game7_Board next_board = *current_board;
            if (next_board.update_board(move)) {
                int eval = minimax(&next_board, SEARCH_DEPTH, false);
                if (eval > best_eval) {
                    best_eval = eval;
                    if (best_move) delete best_move;
                    best_move = new Move<char>(move->get_x(), move->get_y(), move->get_symbol());
                }
            }
            delete move;
        }

        if (!best_move && !valid_moves.empty()) best_move = valid_moves[0];
        return best_move;
    }
};

/**
 * @class Game7_UI
 * @brief Handles input/output and AI/human interaction for Game 7.
 */
class Game7_UI : public UI<char> {
private:
    /**
     * @brief Encode a move symbol for storage.
     */
    char encode_move_symbol(char symbol, int old_x, int old_y) {
        char base = (symbol == 'X') ? 'A' : 'Q';
        return base + (old_x * 4) + old_y;
    }

public:
    Game7_UI() : UI<char>(4) {
        display_message("Welcome to 4x4 Tic-Tac-Toe (Game 7)! Goal: 3 in a row by moving your tokens.");
    }

    /**
     * @brief Create a player (AI or human)
     */
    Player<char>* create_player(string& name, char symbol, PlayerType type) override {
        if (type == PlayerType::AI || type == PlayerType::COMPUTER) {
            return new Game7_AI_Player(name, symbol);
        } else {
            return new Game7_Player(name, symbol, type);
        }
    }

    /**
     * @brief Get the next move from player (AI or human)
     */
    Move<char>* get_move(Player<char>* player) override {
        if (player->get_type() == PlayerType::AI || player->get_type() == PlayerType::COMPUTER) {
            Game7_AI_Player* ai_player = static_cast<Game7_AI_Player*>(player);
            display_message("AI Player (" + player->get_name() + ") is thinking...");
            return ai_player->get_best_move();
        } else {
            int old_x, old_y, new_x, new_y;
            cout << "Player " << player->get_symbol() << " (" << player->get_name() << "): Enter old position (row, col) and new position (row, col): ";
            cin >> old_x >> old_y >> new_x >> new_y;

            char encoded_symbol = encode_move_symbol(player->get_symbol(), old_x, old_y);
            return new Move<char>(new_x, new_y, encoded_symbol);
        }
    }
};

#endif
