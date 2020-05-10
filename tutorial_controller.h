#ifndef TUTORIAL_CONTROLLER_H
#define TUTORIAL_CONTROLLER_H

#include<string>
#include<vector>

namespace chess
{
    class piece;
    class board;
    class controller;
    class tutorial_controller : public controller
    {
    private:
    public:
        tutorial_controller() {};
        ~tutorial_controller() {};
        void make_move(int initial_position, int final_position, board* the_board);
        bool each_turn(board* the_board, std::string information);
        void print_valid_moves(int position, board* the_board);
    };
}



#endif