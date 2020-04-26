#include "board.h"
#include "pieces.h"

int main()
{
    chess::board main_board;
    int size = main_board.get_size();
    std::cout << main_board << std::endl;
    main_board.print_pieces();
    return 0;
}