
#include "SUS_UI.h"
#include <cctype>

/**
 * @class SUS_Board
 * @brief Represents the 3×3 board for the SUS game.
 */

SUS_Board::SUS_Board() : Board(3, 3) {
    /**
     * @brief Initialize all board cells with the blank symbol.
     */
    for (auto& row : board)
        for (auto& c : row)
            c = blank_symbol;
}

/**
 * @brief Updates the board with a player's move.
 *
 * @param move Pointer to the player's Move object.
 * @return true if the move is valid and applied, false otherwise.
 */
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

/**
 * @brief Counts all complete "S-U-S" sequences on the board.
 *
 * @param symbol Symbol of the player (unused but kept for compatibility).
 * @return Number of detected sequences.
 */
int SUS_Board::count_sequences(char symbol) {
    int count = 0;

    /// @brief Allowed movement directions: vertical, horizontal, diagonal, anti-diagonal.
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

/**
 * @brief Checks if the game is a draw.
 *
 * @param player Pointer to the player (unused).
 * @return true if all 9 moves have been played.
 */
bool SUS_Board::is_draw(Player<char>* player) {
    return (n_moves == 9);
}

/**
 * @brief Checks if the game is over.
 *
 * @param player Pointer to the player (unused).
 * @return true if board is full.
 */
bool SUS_Board::game_is_over(Player<char>* player) {
    return n_moves == 9;
}

/**
 * @brief Static helper function: counts "S-U-S" sequences in any matrix.
 *
 * @param mat 2D character matrix.
 * @param symbol Player symbol (unused).
 * @return Total number of sequences found.
 */
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

/**
 * @class SUS_AI
 * @brief AI logic for evaluating game board states.
 */

/**
 * @brief Evaluates the board and returns a score for the AI.
 *
 * @param mat Board matrix.
 * @param me Symbol used by the AI player.
 * @return Evaluation score where higher is better for the AI.
 */
int SUS_AI::evaluate(const std::vector<std::vector<char>>& mat, char me) {
    int myScore = SUS_Board::count_sequences_in_matrix(mat, me);
    char opponent = (me == 'S') ? 'U' : 'S';
    int oppScore = SUS_Board::count_sequences_in_matrix(mat, opponent);

    return myScore * 2 - oppScore;
}

/**
 * @class SUS_UI
 * @brief Handling user interface for player creation and setup.
 */

/**
 * @brief Sets up the two players (names and type: Human/AI).
 *
 * @return Array of two Player pointers.
 */
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

