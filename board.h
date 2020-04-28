#ifndef BOARD_H
#define BOARD_H

#include <string>
#include <iostream>
#include <vector>
#include <sstream> 

std::string square_notation(int square);


namespace chess
{
    class piece;
    class board
    {
        friend std::ostream& operator<<(std::ostream& out_stream, const board& the_board);
    private:
        static int* board_representation;
        std::vector<std::unique_ptr<piece>> pieces;
        int size{ 10 * 12 };
    public:

        //default constructor, starting position.
        board();
        virtual ~board() { delete[] board_representation; };
        size_t get_size() const;
        int get_piece_at_position(int index);
        void remove_piece(int position);
        void populate_out_of_range();
        void position(std::string FEN);
        void print_pieces();
        void print_valid_moves(int position);
    };


}


#endif