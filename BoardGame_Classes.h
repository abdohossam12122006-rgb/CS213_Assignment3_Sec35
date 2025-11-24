#ifndef _BOARDGAME_CLASSES_H
#define _BOARDGAME_CLASSES_H

#include <string>
#include <vector>
#include <iostream>
#include <iomanip>
using namespace std;

template <typename T> class Player;
template <typename T> class Move;

enum class PlayerType {
    HUMAN,
    COMPUTER,
    AI,
    RANDOM
};

template <typename T>
class Board {
protected:
    int rows;
    int columns;
    vector<vector<T>> board;
    int n_moves = 0;

public:
    Board(int rows, int columns)
        : rows(rows), columns(columns), board(rows, vector<T>(columns)) {
    }

    virtual ~Board() {}

    virtual bool update_board(Move<T>* move) = 0;
    virtual bool is_win(Player<T>*) = 0;
    virtual bool is_lose(Player<T>*) = 0;
    virtual bool is_draw(Player<T>*) = 0;
    virtual bool game_is_over(Player<T>*) = 0;

    vector<vector<T>> get_board_matrix() const {
        return board;
    }

    int get_rows() const { return rows; }
    int get_columns() const { return columns; }

    T get_cell(int x, int y) {
        return board[x][y];
    }
};

template <typename T>
class Move {
    int x;
    int y;
    T symbol;

public:
    Move(int x, int y, T symbol) : x(x), y(y), symbol(symbol) {}

    int get_x() const { return x; }
    int get_y() const { return y; }
    T get_symbol() const { return symbol; }
};

template <typename T>
class Player {
protected:
    string name;
    PlayerType type;
    T symbol;
    Board<T>* boardPtr;

public:
    Player(string n, T s, PlayerType t)
        : name(n), symbol(s), type(t), boardPtr(nullptr) {
    }

    virtual ~Player() {}

    string get_name() const { return name; }
    PlayerType get_type() const { return type; }
    T get_symbol() const { return symbol; }
    Board<T>* get_board_ptr() const { return boardPtr; }
    void set_board_ptr(Board<T>* b) { boardPtr = b; }
};

template <typename T>
class UI {
protected:
    int cell_width;

    virtual string get_player_name(string player_label) {
        string name;
        cout << "Enter " << player_label << " name: ";
        getline(cin >> ws, name);
        return name;
    }

    virtual PlayerType get_player_type_choice(string player_label, const vector<string>& options) {
        cout << "Choose " << player_label << " type:\n";
        for (size_t i = 0; i < options.size(); ++i)
            cout << i + 1 << ". " << options[i] << "\n";
        int choice;
        cin >> choice;
        return (choice == 2) ? PlayerType::COMPUTER : PlayerType::HUMAN;
    }

public:
    UI(int cell_display_width = 3) : cell_width(cell_display_width) {}

    UI(string message, int cell_display_width)
        : cell_width(cell_display_width) {
        cout << message << endl;
    }

    virtual ~UI() {}

    virtual void display_message(string message) {
        cout << message << "\n";
    }

    virtual Move<T>* get_move(Player<T>*) = 0;

    virtual Player<T>** setup_players();

    virtual Player<T>* create_player(string& name, T symbol, PlayerType type) {
        return new Player<T>(name, symbol, type);
    }

    virtual void display_board_matrix(const vector<vector<T>>& matrix) const {
        if (matrix.empty() || matrix[0].empty()) return;

        int rows = matrix.size();
        int cols = matrix[0].size();

        cout << "\n    ";
        for (int j = 0; j < cols; ++j)
            cout << setw(cell_width + 1) << j;
        cout << "\n   " << string((cell_width + 2) * cols, '-') << "\n";

        for (int i = 0; i < rows; ++i) {
            cout << setw(2) << i << " |";
            for (int j = 0; j < cols; ++j)
                cout << setw(cell_width) << matrix[i][j] << " |";
            cout << "\n   " << string((cell_width + 2) * cols, '-') << "\n";
        }
        cout << endl;
    }
};

template <typename T>
class GameManager {
    Board<T>* boardPtr;
    Player<T>* players[2];
    UI<T>* ui;

public:
    GameManager(Board<T>* b, Player<T>* p[2], UI<T>* u)
        : boardPtr(b), ui(u) {
        players[0] = p[0];
        players[1] = p[1];
        players[0]->set_board_ptr(b);
        players[1]->set_board_ptr(b);
    }

    void run() {
        ui->display_board_matrix(boardPtr->get_board_matrix());
        Player<T>* currentPlayer = players[0];

        while (true) {
            for (int i : {0, 1}) {
                currentPlayer = players[i];
                Move<T>* move = ui->get_move(currentPlayer);

                while (!boardPtr->update_board(move))
                    move = ui->get_move(currentPlayer);

                ui->display_board_matrix(boardPtr->get_board_matrix());

                if (boardPtr->is_win(currentPlayer)) {
                    ui->display_message(currentPlayer->get_name() + " wins!");
                    return;
                }
                if (boardPtr->is_lose(currentPlayer)) {
                    ui->display_message(players[1 - i]->get_name() + " wins!");
                    return;
                }
                if (boardPtr->is_draw(currentPlayer)) {
                    ui->display_message("Draw!");
                    return;
                }
            }
        }
    }
};

template <typename T>
Player<T>** UI<T>::setup_players() {
    Player<T>** players = new Player<T>*[2];
    vector<string> type_options = { "Human", "Computer" };

    string nameX = get_player_name("Player X");
    PlayerType typeX = get_player_type_choice("Player X", type_options);
    players[0] = create_player(nameX, static_cast<T>('X'), typeX);

    string nameO = get_player_name("Player O");
    PlayerType typeO = get_player_type_choice("Player O", type_options);
    players[1] = create_player(nameO, static_cast<T>('O'), typeO);

    return players;
}

#endif