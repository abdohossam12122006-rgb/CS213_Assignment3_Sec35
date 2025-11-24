#ifndef MISERE_MINIMAX_PLAYER_H
#define MISERE_MINIMAX_PLAYER_H

#include "BoardGame_Classes.h"
#include "MisereTicTacToe.h"
#include <limits>

template <typename T>
class MisereMinimaxPlayer : public Player<T> {
public:
    MisereMinimaxPlayer(string name, T symbol)
        : Player<T>(name, symbol, PlayerType::COMPUTER) {}

    Move<T>* get_best_move(Board<T>* board) {
        int bestScore = numeric_limits<int>::max();
        int bestX = -1, bestY = -1;

        for (int i = 0; i < board->get_rows(); i++) {
            for (int j = 0; j < board->get_columns(); j++) {
                if (board->get_cell(i, j) == 0) {
                    Move<T> testMove(i, j, this->symbol);
                    board->update_board(&testMove);

                    int score = minimax(board, 0, false);

                    MisereBoard* misereBoard = dynamic_cast<MisereBoard*>(board);
                    misereBoard->undo_move(i, j);

                    if (score < bestScore) {
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
    int minimax(Board<T>* board, int depth, bool isMaximizing) {
        MisereBoard* misereBoard = dynamic_cast<MisereBoard*>(board);

        if (misereBoard->is_lose(this)) {
            return 10 - depth;
        }

        Player<T> opponent("Temp", (this->symbol == 'X' ? 'O' : 'X'), PlayerType::HUMAN);
        if (misereBoard->is_lose(&opponent)) {
            return depth - 10;
        }

        if (misereBoard->is_draw(this)) {
            return 0;
        }

        if (isMaximizing) {
            int maxScore = numeric_limits<int>::min();

            for (int i = 0; i < board->get_rows(); i++) {
                for (int j = 0; j < board->get_columns(); j++) {
                    if (board->get_cell(i, j) == 0) {
                        Move<T> testMove(i, j, this->symbol);
                        board->update_board(&testMove);

                        int score = minimax(board, depth + 1, false);
                        maxScore = max(maxScore, score);

                        misereBoard->undo_move(i, j);
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
                    if (board->get_cell(i, j) == 0) {
                        Move<T> testMove(i, j, opponentSymbol);
                        board->update_board(&testMove);

                        int score = minimax(board, depth + 1, true);
                        minScore = min(minScore, score);

                        misereBoard->undo_move(i, j);
                    }
                }
            }
            return minScore;
        }
    }
};

#endif