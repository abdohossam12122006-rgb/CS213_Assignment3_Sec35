#include <iostream>
#include <string>
#include <vector>
#include <limits>
#include "BoardGame_Classes.h"
#include "XO_Classes.h"

// --- Game Headers ---
// Group 1
#include "SUS_Board.h"
#include "SUS_UI.h"

// Group 2
#include "Four_in_a_row_Board.h"
#include "Four_in_a_row_Random_Player.h"

// Group 3 (NEW)
#include "FiveByFiveBoard.h"
#include "Word_Board.h"
#include "Word_UI.h"

// Group 4 & Others
#include "MisereTicTacToe.h"
#include "MisereMinimaxPlayer.h"
#include "MisereUI.h"
#include "DiamondBoard.h"
#include "DiamondMinimaxPlayer.h"
#include "DiamondUI.h"

using namespace std;

void display_menu() {
    cout << "\n========================================\n";
    cout << "    Welcome to the CS213 Game Center!    \n";
    cout << "========================================\n";
    cout << " 1. SUS Game\n";
    cout << " 2. Four-in-a-row Game\n";
    cout << " 3. 5x5 Tic Tac Toe (Ready)\n";
    cout << " 4. Word Tic-tac-toe (Ready)\n";
    cout << " 5. Misere Tic Tac Toe\n";
    cout << " 6. Diamond Tic-Tac-Toe\n";
    cout << " 14. X-O Game (Example)\n";
    cout << " 0. Exit\n";
    cout << "========================================\n";
    cout << "Enter your choice: ";
}

void run_game_selection(int choice) {
    Board<char>* board = nullptr;
    UI<char>* ui = nullptr;
    Player<char>* players[2] = { nullptr, nullptr };
    GameManager<char>* gameManager = nullptr;

    switch (choice) {
        // --- Game 1: SUS ---
    case 1: {
        board = new SUS_Board();
        players[0] = new Player<char>("P1", 'S', PlayerType::HUMAN);
        players[1] = new Player<char>("P2", 'U', PlayerType::HUMAN);
        ui = new SUS_UI();
        gameManager = new GameManager<char>(board, players, ui);
        gameManager->run();

        if (auto susBoard = dynamic_cast<SUS_Board*>(board)) {
            cout << "Score -> P1: " << susBoard->get_score(0)
                << " | P2: " << susBoard->get_score(1) << endl;
        }
        break;
    }

          // --- Game 2: Four-in-a-row ---
    case 2: {
        board = new Four_in_a_row_Board();
        players[0] = new Player<char>("P1", 'X', PlayerType::HUMAN);
        cout << "1. Human vs Human\n2. Human vs Random Computer\nChoice: ";
        int c; cin >> c;
        if (c == 2) players[1] = new Four_in_a_row_Random_Player<char>('O');
        else players[1] = new Player<char>("P2", 'O', PlayerType::HUMAN);

        ui = new XO_UI(); 
        gameManager = new GameManager<char>(board, players, ui);
        gameManager->run();
        break;
    }

          // --- Game 3: 5x5 Tic Tac Toe (NEW) ---
    case 3: {
        cout << "\n--- Starting 5x5 Tic Tac Toe ---\n";
        cout << "Goal: Get the most 3-in-a-rows (vertical, horizontal, diagonal).\n";
        board = new FiveByFiveBoard();
        players[0] = new Player<char>("P1", 'X', PlayerType::HUMAN);
        players[1] = new Player<char>("P2", 'O', PlayerType::HUMAN);

        ui = new XO_UI();

        gameManager = new GameManager<char>(board, players, ui);
        gameManager->run();

        if (auto b = dynamic_cast<FiveByFiveBoard*>(board)) {
            cout << "X Count: " << b->count_three_in_a_row('X') << endl;
            cout << "O Count: " << b->count_three_in_a_row('O') << endl;
        }
        break;
    }

          // --- Game 4: Word Tic-tac-toe (NEW) ---
    case 4: {
        cout << "\n--- Starting Word Tic-tac-toe ---\n";
        cout << "Goal: Form a valid English word (3 letters).\n";
        board = new WordBoard();
        players[0] = new Player<char>("P1", '?', PlayerType::HUMAN);
        players[1] = new Player<char>("P2", '?', PlayerType::HUMAN);

        ui = new Word_UI();

        gameManager = new GameManager<char>(board, players, ui);
        gameManager->run();
        break;
    }

          // --- Game 5: Misere ---
    case 5: {
        board = new MisereBoard();
        players[0] = new Player<char>("P1", 'X', PlayerType::HUMAN);
        cout << "1. Human vs Human\n2. Human vs AI\nChoice: ";
        int c; cin >> c;
        if (c == 2) {
            players[1] = new MisereMinimaxPlayer<char>("AI", 'O');
            players[1]->set_board_ptr(board);
        }
        else players[1] = new Player<char>("P2", 'O', PlayerType::HUMAN);
        ui = new MisereUI();
        gameManager = new GameManager<char>(board, players, ui);
        gameManager->run();
        break;
    }

          // --- Game 6: Diamond ---
    case 6: {
        cout << "\n--- Diamond Tic-Tac-Toe ---\n";
        board = new DiamondBoard();

        players[0] = new Player<char>("P1", 'X', PlayerType::HUMAN);

        cout << "1. Human vs Human\n2. Human vs AI\nChoice: ";
        int c;
        cin >> c;

        if (c == 2) {
            players[1] = new DiamondMinimaxPlayer<char>("AI", 'O');
            players[1]->set_board_ptr(board);
            cout << "AI is ready!\n";
        }
        else {
            players[1] = new Player<char>("P2", 'O', PlayerType::HUMAN);
        }

        ui = new DiamondUI();
        gameManager = new GameManager<char>(board, players, ui);
        gameManager->run();
        break;
    }


          // --- Example Game ---
    case 14: {
        board = new X_O_Board();
        players[0] = new Player<char>("P1", 'X', PlayerType::HUMAN);
        players[1] = new Player<char>("P2", 'O', PlayerType::HUMAN);
        ui = new XO_UI();
        gameManager = new GameManager<char>(board, players, ui);
        gameManager->run();
        break;
    }

    default:
        cout << "Invalid Choice or Game Not Loaded.\n";
        break;
    }

    if (gameManager) delete gameManager;
    if (board) delete board;
    if (players[0]) delete players[0];
    if (players[1]) delete players[1];
    if (ui) delete ui;
}

int main() {
    int choice = -1;
    while (true) {
        display_menu();
        if (!(cin >> choice)) {
            cin.clear(); cin.ignore(10000, '\n');
            continue;
        }
        if (choice == 0) break;
        run_game_selection(choice);
    }
    return 0;
}
