#include "NumericalPlayer.h"
#include <cstdlib>
#include <ctime>
#include <vector>
#include <algorithm>

NumericalPlayer::NumericalPlayer(string n, int s, PlayerType t)
        : Player<int>(n, s, t) {
    srand(static_cast<unsigned int>(time(nullptr)));
}

Move<int>* NumericalPlayer::get_random_move() {
    vector<vector<int>> matrix = this->boardPtr->get_board_matrix();
    int rows = this->boardPtr->get_rows();
    int cols = this->boardPtr->get_columns();

    // emptycells
    vector<pair<int,int>> emptyCells;
    for (int i = 0; i < rows; ++i)
        for (int j = 0; j < cols; ++j)
            if (matrix[i][j] == 0)
                emptyCells.push_back({i, j});

    if (emptyCells.empty()) return nullptr;

    // random
    auto [x, y] = emptyCells[rand() % emptyCells.size()];

    // odd or even
    int num;
    if (this->symbol % 2 == 1) // odd
        num = 1 + 2 * (rand() % 5); 
    else // even
        num = 2 + 2 * (rand() % 4);  

    return new Move<int>(x, y, num);
}
