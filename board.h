#ifndef BOARD_H
#define BOARD_H

#include <string>
#include <iostream>
#include <vector>
#include <sstream> 
#include "pieces.h"

namespace chess
{
    class board 
    {
        friend class piece;
        friend std::ostream &operator<<(std::ostream &out_stream, const board &the_board);
    protected:
        int* board_representation{nullptr};
        int size{10*12};
    public:
        //default constructor, starting position.
        board();
        virtual ~board() {delete[] board_representation;};    
        size_t get_size() const;
        void populate_out_of_range();
        void position(std::string FEN);
    };


std::ostream &operator<<(std::ostream &out_stream, const board &the_board)
{
    if(the_board.get_size() > 0){
        for (size_t mirror_index{the_board.get_size()/10}; mirror_index > 0; mirror_index--){
            for (size_t index{(mirror_index-1)*10}; index < mirror_index*10; index++) {
                if ((index+1) % 10 == 0) {
                    out_stream << the_board.board_representation[index] << std::endl;
                }else{
                    out_stream << the_board.board_representation[index] << ";";
                }
            }
        }
            
    }else{
        out_stream << "board is empty" << std::endl;
    }
    return out_stream;
}

}

#endif