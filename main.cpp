#include <iostream>
#include <string>
#include <vector>
#include <limits>
#include "BoardGame_Classes.h"
#include "XO_Classes.h"
#include "NumericalPlayer.h"
#include "NumericalBoard.h"
#include "NumericalUI.h"
#include "MisereTicTacToe.h"
#include "MisereMinimaxPlayer.h"
#include "MisereUI.h"
#include "DiamondBoard.h"
#include "DiamondMinimaxPlayer.h"
#include "DiamondUI.h"

using namespace std;

static void display_menu() {
    cout << "========================================" << endl;
    cout << "    Welcome to the CS213 Game Center!   " << endl;
    cout << "========================================" << endl;
    cout << "  Individual Games (Set 1):" << endl;
    cout << "     1. SUS" << endl;
    cout << "     2. Four-in-a-row" << endl;
    cout << "  Individual Games (Set 2):" << endl;
    cout << "     3. 5x5 Tic Tac Toe" << endl;
    cout << "     4. Word Tic-tac-toe" << endl;
    cout << "  Individual Games (Set 3):" << endl;
    cout << "     5. Misere Tic Tac Toe (with AI)" << endl;
    cout << "     6. Diamond Tic-Tac-Toe (with AI)" << endl;
    cout << "  Individual Games (Set 4):" << endl;
    cout << "     7. 4x4 Tic-Tac-Toe" << endl;
    cout << "     8. Pyramid Tic-Tac-Toe" << endl;
    cout << "--- Group Games ---" << endl;
    cout << "     9. Numerical Tic-Tac-Toe" << endl;
    cout << "     10. Obstacles Tic-Tac-Toe" << endl;
    cout << "     11. Infinity Tic-Tac-Toe" << endl;
    cout << "--- Bonus Group Games ---" << endl;
    cout << "     12. Ultimate Tic Tac Toe" << endl;
    cout << "     13. Memory Tic-Tac-Toe" << endl;
    cout << "----------------------------------------" << endl;
    cout << "     14. (Example) X-O Game" << endl;
    cout << "     0. Exit" << endl;
    cout << "========================================" << endl;
    cout << "Enter your choice (0-14): ";
}

static void clear_screen() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

static void pause_screen() {
    cout << "\nPress Enter to return to the main menu..." << endl;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cin.get();
}

static void run_game_selection(int choice) {
    clear_screen();

    Board<char>* board = nullptr;
    UI<char>* ui = nullptr;
    Player<char>** players = nullptr;
    GameManager<char>* gameManager = nullptr;

    switch (choice) {
    case 1:
        cout << "Starting Game: SUS..." << endl;
        break;
    case 2:
        cout << "Starting Game: Four-in-a-row..." << endl;
        break;
    case 3:
        cout << "Starting Game: 5x5 Tic Tac Toe..." << endl;
        break;
    case 4:
        cout << "Starting Game: Word Tic-tac-toe..." << endl;
        break;

    case 5:
        cout << "Starting Misere Tic Tac Toe..." << endl;

        board = new MisereBoard();
        ui = new MisereUI();
        players = ui->setup_players();

        gameManager = new GameManager<char>(board, players, ui);
        gameManager->run();

        delete gameManager;
        delete board;
        delete players[0];
        delete players[1];
        delete[] players;
        delete ui;
        break;

    case 6:
        cout << "Starting Diamond Tic-Tac-Toe..." << endl;

        board = new DiamondBoard();
        ui = new DiamondUI();
        players = ui->setup_players();

        gameManager = new GameManager<char>(board, players, ui);
        gameManager->run();

        delete gameManager;
        delete board;
        delete players[0];
        delete players[1];
        delete[] players;
        delete ui;
        break;

    case 7:
        cout << "Starting Game: 4x4 Tic-Tac-Toe..." << endl;
        break;
    case 8:
        cout << "Starting Game: Pyramid Tic-Tac-Toe..." << endl;
        break;

    case 9:
        cout << "Starting Game: Numerical Tic-Tac-Toe..." << endl;

        board = new NumericalBoard();
        ui = new NumericalUI();

        {
            vector<int> odds = { 1, 3, 5, 7, 9 };
            vector<int> evens = { 2, 4, 6, 8 };
            Player<char>* numPlayers[2];
            numPlayers[0] = new NumericalPlayer('X', "Player 1 (Odd)", odds, PlayerType::HUMAN);
            numPlayers[1] = new NumericalPlayer('O', "Player 2 (Even)", evens, PlayerType::HUMAN);

            gameManager = new GameManager<char>(board, numPlayers, ui);
            gameManager->run();

            delete board;
            delete ui;
            delete numPlayers[0];
            delete numPlayers[1];
            delete gameManager;
        }
        break;

    case 10:
        cout << "Starting Game: Obstacles Tic-Tac-Toe..." << endl;
        break;
    case 11:
        cout << "Starting Game: Infinity Tic-Tac-Toe..." << endl;
        break;
    case 12:
        cout << "Starting Game: Ultimate Tic Tac Toe..." << endl;
        break;
    case 13:
        cout << "Starting Game: Memory Tic-Tac-Toe..." << endl;
        break;
    case 14:
        cout << "Starting Game: (Example) X-O Game..." << endl;

        board = new X_O_Board();
        {
            Player<char>* xoPlayers[2];
            xoPlayers[0] = new Player<char>("Player 1", 'X', PlayerType::HUMAN);
            xoPlayers[1] = new Player<char>("Player 2", 'O', PlayerType::HUMAN);
            ui = new XO_UI();

            gameManager = new GameManager<char>(board, xoPlayers, ui);
            gameManager->run();

            delete board;
            delete ui;
            delete xoPlayers[0];
            delete xoPlayers[1];
            delete gameManager;
        }
        break;

    default:
        cout << "Invalid choice. Please select a number from the menu." << endl;
        break;
    }
}


int main() {
    int choice = -1;

    while (true) {
        clear_screen();
        display_menu();

        while (!(cin >> choice)) {
            cout << "Invalid input. Please enter a number: ";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }

        if (choice == 0) {
            clear_screen();
            cout << "Thank you for playing. Goodbye!" << endl;
            return 0;
        }

        run_game_selection(choice);

        if (choice >= 1 && choice <= 14) {
            pause_screen();
        }
    }

    return 0;
}