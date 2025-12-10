#ifndef DIAMOND_UI_H
#define DIAMOND_UI_H

#include "BoardGame_Classes.h"
#include "DiamondBoard.h"
#include "DiamondMinimaxPlayer.h"
#include <iostream>
#include <iomanip>
#include <limits>

using namespace std;

/**
 * @brief User Interface class for Diamond Tic-Tac-Toe.
 * @details This class inherits from the generic UI class and handles the specific
 * visualization and input requirements for the diamond-shaped board.
 */
class DiamondUI : public UI<char> {
public:
    /**
     * @brief Constructor for DiamondUI.
     * @details Initializes the UI with a dimension of 3 (though the grid is 5x5 effectively).
     */
    DiamondUI() : UI<char>(3) {}

    /**
     * @brief Displays the Diamond board configuration.
     * @details Iterates through a 5x5 grid and only displays cells that are part of the diamond.
     * Cells outside the diamond are masked with '#'.
     * @param board Pointer to the generic Board object.
     */
    void display_board(Board<char>* board) {
        DiamondBoard* diamondBoard = dynamic_cast<DiamondBoard*>(board);

        cout << "\n==================================" << endl;
        cout << "      DIAMOND TIC-TAC-TOE" << endl;
        cout << "==================================" << endl;
        cout << "\n     0   1   2   3   4  " << endl;
        cout << "   ---------------------" << endl;

        for (int i = 0; i < 5; i++) {
            cout << i << " |";

            for (int j = 0; j < 5; j++) {
                // Check if the cell is valid within the diamond shape
                if (diamondBoard->is_inside_diamond(i, j)) {
                    char cell = board->get_cell(i, j);
                    if (cell == 0) {
                        cout << "   |";
                    }
                    else {
                        cout << " " << cell << " |";
                    }
                }
                else {
                    cout << " # |"; // Mask invalid cells
                }
            }
            cout << endl;
            cout << "   ---------------------" << endl;
        }

        cout << "\nLegend: # = Outside diamond, Empty = Available" << endl;
        cout << "==================================" << endl;
    }

    /**
     * @brief Gets a valid move from the player.
     * @details Handles two scenarios:
     * 1. AI Player: Calls the minimax algorithm to get the best move.
     * 2. Human Player: Prompts for input and validates it (bounds, inside diamond, empty cell).
     * @param player Pointer to the current player.
     * @return Pointer to the Move object.
     */
    Move<char>* get_move(Player<char>* player) override {
        // Check if the player is an AI
        DiamondMinimaxPlayer<char>* aiPlayer = dynamic_cast<DiamondMinimaxPlayer<char>*>(player);

        if (aiPlayer != nullptr) {
            cout << "\n" << player->get_name() << " (AI) is thinking..." << endl;
            Move<char>* aiMove = aiPlayer->get_best_move(player->get_board_ptr());
            cout << "AI plays at position (" << aiMove->get_x() << ", " << aiMove->get_y() << ")" << endl;
            return aiMove;
        }

        // Human player logic
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

            // Validation checks
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

    /**
     * @brief Displays the final game result.
     * @details Prints who won or if it was a draw, along with the specific winning condition.
     * @param winner Pointer to the winning player (nullptr if draw).
     */
    void display_winner(Player<char>* winner) {
        cout << "\n==================================" << endl;
        cout << "          GAME OVER!" << endl;
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

    /**
     * @brief Factory method to create players.
     * @details Creates a DiamondMinimaxPlayer if the type is COMPUTER, otherwise creates a standard Player.
     * @param name Name of the player.
     * @param symbol Symbol of the player.
     * @param type Type of the player (HUMAN or COMPUTER).
     * @return Pointer to the created Player object.
     */
    Player<char>* create_player(string& name, char symbol, PlayerType type) override {
        if (type == PlayerType::COMPUTER) {
            return new DiamondMinimaxPlayer<char>(name, symbol);
        }
        return new Player<char>(name, symbol, type);
    }
};

#endif
