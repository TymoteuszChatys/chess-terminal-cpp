#include "board.h"
#include "pieces.h"
#include "controller.h"
#include<cmath>


using namespace chess;



int controller::get_turn_to_move()
{
    std::cout << turn_to_move << std::endl;
    return turn_to_move;
}



void controller::change_turn_to_move() 
{
	turn_to_move = get_turn_to_move() * -1;
}

void controller::set_turn_to_move(int colour)
{
    if (colour == 1) {
        turn_to_move = 1;
    }else if (colour == -1) {
        turn_to_move = -1;
    }
    std::cout << turn_to_move << std::endl;
}

std::vector<std::string> controller::get_move_history()
{
    return move_history;
}


void controller::add_move(int initial_position, int final_position)
{
    move_history.push_back(square_notation(initial_position) + square_notation(final_position)); 
}

void controller::print_move_history()
{
    std::cout << "Moves made so far: " << std::endl;
    double move_number{1}; // counter 
    if (fmod(move_number, 1.0) == 0) {
        std::cout << move_number << ".";
    }
    for (auto iterator = move_history.begin(); iterator != move_history.end(); iterator++) {
        std::cout << *iterator << " ";
        move_number = move_number + 0.5;
    }
}

/*void controller::make_move(int initial_position, int final_position, board *the_board)
{
    bool legal_move{false};
    for (auto iterator = the_board->get_pieces().begin(); iterator != the_board->get_pieces().end(); iterator++) {
        if ((*iterator)->get_position<int>() == initial_position) {
            
            for (const auto& allowed_move : (*iterator)->valid_moves(the_board)) {
                if (allowed_move == final_position) {
                    legal_move = true;
                }
            }
        }
    }

    if (legal_move == true) {
        for (auto iterator = the_board->get_pieces().begin(); iterator != the_board->get_pieces().end(); iterator++) {
            if ((*iterator)->get_position<int>() == final_position) {
                //the_board->remove_piece(final_position);
            }
        }

    }

}*/