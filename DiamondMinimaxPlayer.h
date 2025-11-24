#ifndef DIAMOND_MINIMAX_PLAYER_H
#define DIAMOND_MINIMAX_PLAYER_H

#include "BoardGame_Classes.h"
#include "DiamondBoard.h"
#include <limits>

template <typename T>
class DiamondMinimaxPlayer : public Player<T> {
public:
    DiamondMinimaxPlayer(string name, T symbol)
        : Player<T>(name, symbol, PlayerType::COMPUTER) {}

    Move<T>* get_best_move(Board<T>* board) {
        int bestScore = numeric_limits<int>::min();
        int bestX = -1, bestY = -1;

        DiamondBoard* diamondBoard = dynamic_cast<DiamondBoard*>(board);

        for (int i = 0; i < board->get_rows(); i++) {
            for (int j = 0; j < board->get_columns(); j++) {
                if (diamondBoard->is_inside_diamond(i, j) && board->get_cell(i, j) == 0) {
                    Move<T> testMove(i, j, this->symbol);
                    board->update_board(&testMove);

                    int score = minimax(board, 0, 4, false);

                    diamondBoard->undo_move(i, j);

                    if (score > bestScore) {
                        bestScore = score;
                        bestX = i;
                        bestY = j;
                    }
                }
            }
        }

        return new Move<T>(bestX, bestY, this->symbol);
    }

private:
    int minimax(Board<T>* board, int depth, int maxDepth, bool isMaximizing) {
        if (board->is_win(this)) {
            return 1000 - depth;
        }

        Player<T> opponent("Temp", (this->symbol == 'X' ? 'O' : 'X'), PlayerType::HUMAN);
        if (board->is_win(&opponent)) {
            return depth - 1000;
        }

        if (board->is_draw(this)) {
            return 0;
        }

        if (depth >= maxDepth) {
            return evaluate_position(board);
        }

        DiamondBoard* diamondBoard = dynamic_cast<DiamondBoard*>(board);

        if (isMaximizing) {
            int maxScore = numeric_limits<int>::min();

            for (int i = 0; i < board->get_rows(); i++) {
                for (int j = 0; j < board->get_columns(); j++) {
                    if (diamondBoard->is_inside_diamond(i, j) && board->get_cell(i, j) == 0) {
                        Move<T> testMove(i, j, this->symbol);
                        board->update_board(&testMove);

                        int score = minimax(board, depth + 1, maxDepth, false);
                        maxScore = max(maxScore, score);

                        diamondBoard->undo_move(i, j);
                    }
                }
            }
            return maxScore;
        }
        else {
            int minScore = numeric_limits<int>::max();
            T opponentSymbol = (this->symbol == 'X' ? 'O' : 'X');

            for (int i = 0; i < board->get_rows(); i++) {
                for (int j = 0; j < board->get_columns(); j++) {
                    if (diamondBoard->is_inside_diamond(i, j) && board->get_cell(i, j) == 0) {
                        Move<T> testMove(i, j, opponentSymbol);
                        board->update_board(&testMove);

                        int score = minimax(board, depth + 1, maxDepth, true);
                        minScore = min(minScore, score);

                        diamondBoard->undo_move(i, j);
                    }
                }
            }
            return minScore;
        }
    }

    int evaluate_position(Board<T>* board) {
        int score = 0;
        DiamondBoard* diamondBoard = dynamic_cast<DiamondBoard*>(board);

        if (diamondBoard->get_cell(2, 2) == this->symbol) {
            score += 10;
        }

        return score;
    }
};

#endif