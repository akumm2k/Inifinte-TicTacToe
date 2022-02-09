#pragma once
#include <iostream>
#include <vector>
#include <unordered_map>
#include "win-line.hpp"

struct hash_pair {
    template <class T1, class T2>
    size_t operator()(const std::pair<T1, T2>& p) const {
        auto hash1 = std::hash<T1>{}(p.first);
        auto hash2 = std::hash<T2>{}(p.second);
        return hash1 ^ hash2;
    }
};

class TicTacToe {
	using board_type = std::unordered_map<point_type, char, hash_pair>;

	uint8_t player = 1;
	const size_t tiles_to_win;
	board_type board;

	char winner;
	const std::vector<std::pair<char, char>> dirs 
	{{0, 1}, // right 
	{-1, 1}, // up and right
	{-1, 0}, // up 
	{1, 1}}; // down and right 

	WinLine line;

	bool board_contains(const point_type& point) const {
		return board.find(point) != board.end();
	}

	bool check_win(const point_type& point) { 
		size_t countr;
		for (auto &&dir : dirs) {
			const char dx = dir.first, dy = dir.second;
			countr = 0;
			int x = point.first - tiles_to_win * dx, 
				y = point.second  - tiles_to_win * dy; 

			WinLine new_line(tiles_to_win);
			size_t loop = 2 * tiles_to_win - 1; 
			// check for ${tiles_to_win} consecutive plays in 
			// a line of (2 * tiles_to_win + 1) tiles
			
			while (loop > 0) { 
				if (board_contains({x, y}) && board[{x, y}] == player) {
					new_line.add({x, y});
					countr++;
				}
				else countr = 0;
				if (countr == tiles_to_win) {
					line = (new_line); 
					return true;
				}
				x +=  dx; y +=  dy;
				loop--;
			}
		}
		return false;
	}	

	public:

		TicTacToe(const size_t tiles_to_win = 5) : 
			tiles_to_win(tiles_to_win), winner(-1) { }
		
		uint8_t get_turn() const noexcept {
			return player;
		}

		char get_winner() const noexcept {
			return winner;
		}

		const WinLine& get_win_line() const {
			return line;
		}

		bool has_winner() const noexcept {
			return winner != -1;
		}

		bool move(const point_type& point) {
			if (!board_contains(point)) {
				board[point] = player;
				if (check_win(point)) 
					winner = player;
				player = 1 - player;
				return true;
			}
			return false;
		}
};