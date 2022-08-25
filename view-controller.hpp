#pragma once

// Std lib imports
#include <cassert>
#include <regex>
#include <string>
#include <algorithm> 
#include <iterator>

// local imports
#include "tictactoe-model.hpp"

class ViewController {

    static std::pair<int, int> get_pos() {
        std::string re {"(-?\\d+) (-?\\d+)"};
        std::string prompt {"Enter move:"};
        const auto nums {validated_response(prompt, re, "<int> <int>")};

        int x = std::stoi(nums[1]);
        int y = std::stoi(nums[2]);
        
        return {x, y};
    }

    static void print_win_line(const WinLine& win_line) {
        std::shared_ptr<WinPoint> itr {win_line.head};
        std::cout << '-';
        while (itr) {
            std::cout << WinPoint::str_point(itr->point) << "-";
            itr = itr->next;
        }
        std::cout << '\n';
    }
    
    static const std::vector<std::string> get_player_names() {
        std::vector<std::string> player_names {};
        const std::string name_re {"(^[a-z ,.'-]+$)"};

        for (int i = 0; i < 2; i++) {
            const auto name_matches {
                validated_response(
                    "Enter player " + std::to_string(i + 1) + "'s name",
                    name_re, "[alphabetical string(s)]\nExample: Tim Pool"
                )
            };
            player_names.emplace_back(name_matches[1]);
        }

        assert(player_names[0] != player_names[1] 
            && "different playas please");

        return player_names;
    }

    static std::vector<std::string> validated_response(
        const std::string& prompt, const std::string& regex, 
        const std::string& usage
    ) {
        const std::regex re(regex);
        std::smatch matches {};

        std::cout << prompt << '\n';
        std::string input {};
        std::getline(std::cin, input);

        while (!std::regex_match(input, matches, re)) {
            std::cout << "Bad input.\n";
            std::cout << usage << '\n';
            std::cout << prompt << '\n';
            std::getline(std::cin, input);
        }

        // return matches;
        // ! for some reason returning matches fills the 
        // ! returned object with garbage values

        std::vector<std::string> ret {};
        std::copy(matches.cbegin(), matches.cend(), std::back_inserter(ret));

        return ret;
    }

    static int get_tiles_to_win() {
        const std::string number_regex {"(\\d+)"};
        const std::string usage = {
            "<number of tiles to win>"
        };
        const std::string prompt = "Enter the number of tiles";
        auto strs {validated_response(prompt, number_regex, usage)};

        return std::stoi(strs[1]);
    }

public:
        
    static void play() {
        const int tiles_to_win {get_tiles_to_win()};
        const auto player_names {get_player_names()};

        TicTacToe game(player_names[0], player_names[1], tiles_to_win);

        while(!game.has_winner()) {
            std::cout << '\n';
            const auto player_to_play {game.get_turn()};
            std::cout << player_to_play << "'s turn:\n";

            auto [x, y] = get_pos();
            
            if (game.move({x, y}))
                std::cout << "Move made: " << WinPoint::str_point({x, y}) << '\n';
            else 
                std::cout << "Invalid move! Tile occupied.\n";
        }
        const std::string winner {game.get_winner()};
        std::cout << "Winner: " << winner << '\n';
        print_win_line(game.get_win_line());
    }
};

