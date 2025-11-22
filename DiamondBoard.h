#ifndef DIAMOND_BOARD_H
#define DIAMOND_BOARD_H

#include "BoardGame_Classes.h"
#include <vector>
#include <cmath>
#include <algorithm>

using namespace std;

class DiamondBoard : public Board<char> {
public:
    // Constructor: ÈäÍÏÏ ÇáÈæÑÏ 5x5
    DiamondBoard() : Board<char>(5, 5) {
        this->n_moves = 0;
        // ÊåíÆÉ ÇáÈæÑÏ
        for (int i = 0; i < this->rows; i++) {
            for (int j = 0; j < this->columns; j++) {
                this->board[i][j] = 0;
            }
        }
    }

    // ÏÇáÉ ãÓÇÚÏÉ ÚÔÇä äÚÑİ ÇáãßÇä Ïå Ìæå ÇáãÇÓÉ æáÇ áÃ
    // ÇáãÚÇÏáÉ: ÇáãÓÇİÉ ãä ÇáãÑßÒ (2,2) áÇÒã Êßæä <= 2
    bool is_inside_diamond(int x, int y) {
        return (abs(x - 2) + abs(y - 2)) <= 2;
    }

    bool update_board(Move<char>* move) override {
        int x = move->get_x();
        int y = move->get_y();
        char symbol = move->get_symbol();

        // 1. İÍÕ ÇáÍÏæÏ
        if (x < 0 || x >= this->rows || y < 0 || y >= this->columns) {
            return false;
        }

        // 2. İÍÕ ÔÑØ ÇáãÇÓÉ (åá ÇáãßÇä Ïå ÕÇáÍ¿)
        if (!is_inside_diamond(x, y)) {
            return false;
        }

        // 3. İÍÕ åá ÇáãßÇä İÇÖí
        if (this->board[x][y] != 0) {
            return false;
        }

        this->board[x][y] = symbol;
        this->n_moves++;
        return true;
    }

    // ÏÇáÉ ãÓÇÚÏÉ ÈÊİÍÕ ÓØÑ ßÇãá æÊÔæİ åá İíå ÎØæØ ÈÇáØæá ÇáãØáæÈ æáÇ áÃ
    void check_line_segment(int start_x, int start_y, int dx, int dy, char symbol, bool& has3, bool& has4) {
        int count = 0;
        int x = start_x;
        int y = start_y;

        while (x >= 0 && x < this->rows && y >= 0 && y < this->columns) {
            // ÈäÚÏ ÈÓ áæ ÇáãßÇä Ìæå ÇáãÇÓÉ æİíå ÑãÒ ÇááÇÚÈ
            if (is_inside_diamond(x, y) && this->board[x][y] == symbol) {
                count++;
            }
            else {
                // ÇáÓáÓáÉ ÇŞØÚÊ¡ äÔæİ æÕáäÇ áßÇã
                if (count == 3) has3 = true;
                if (count == 4) has4 = true; // ÈäİÊÑÖ Åä ÇáÜ 4 áÇÒã Êßæä 4 ÈÇáÖÈØ Ãæ ÃßÊÑ
                if (count >= 5) has4 = true;
                count = 0;
            }
            x += dx;
            y += dy;
        }
        // İÍÕ ÂÎÑ ÌÒÁ İí ÇáÓØÑ
        if (count == 3) has3 = true;
        if (count >= 4) has4 = true;
    }

    // ÏÇáÉ ÇáİæÒ ÇáãÚŞÏÉ
    bool is_win(Player<char>* player) override {
        char symbol = player->get_symbol();

        // ãÕİæİÇÊ áÊÎÒíä åá áŞíäÇ ÎØ 3 Ãæ ÎØ 4 İí ßá ÇÊÌÇå
        // ÇáÇÊÌÇåÇÊ: 0:ÃİŞí¡ 1:ÑÃÓí¡ 2:ŞØÑ ÑÆíÓí¡ 3:ŞØÑ İÑÚí
        bool dir3[4] = { false, false, false, false };
        bool dir4[4] = { false, false, false, false };

        // 1. İÍÕ ßá ÇáÕİæİ (ÃİŞí)
        for (int i = 0; i < 5; i++) {
            check_line_segment(i, 0, 0, 1, symbol, dir3[0], dir4[0]);
        }

        // 2. İÍÕ ßá ÇáÃÚãÏÉ (ÑÃÓí)
        for (int j = 0; j < 5; j++) {
            check_line_segment(0, j, 1, 0, symbol, dir3[1], dir4[1]);
        }

        // 3. İÍÕ ÇáÃŞØÇÑ ÇáÑÆíÓíÉ (Mian Diagonals)
        // ÇáÃŞØÇÑ Çááí ããßä ÊÔíá 3 ÎÇäÇÊ Ãæ ÃßÊÑ ÈÊÈÏÃ ãä ÇáÕİæİ æÇáÃÚãÏÉ Ïí:
        check_line_segment(2, 0, 1, 1, symbol, dir3[2], dir4[2]);
        check_line_segment(1, 0, 1, 1, symbol, dir3[2], dir4[2]);
        check_line_segment(0, 0, 1, 1, symbol, dir3[2], dir4[2]); // ÇáŞØÑ ÇáÑÆíÓí
        check_line_segment(0, 1, 1, 1, symbol, dir3[2], dir4[2]);
        check_line_segment(0, 2, 1, 1, symbol, dir3[2], dir4[2]);

        // 4. İÍÕ ÇáÃŞØÇÑ ÇáÚßÓíÉ (Anti Diagonals)
        check_line_segment(2, 4, 1, -1, symbol, dir3[3], dir4[3]);
        check_line_segment(1, 4, 1, -1, symbol, dir3[3], dir4[3]);
        check_line_segment(0, 4, 1, -1, symbol, dir3[3], dir4[3]); // ÇáŞØÑ ÇáÚßÓí ÇáÑÆíÓí
        check_line_segment(0, 3, 1, -1, symbol, dir3[3], dir4[3]);
        check_line_segment(0, 2, 1, -1, symbol, dir3[3], dir4[3]);

        // ÔÑØ ÇáİæÒ: æÌæÏ ÎØ 3 İí ÇÊÌÇå¡ æÎØ 4 İí ÇÊÌÇå *ãÎÊáİ*
        for (int i = 0; i < 4; i++) {     // i åæ ÇÊÌÇå ÇáÎØ ÇáÜ 3
            for (int j = 0; j < 4; j++) { // j åæ ÇÊÌÇå ÇáÎØ ÇáÜ 4
                if (i != j && dir3[i] && dir4[j]) {
                    return true;
                }
            }
        }

        return false;
    }

    // ÏÇáÉ ÇáÎÓÇÑÉ (ãİíÔ ÎÓÇÑÉ ãÈÇÔÑÉ Òí Misere)
    bool is_lose(Player<char>* player) override {
        return false;
    }
    bool is_draw(Player<char>* player) override {
        return (this->n_moves == 13 && !is_win(player));
    }

    bool game_is_over(Player<char>* player) override {
        return is_win(player) || is_draw(player);
    }
};

#endif // DIAMOND_BOARD_H

       