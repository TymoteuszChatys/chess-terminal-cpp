#include "board.h"
#include "pieces.h"

chess::board global_board;

int main()
{
    std::cout << global_board << std::endl;;
    //global_board.print_valid_moves(22);
    global_board.print_valid_moves(64);
    //global_board.print_valid_moves(96);
    //global_board.print_valid_moves(32);
    //global_board.print_valid_moves(37);
    //global_board.print_valid_moves(46);
    //global_board.print_valid_moves(66);
    //global_board.print_valid_moves(55);
    //global_board.print_valid_moves(35);
    //global_board.print_valid_moves(82);
    std::cout << std::endl << std::endl;
    return 0;
}