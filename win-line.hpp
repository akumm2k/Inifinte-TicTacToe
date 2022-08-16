#pragma once

// Std lib imports
#include <iostream>
#include <string>
#include <memory>

using point_type = std::pair<int, int>;

struct WinPoint {
	point_type point;
	std::shared_ptr<WinPoint> next;
	
	WinPoint() : next(nullptr) { }
	WinPoint(point_type p) : point(p), next(nullptr) { }
	WinPoint(point_type p, std::shared_ptr<WinPoint> next) 
		: point(p), next(next) { }
	
	static std::string str_point(const point_type& p) {
		return "(" + std::to_string(p.first) + ", " 
			+ std::to_string(p.second) + ")";
	}
};

struct WinLine {
	size_t count, tiles_to_win;
	std::shared_ptr<WinPoint> head, tail;

	WinLine() : head(nullptr), tail(nullptr) { }

	const WinLine& operator=(WinLine&& new_line) { 
		head = new_line.head;
		tail = new_line.tail;
		count = new_line.count;
		tiles_to_win = new_line.tiles_to_win;
		new_line.head = nullptr;
		new_line.tail = nullptr;
		return *this;
	}

	const WinLine& operator=(WinLine& new_line) { 
		head = new_line.head;
		tail = new_line.tail;
		count = new_line.count;
		tiles_to_win = new_line.tiles_to_win;
		new_line.head = nullptr;
		new_line.tail = nullptr;
		return *this;
	}

	WinLine(size_t tiles_to_win) 
		: count(0), tiles_to_win(tiles_to_win), head(nullptr), tail(nullptr) { }

	void add(const point_type& p) {
		auto new_point {std::make_shared<WinPoint>(p)}; 

		if (count == 0) {
			head = new_point;
			tail = new_point;
			count++;
		} else {
			tail->next = new_point;
			tail = tail->next;
			count++;
			if (count == tiles_to_win + 1) {
				head = head->next;
				count--;
			}
		}
	}

	void print_line() const {
		std::shared_ptr<WinPoint> itr {head};
		while(itr) {
			std::cout << WinPoint::str_point(itr->point) << " -> ";
			itr = itr->next;
		}
		std::cout << '\n';
	}
};
