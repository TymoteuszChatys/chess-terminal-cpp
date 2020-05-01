#include "board.h"
#include "pieces.h"
#include "controller.h"

class board;
class controller;


int main()
{
    chess::controller global_controller;
    chess::board global_board(&global_controller);
    
    for (auto i = 0; i < 50; i++) {
        global_controller.each_turn(&global_board);
    }
    return 0;
}