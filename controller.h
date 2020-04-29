#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <vector>
#include <string>

namespace chess
{
    class piece;
    class board;
    class controller
    {
    private:
        int turn_to_move{};
        std::vector<std::string> move_history{};
    public:
        //default constructor, starting position.
        controller() {};
        virtual ~controller () {};
        std::vector<std::string> get_move_history();
        void add_move(int initial_position, int final_position);
        void print_move_history();
        int get_turn_to_move();
        void set_turn_to_move(int colour);
        void change_turn_to_move();

        //void make_move(int initial_position, int final_position, board* the_board);

        //to include
        //white king castle
        //black king castle
        //en passant
    };


}


#endif