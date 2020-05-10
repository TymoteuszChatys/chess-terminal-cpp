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
        int en_passant_square;
        bool white_castle_king;
        bool white_castle_queen;
        bool black_castle_king;
        bool black_castle_queen;
    public:

        //default constructor, starting position.
        board();
        board(std::string fen, controller* the_controller);
        board(controller *the_controller);
        board(const board* a_board, controller* the_controller);
        board(const board* a_board, controller* the_controller, int initial_position, int final_position);


        virtual ~board() {delete[] board_representation;}
        void remove_piece(int position);
        void move_piece(int final_position, std::shared_ptr<piece> the_piece);
        void populate_out_of_range();
        void position(std::string FEN);
        void print_valid_moves(int position, bool check_or_not);
        bool is_king_in_check(int colour);

        void set_white_castle_king(bool true_or_false);
        void set_white_castle_queen(bool true_or_false);
        void set_black_castle_king(bool true_or_false);
        void set_black_castle_queen(bool true_or_false);
        void set_en_passant_square(int square);

        size_t get_size() const;
        bool is_there_any_valid_moves(std::string player_to_move);
        int* get_board_representation();
        int get_piece_at_position(int index);
        std::vector<std::shared_ptr<piece>> get_pieces();
        std::string get_fen() const;
        bool get_white_castle_king();
        bool get_white_castle_queen();
        bool get_black_castle_king();
        bool get_black_castle_queen();
        int get_en_passant_square();


        std::string whose_turn_to_move();        
    };


}


#endif