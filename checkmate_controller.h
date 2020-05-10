#ifndef CHECKMATE_CONTROLLER_H
#define CHECKMATE_CONTROLLER_H

#include<string>
#include<vector>

namespace chess
{
    class piece;
    class board;
    class controller;
    class checkmate_controller : public controller
    {
    public:
        checkmate_controller() {};
        ~checkmate_controller() {};
        bool each_turn(board* the_board, std::string information, std::string correct_move);
    };
}



#endif