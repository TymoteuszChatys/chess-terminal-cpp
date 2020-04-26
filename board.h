#ifndef BOARD_H
#define BOARD_H

#include <string>
#include <iostream>
#include <vector>
#include <sstream> 

namespace chess
{
    class board
    {
        friend class piece;
        friend std::ostream& operator<<(std::ostream& out_stream, const board& the_board);
    private:
        int* board_representation{ nullptr };
        std::vector<std::unique_ptr<piece>> pieces;
        int size{ 10 * 12 };
    public:

        //default constructor, starting position.
        board();
        virtual ~board() { delete[] board_representation; };
        size_t get_size() const;
        void populate_out_of_range();
        void position(std::string FEN);
        void print_pieces();
    };

}

#endif