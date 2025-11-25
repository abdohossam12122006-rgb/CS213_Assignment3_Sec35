#pragma once
#ifndef TIC_TAC_TOE_H
#define TIC_TAC_TOE_H
#include "BoardGame_Classes.h" 
using namespace std;
class MemoryXO_Board : public Board<char> {
private:
	char blank_symbol = '.';
	// hidden_board stores actual marks; base::board remains filled with blank_symbol so UI shows empties
    vector<vector<char>> actual_board; public:
	MemoryXO_Board();
	bool update_board(Move<char>* move) override;
	bool is_win(Player<char>* player) override;
	bool is_lose(Player<char>* player) override;
	bool is_draw(Player<char>* player) override;
	bool game_is_over(Player<char>* player) override;


	// helper to access hidden matrix if needed
	vector<vector<char>> get_hidden_board() const { return actual_board; }
};


class MemoryXO_UI : public UI<char> {
public:
	MemoryXO_UI();
	~MemoryXO_UI() {};
	Player<char>* create_player(string& name, char symbol, PlayerType type) override;
	virtual Move<char>* get_move(Player<char>* player) override;
	// override display_board_matrix to always show blanks (we'll reuse base implementation by passing base board)
};

#endif
