#pragma once

// Std lib imports
#include <string>

// local imports
#include "tictactoe-model.hpp"

class ViewController {

    std::string players[2];
    size_t tiles_to_win;

    bool input_valid_pos(int& x, int& y) const {
        std::string inp {};
        getline(std::cin, inp);
        int space_countr {0};
        std::string nums[2];
        for (auto && c : inp) {
            if (!std::isdigit(c)) {
                if (c == ' ') {
                    if(++space_countr > 1)
                        return false;
                } else 
                    return false;
            } else 
                nums[space_countr] += c;
        }
        x = std::stoi(nums[0]);
        y = std::stoi(nums[1]);
        return true;
    }

    void print_win_line(const WinLine& win_line) const {
        std::shared_ptr<WinPoint> itr {win_line.head};
        std::cout << '-';
        while (itr) {
            std::cout << WinPoint::str_point(itr->point) << "-";
            itr = itr->next;
        }
        std::cout << '\n';
    }
    
    void get_player_names() {
        std::cout << "Enter Player 1's name: \n";
        getline(std::cin, players[1]);
        std::cout << "Enter Player 2's name: \n";
        getline(std::cin, players[0]);
        for (int i = 1; i >= 0; i--)
            if (players[i] == "")
                players[i] = "Player " + std::to_string(i);
    }

    void get_tiles_to_win() {
        std::cout << "Enter tiles to win: \n";
        std::cin >> tiles_to_win;
        std::cin.ignore();
    }

public:

    ViewController() {
        get_tiles_to_win();
        get_player_names();
    }
        
    void play() const {
        TicTacToe game(tiles_to_win);
        int x {}, y {};
        while(!game.has_winner()) {
            const auto turn {game.get_turn()};
            std::cout << players[turn] << "'s turn: ";

            while(!input_valid_pos(x, y)) 
                std::cout << "invalid position. Try again: ";
            
            if (game.move({x, y}))
                std::cout << "Move made: " << WinPoint::str_point({x, y}) << '\n';
            else 
                std::cout << "Invalid move! Tile occupied.\n";
        }
        const winner_type winner {game.get_winner()};
        std::cout << "Winner: " << players[winner] << '\n';
        print_win_line(game.get_win_line());
    }
};

