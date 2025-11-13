#include <iostream>
#include <string>
#include <vector>
#include <limits>
#include "BoardGame_Classes.h"
#include "XO_Classes.h"
using namespace std;
void display_menu() {
    cout << "========================================" << endl;
    cout << "   Welcome to the CS213 Game Center!  " << endl;
    cout << "========================================" << endl;
    cout << "  Individual Games (Set 1):" << endl;
    cout << "    1. SUS" << endl;
    cout << "    2. Four-in-a-row" << endl;
    cout << "  Individual Games (Set 2):" << endl;
    cout << "    3. 5x5 Tic Tac Toe" << endl;
    cout << "    4. Word Tic-tac-toe" << endl;
    cout << "  Individual Games (Set 3):" << endl;
    cout << "    5. Misere Tic Tac Toe" << endl;
    cout << "    6. Diamond Tic-Tac-Toe" << endl;
    cout << "  Individual Games (Set 4):" << endl;
    cout << "    7. 4x4 Tic-Tac-Toe" << endl;
    cout << "    8. Pyramid Tic-Tac-Toe" << endl;
    cout << "--- Group Games ---" << endl;
    cout << "    9. Numerical Tic-Tac-Toe" << endl;
    cout << "    10. Obstacles Tic-Tac-Toe" << endl;
    cout << "    11. Infinity Tic-Tac-Toe" << endl;
    cout << "--- Bonus Group Games ---" << endl;
    cout << "    12. Ultimate Tic Tac Toe" << endl;
    cout << "    13. Memory Tic-Tac-Toe" << endl;
    cout << "----------------------------------------" << endl;
    cout << "    14. (Example) X-O Game" << endl;
    cout << "    0. Exit" << endl;
    cout << "========================================" << endl;
    cout << "Enter your choice (0-14): ";
}

void clear_screen() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

void pause_screen() {
    cout << "\nPress Enter to return to the main menu..." << endl;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cin.get();
}


void run_game_selection(int choice) {
    clear_screen(); 

    switch (choice) {
        // --- Individual Games ---
    case 1: // SUS
        cout << "Starting Game: SUS..." << endl;
       
        break;
    case 2: // Four-in-a-row
        cout << "Starting Game: Four-in-a-row..." << endl;
        
        break;
    case 3: // 5x5 Tic Tac Toe
        cout << "Starting Game: 5x5 Tic Tac Toe..." << endl;
       
        break;
    case 4: // Word Tic-tac-toe
        cout << "Starting Game: Word Tic-tac-toe..." << endl;
        
        break;
    case 5: // Misere Tic Tac Toe
        cout << "Starting Game: Misere Tic Tac Toe..." << endl;
        break;
    case 6: // Diamond Tic-Tac-Toe
        cout << "Starting Game: Diamond Tic-Tac-Toe..." << endl;
        break;
    case 7: // 4x4 Tic-Tac-Toe
        cout << "Starting Game: 4x4 Tic-Tac-Toe..." << endl;
        break;
    case 8: // Pyramid Tic-Tac-Toe
        cout << "Starting Game: Pyramid Tic-Tac-Toe..." << endl;
        break;

        // --- Group Games ---
    case 9: // Numerical Tic-Tac-Toe
        cout << "Starting Game: Numerical Tic-Tac-Toe..." << endl;
        break;
    case 10: // Obstacles Tic-Tac-Toe
        cout << "Starting Game: Obstacles Tic-Tac-Toe..." << endl;
        break;
    case 11: // Infinity Tic-Tac-Toe
        cout << "Starting Game: Infinity Tic-Tac-Toe..." << endl;
        break;

        // --- Bonus Group Games ---
    case 12: // Ultimate Tic Tac Toe
        cout << "Starting Game: Ultimate Tic Tac Toe..." << endl;
        break;
    case 13: // Memory Tic-Tac-Toe
        cout << "Starting Game: Memory Tic-Tac-Toe..." << endl;
        break;

        // --- Example Game ---
    case 14: // X-O Game
        cout << "Starting Game: (Example) X-O Game..." << endl;
        break;

    default:
        cout << "Invalid choice. Please select a number from the menu." << endl;
        break;
    }
}


int main() {
    int choice;

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
        pause_screen();
    }

    return 0; 
}

