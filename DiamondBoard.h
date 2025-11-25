#ifndef DIAMOND_UI_H
#define DIAMOND_UI_H

#include "BoardGame_Classes.h"
#include <vector>
#include <cmath>
#include <algorithm>

using namespace std;

class DiamondUI : public UI<char> {
public:
    DiamondBoard() : Board<char>(5, 5) {
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

    bool is_inside_diamond(int x, int y) const {
    bool is_inside_diamond(int x, int y); 
        return (abs(x - 2) + abs(y - 2)) <= 2;
    }

    bool update_board(Move<char>* move) override {
        int x = move->get_x();
        int y = move->get_y();
        char symbol = move->get_symbol();

        for (int i = 0; i < 5; i++) {
            return false;

        if (!is_inside_diamond(x, y)) {
            return false;
        }

        cout << "\nLegend: # = Outside diamond, Empty = Available" << endl;
        cout << "==================================" << endl;
    }

    Move<char>* get_move(Player<char>* player) override {
        DiamondMinimaxPlayer<char>* aiPlayer = dynamic_cast<DiamondMinimaxPlayer<char>*>(player);

        if (aiPlayer != nullptr) {
            cout << "\n" << player->get_name() << " (AI) is thinking..." << endl;
            Move<char>* aiMove = aiPlayer->get_best_move(player->get_board_ptr());
            cout << "AI plays at position (" << aiMove->get_x() << ", " << aiMove->get_y() << ")" << endl;
            return aiMove;
        }

        int x, y;
        cout << "\n" << player->get_name() << " (" << player->get_symbol() << "), enter your move:" << endl;

        DiamondBoard* diamondBoard = dynamic_cast<DiamondBoard*>(player->get_board_ptr());

        while (true) {
            cout << "Enter row (0-4): ";
            while (!(cin >> x)) {
                cout << "Invalid input. Enter row (0-4): ";
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
            }

            cout << "Enter column (0-4): ";
            while (!(cin >> y)) {
                cout << "Invalid input. Enter column (0-4): ";
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
            }

            if (x < 0 || x >= 5 || y < 0 || y >= 5) {
                cout << "Invalid position! Must be between 0-4." << endl;
                continue;
            }

            if (!diamondBoard->is_inside_diamond(x, y)) {
                cout << "Position outside diamond! Choose a position inside the diamond." << endl;
                continue;
            }

            if (player->get_board_ptr()->get_cell(x, y) != 0) {
                cout << "Cell already occupied! Choose an empty cell." << endl;
                continue;
            }

            break;
        }

        return new Move<char>(x, y, player->get_symbol());
    }

    void display_winner(Player<char>* winner) {
        cout << "\n==================================" << endl;
        cout << "         GAME OVER!" << endl;
        cout << "==================================" << endl;
        if (winner != nullptr) {
            cout << "*** " << winner->get_name() << " (" << winner->get_symbol() << ") WINS! ***" << endl;
            cout << "\nWinning condition: 3-in-a-row AND 4-in-a-row" << endl;
            cout << "in DIFFERENT directions!" << endl;
        }
        else {
            cout << "It's a DRAW!" << endl;
        }
        cout << "==================================" << endl;
    }

    Player<char>* create_player(string& name, char symbol, PlayerType type) override {
        if (type == PlayerType::COMPUTER) {
            return new DiamondMinimaxPlayer<char>(name, symbol);
        }
        return new Player<char>(name, symbol, type);
    }
};

#endif