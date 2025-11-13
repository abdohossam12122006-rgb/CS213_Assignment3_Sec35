#include <iostream>
#include <cstdlib>
#include <ctime>
#include "BoardGame_Classes.h"
#include "NumericalBoard.h"
#include "NumericalUI.h"
#include "NumericalPlayer.h"

int main() {
    srand(static_cast<unsigned int>(time(0)));

    // Create UI
    NumericalUI* game_ui = new NumericalUI();

    // Create board
    Board<char>* board = new NumericalBoard();

    // Create players with their numbers
    std::vector<int> player1_nums = { 1, 3, 5, 7, 9 };  // odd numbers
    std::vector<int> player2_nums = { 2, 4, 6, 8 };     // even numbers

    Player<char>* players[2];
    players[0] = new NumericalPlayer('1', "Player 1", player1_nums);
    players[1] = new NumericalPlayer('2', "Player 2", player2_nums);

    // Set board for players
    players[0]->set_board_ptr(board);
    players[1]->set_board_ptr(board);

    // Create game manager
    GameManager<char> game(board, players, game_ui);

    // Run game
    game.run();

    // Cleanup
    delete board;
    delete players[0];
    delete players[1];
    delete game_ui;

    return 0;
}