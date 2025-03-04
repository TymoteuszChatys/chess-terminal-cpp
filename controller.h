#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <vector>
#include <string>
#include <chrono>
#include <fstream>


namespace chess
{
    class piece;
    class board;
    class controller
    {
    private:
        int turn_to_move{};
        int turn_number{};
        int ply{};
        std::vector<std::string> move_history{};
    public:
        //default constructor, starting position.
        controller() {};
        virtual ~controller () {};
        std::vector<std::string> get_move_history();
        void add_move(int initial_position, int final_position);
        void print_move_history();
        int get_turn_to_move();
        int get_turn_number();
        int get_ply();
        
        void set_turn_number(int the_turn_number);
        void set_ply(int the_ply);
        void add_turn_number();
        void add_ply();
        void set_turn_to_move(int colour);
        
        void change_turn_to_move();
        std::vector<int> enter_move(board* the_board);
        void make_move(int initial_position, int final_position, board* the_board);

        bool each_turn(board* the_board);
        void save_game(board* the_board);
    };


}


#endif