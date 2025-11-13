#include "NumericalUI.h"
#include <iostream>
#include <string>
#include <vector>
#include <stdexcept>

Move<char>* NumericalUI::get_move(Player<char>* player) {
    NumericalPlayer* num_player = dynamic_cast<NumericalPlayer*>(player);

    if (!num_player) {
        throw std::runtime_error("Error: Player object is not of type NumericalPlayer");
    }

    int chosen_num = -1;
    int r = -1, c = -1;

    while (true) {
        std::cout << player->get_name() << ". Your available numbers are: { ";
        const auto& numbers = num_player->get_available_numbers();
        for (size_t i = 0; i < numbers.size(); ++i) {
            std::cout << numbers[i] << (i == numbers.size() - 1 ? " " : ", ");
        }
        std::cout << "}\n";
        std::cout << "Please choose a number: ";
        std::cin >> chosen_num;

        if (num_player->is_number_available(chosen_num)) {
            break;
        }
        else {
            std::cout << "Invalid number! Please pick from your available list.\n";
            std::cin.clear();
            std::cin.ignore(10000, '\n');
        }
    }

    std::cout << "Now, enter the row (0-2) and col (0-2) to place it: ";

    Board<char>* b_ptr = player->get_board_ptr();

    while (true) {
        std::cin >> r >> c;

        std::vector<std::vector<char>> matrix = b_ptr->get_board_matrix();

        if (r >= 0 && r <= 2 && c >= 0 && c <= 2 && matrix[r][c] == 0) {
            break;
        }
        else {
            std::cout << "Invalid move! Cell is not empty or out of bounds. Try again: ";
            std::cin.clear();
            std::cin.ignore(10000, '\n');
        }
    }

    num_player->remove_number(chosen_num);

    char num_as_char = chosen_num + '0';
    return new Move<char>(r, c, num_as_char);
}

Player<char>* NumericalUI::create_player(string& name, char symbol, PlayerType type) {
    return new Player<char>(name, symbol, type);
}
