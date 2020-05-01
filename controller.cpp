#include "board.h"
#include "pieces.h"
#include "controller.h"
#include<cmath>


using namespace chess;

std::vector<std::string> split_string(const std::string& string, int split_length)
{
    int number_substring = string.length() / split_length;
    std::vector<std::string> return_vector;

    for (auto i = 0; i < number_substring; i++){
        return_vector.push_back(string.substr(i * split_length, split_length));
    }

    // If there are leftover characters, create a shorter item at the end.
    if (string.length() % split_length != 0){
        return_vector.push_back(string.substr(split_length * number_substring));
    }
    return return_vector;
}

void controller::each_turn(board* the_board) 
{
    std::cout << *the_board << std::endl;
    this->print_move_history();
    std::cout << std::endl;
    bool valid_move{ false };
    while (valid_move == false) {
        std::cout << the_board->whose_turn_to_move() << "'s turn to move. Enter your move: ";
        std::vector<int> moves = enter_move();
        if (moves.at(1) == -101) {
            the_board->print_valid_moves(moves.at(0));
        }else {
            this->make_move(moves.at(0), moves.at(1), the_board);
            valid_move = true;
            std::system("cls");
        }
    } 
}

int controller::get_turn_to_move()
{
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
}

std::vector<std::string> controller::get_move_history()
{
    return move_history;
}

int controller::get_turn_number() 
{
    return turn_number;
}

int controller::get_ply() 
{
    return ply;
}

void controller::set_turn_number(int the_turn_number) 
{
    turn_number = the_turn_number;
}

void controller::set_ply(int the_ply) 
{
    ply = the_ply;
}

void controller::add_turn_number() 
{
    turn_number++;
}

void controller::add_ply() 
{
    ply++;
}

void controller::add_move(int initial_position, int final_position)
{
    move_history.push_back(square_notation_to_human(initial_position) + square_notation_to_human(final_position)); 
}

void controller::print_move_history()
{
    std::cout << "move history: " << std::endl;
    double move_number{1}; // counter 
    for (auto iterator = move_history.begin(); iterator != move_history.end(); iterator++) {
        if (fmod(move_number, 1.0) == 0) {
            std::cout << move_number << ".";
        }
        std::cout << *iterator << " ";
        move_number = move_number + 0.5;
    }
}

std::vector<int> controller::enter_move() 
{
    std::vector<int> initial_and_final_moves;
    std::string moves;
    getline(std::cin, moves);
    if (moves.length() == 4) {
        std::vector<std::string> move_vector = split_string(moves, 2);
        initial_and_final_moves.push_back(square_notation_to_computer(move_vector.at(0)));
        initial_and_final_moves.push_back(square_notation_to_computer(move_vector.at(1)));
    }
    else if (moves.length() == 2) {
        initial_and_final_moves.push_back(square_notation_to_computer(moves));
        initial_and_final_moves.push_back(-101);
    }
    else {
        initial_and_final_moves.push_back(-1);
        initial_and_final_moves.push_back(-1);
    }


    return initial_and_final_moves;
}



void controller::make_move(int initial_position, int final_position, board *the_board)
{
    std::shared_ptr<piece> the_piece;
    bool legal_move{false};
    std::vector<std::shared_ptr<piece>> the_pieces = the_board->get_pieces();
    for (auto iterator = the_pieces.begin(); iterator != the_pieces.end(); iterator++) {

        if ((*iterator)->get_position<int>() == initial_position) {
            
            for (const auto& allowed_move : (*iterator)->valid_moves(the_board)) {
                if (allowed_move == final_position) {
                    legal_move = true;
                    the_piece = (*iterator);
                    break;
                }
            }
        }
    }

    if (legal_move == true) {
        for (auto iterator = the_pieces.begin(); iterator != the_pieces.end(); iterator++) {
            if ((*iterator)->get_position<int>() == final_position) {
                the_board->remove_piece(final_position);
            }
        }
        the_board->move_piece(final_position, the_piece);
        add_move(initial_position, final_position);
        change_turn_to_move();
        add_ply();
        if (get_ply() % 2) {
            add_turn_number();
        }
    }else {
        std::cout << "Invalid move " << std::endl;
    }

}