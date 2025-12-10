
#include "SUS_UI.h"
#include <cctype>

SUS_Board::SUS_Board() : Board(3, 3) {
    for (auto& row : board)
        for (auto& c : row)
            c = blank_symbol;
}

bool SUS_Board::update_board(Move<char>* move) {
    int x = move->get_x();
    int y = move->get_y();
    char mark = move->get_symbol();

    if (x < 0 || x >= rows || y < 0 || y >= columns)
        return false;

    if (board[x][y] != blank_symbol)
        return false;

    board[x][y] = toupper(mark);
    n_moves++;
    return true;
}

int SUS_Board::count_sequences(char symbol) {
    int count = 0;
    int dir[4][2] = { {1,0}, {0,1}, {1,1}, {1,-1} };

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < columns; j++) {
            for (auto& d : dir) {
                int x1 = i, y1 = j;
                int x2 = i + d[0], y2 = j + d[1];
                int x3 = i + 2 * d[0], y3 = j + 2 * d[1];

                if (x3 < 0 || x3 >= rows || y3 < 0 || y3 >= columns) continue;

                if (board[x1][y1] == 'S' && board[x2][y2] == 'U' && board[x3][y3] == 'S')
                    count++;
            }
        }
    }
    return count;
}

bool SUS_Board::is_draw(Player<char>* player) {
    return (n_moves == 9);
}

bool SUS_Board::game_is_over(Player<char>* player) {
    return n_moves == 9;
}

int SUS_Board::count_sequences_in_matrix(const std::vector<std::vector<char>>& mat, char symbol) {
    int rows = (int)mat.size();
    if (rows == 0) return 0;
    int cols = (int)mat[0].size();
    int count = 0;
    int dir[4][2] = { {1,0}, {0,1}, {1,1}, {1,-1} };

    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            for (auto& d : dir) {
                int x1 = i, y1 = j;
                int x2 = i + d[0], y2 = j + d[1];
                int x3 = i + 2 * d[0], y3 = j + 2 * d[1];

                if (x3 < 0 || x3 >= rows || y3 < 0 || y3 >= cols) continue;

                if (mat[x1][y1] == 'S' && mat[x2][y2] == 'U' && mat[x3][y3] == 'S')
                    count++;
            }
        }
    }
    return count;
}

int SUS_AI::evaluate(const std::vector<std::vector<char>>& mat, char me) {
    int myScore = SUS_Board::count_sequences_in_matrix(mat, me);
    char opponent = (me == 'S') ? 'U' : 'S';
    int oppScore = SUS_Board::count_sequences_in_matrix(mat, opponent);
    return myScore * 2 - oppScore;
}

// setup_players implementation
Player<char>** SUS_UI::setup_players() {
    Player<char>** players = new Player<char>*[2];
    string name, type;

    for (int i = 0; i < 2; i++) {
        cout << "Enter Player " << (i == 0 ? 'S' : 'U') << " name: ";
        cin >> name;

        cout << "Choose type (Human/AI): ";
        cin >> type;

        if (type == "AI" || type == "ai")
            players[i] = new SUS_AI(name, i == 0 ? 'S' : 'U');
        else
            players[i] = new Player<char>(name, i == 0 ? 'S' : 'U', PlayerType::HUMAN);
    }

    return players;
}
