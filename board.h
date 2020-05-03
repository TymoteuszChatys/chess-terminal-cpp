#ifndef BOARD_H
#define BOARD_H

#include <string>
#include <iostream>
#include <vector>
#include <sstream> 
#include <windows.h>



std::string square_notation_to_human(int square);
int square_notation_to_computer(std::string square);

namespace chess
{
    class controller;
    class piece;
    class board
    {
        friend std::ostream& operator<<(std::ostream& out_stream, const board& the_board);
    private:
        int* board_representation;
        controller* board_controller;
        std::vector<std::shared_ptr<piece>> pieces;
        int size{ 10 * 12 };
    public:

        //default constructor, starting position.
        board();
        board(controller *the_controller);
        board(board *the_board);
        board(int* board_diagram);

        virtual ~board() { delete[] board_representation; };
        size_t get_size() const;
        int* get_board_representation();
        std::vector<std::shared_ptr<piece>> get_pieces();
        int get_piece_at_position(int index);
        void remove_piece(int position);
        void move_piece(int final_position, std::shared_ptr<piece> the_piece);
        void populate_out_of_range();
        void position(std::string FEN);
        void print_pieces();
        void print_valid_moves(int position);
        bool is_king_in_check(int colour);

        std::string whose_turn_to_move();
        
    };


}


#endif