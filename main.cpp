#include <iostream>
#include <string>
#include <vector>
#include <limits>
#include "BoardGame_Classes.h"
#include "XO_Classes.h"
#include "ObstaclesBoard.h"
#include "ObstaclesUI.h"
#include "SUS_Board.h"
#include "SUS_UI.h"
#include "Four_in_a_row_Board.h"
#include "Four_in_a_row_Random_Player.h"
#include "FiveByFiveBoard.h"
#include "Word_Board.h"
#include "MisereTicTacToe.h"
#include "MisereMinimaxPlayer.h"
#include "MisereUI.h"
#include "DiamondBoard.h"
#include "DiamondMinimaxPlayer.h"
#include "DiamondUI.h"

#include "Game_7_.h"
#include "Pyramid.h"
#include "Infinity.h"

#include "NumericalBoard.h"
#include "NumericalUI.h"
#include "UltimateTicTacToe.h"
using namespace std;

void display_menu() {
    cout << "\n========================================\n";
    cout << "    Welcome to the CS213 Game Center!    \n";
    cout << "========================================\n";
    cout << " 1. SUS Game\n";
    cout << " 2. Four-in-a-row Game\n";
    cout << " 3. 5x5 Tic Tac Toe Game \n";
    cout << " 4. Word Tic-tac-toe Game\n";
    cout << " 5. Misere Tic Tac Toe Game \n";
    cout << " 6. Diamond Tic-Tac-Toe Game \n";
    cout << " 7. 4x4 Tic-Tac-Toe Game\n";
    cout << " 8. Pyramid Tic-Tac-Toe Game\n";
    cout << " 9. Numerical Tic-Tac-Toen Game\n";
    cout << " 10. Obstacles Tic-Tac-Toen Game\n";
    cout << " 11. Infinity Tic-Tac-Toe Game\n";
    cout << " 12. Ultimate Tic-Tac-Toe Game\n";
    cout << " 13. Memory Tic-Tac-Toe Game\n";
    cout << " 14. X-O Game\n";
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
        // Game 1: SUS 
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

          //  Game 2: Four-in-a-row 
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

               //  Game 3: 5x5 Tic Tac Toe  
 case 3: {
     cout << "Starting Game: 5x5 Tic Tac Toe..." << endl;

     int mode;
     cout << "\nChoose mode:\n";
     cout << "1) Human vs Human\n";
     cout << "2) Human vs AI\n";
     cout << "Enter choice: ";
     cin >> mode;

     board = new FiveByFiveBoard();

     if (mode == 1) {
         // Human vs Human
         players[0] = new Player<char>("Player 1", 'X', PlayerType::HUMAN);
         players[1] = new Player<char>("Player 2", 'O', PlayerType::HUMAN);
     }
     else {
         // Human vs AI
         players[0] = new Player<char>("Player 1", 'X', PlayerType::HUMAN);
         players[1] = new AIPlayer("Computer", 'O');  // AI class from your .h file
     }

     ui = new XO_UI();

     gameManager = new GameManager<char>(board, players, ui);
     gameManager->run();

     delete board;
     delete ui;
     delete players[0];
     delete players[1];
     delete gameManager;
     break;
 }

             //  Game 4:  Word Tic-tac-toe
case 4:
{
    cout << "Starting Game: Word Tic-tac-toe...\n";

    board = new WordTicTacToe();
    ui = new WordUI();

    int mode;
    cout << "Choose Mode:\n1) Human vs Human\n2) Human vs AI\nEnter choice: ";
    cin >> mode;

    string name1 = "Player 1";
    string name2 = (mode == 2 ? "AI" : "Player 2");

    players[0] = ui->create_player(name1, '\0', PlayerType::HUMAN);
    players[1] = ui->create_player(name2, '\0',
        mode == 2 ? PlayerType::AI : PlayerType::HUMAN);

    gameManager = new GameManager<char>(board, players, ui);
    gameManager->run();

    delete gameManager;
    delete board;
    delete ui;
    delete players[0];
    delete players[1];

    break;
}


          // Game 5: Misere 
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

          //  Game 6: Diamond 
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
          // Game 7: 4x4 Tic-Tac-Toe 
    case 7: {
     cout << "Starting Game: 4x4 Tic-Tac-Toe..." << endl;
     Game7_Board* board = new Game7_Board();
     Game7_UI* ui = new Game7_UI();

     Player<char>** players = ui->setup_players();
     GameManager<char>* manager = new GameManager<char>(board, players, ui);
     manager->run();

     delete board;
     delete ui;
     delete manager;
     delete[] players;
     break;
 }
        case 8: { // Pyramid Tic-Tac-Toe
    cout << "Starting Game: Pyramid Tic-Tac-Toe..." << endl;

    Pyramid_Board* board = new Pyramid_Board();

    Pyramid_UI* ui = new Pyramid_UI(); 

    Player<char>** players = ui->setup_players();

    GameManager<char>* manager = new GameManager<char>(board, players, ui);

    manager->run();

    delete board;
    delete ui;
    delete manager;
    delete[] players;
    break;
}
              // --- Game 9: Numerical Tic-Tac-Toe 
        case 9: {
            cout << "\n--- Starting Numerical Tic-Tac-Toe ---\n";
            cout << "Player 1: Odd Numbers (1,3,5,7,9)\n";
            cout << "Player 2: Even Numbers (2,4,6,8)\n";
            cout << "Goal: Sum of 15 in any line.\n";

            board = new NumericalBoard();
            players[0] = new Player<char>("P1", '1', PlayerType::HUMAN); 
            players[1] = new Player<char>("P2", '2', PlayerType::HUMAN);
            ui = new Numerical_UI();

            gameManager = new GameManager<char>(board, players, ui);
            gameManager->run();
            break;
        }
            
              // Game 10: Obstacles
        case 10:
        {
            cout << "Starting Game: ObstaclesBoard..." << endl;

            board = new ObstaclesBoard();
            ui = new ObstaclesUI();

            int mode;
            cout << "Choose mode:\n1) Human vs Human\n2) Human vs AI\nEnter choice: ";
            cin >> mode;

            string name1 = "Player X";
            string name2 = "Player O";

            // Player 1 (Human)
            players[0] = ui->create_player(name1, 'X', PlayerType::HUMAN);

            // Player 2 (Human or AI)
            if (mode == 2) {
                players[1] = new AIPlayer_Obstacles('O');  // AI player
            }
            else {
                players[1] = ui->create_player(name2, 'O', PlayerType::HUMAN);
            }

            gameManager = new GameManager<char>(board, players, ui);
            gameManager->run();

            delete gameManager;
            delete board;
            delete ui;
            delete players[0];
            delete players[1];
            break;
        }
        case 11: { // Infinity Tic-Tac-Toe
    cout << "\n--- Starting Infinity Tic-Tac-Toe ---\n";
    cout << "Board: 3x3. Rule: Oldest move is removed after every 3 moves.\n";

    
    board = new Infinity_Board();
    ui = new InfinityUI();
    Player<char>** players_array = ui->setup_players();

    gameManager = new GameManager<char>(board, players_array, ui);
    gameManager->run();
    delete board;
    delete ui;
    delete gameManager;
    delete players_array[0];
    delete players_array[1];
    delete[] players_array;

    break;
}
           // Game 12 : Ultimate_TicTacToe

    case 12: {
        cout << "\n--- Starting Ultimate Tic-Tac-Toe ---\n";
        cout << "Big Board is 9x9 (contains 9 mini-boards).\n";
        cout << "Winning a mini-board marks the big cell.\n";
        cout << "Get 3 big cells in a row to WIN!\n";

        board = new UltimateBoard();
        players[0] = new Player<char>("P1", 'X', PlayerType::HUMAN);
        players[1] = new Player<char>("P2", 'O', PlayerType::HUMAN);

        ui = new XO_UI();
        gameManager = new GameManager<char>(board, players, ui);

        gameManager->run();

        delete gameManager;
        delete board;
        delete players[0];
        delete players[1];
        delete ui;
        break;
    }
        
          //  Game XO 
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

