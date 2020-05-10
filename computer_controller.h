#ifndef COMPUTER_CONTROLLER_H
#define COMPUTER_CONTROLLER_H

#include<string>
#include<vector>

namespace chess



{

    class piece;
    class board;
    class controller;
    class computer_controller : public controller
    {
    public:
        computer_controller() {};
        ~computer_controller() {};
        
        
        int evaluation(board* the_board, int* player_to_move);
        auto valid_moves_list(board* the_board, int player_to_move);
        std::tuple<int, std::string> minimax_search(board* the_board, size_t depth, int alpha, int beta, bool maximizing_player);
        bool each_turn(board* the_board);
        std::vector<int> enter_computer_move(board* the_board, std::string move);
    };
}

std::vector<std::string> split_string(const std::string& string, int split_length);
#endif