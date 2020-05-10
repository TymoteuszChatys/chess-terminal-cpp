#include "board.h"
#include "pieces.h"
#include "controller.h"
#include "tutorial_controller.h"

using namespace chess;

//Colours
HANDLE tutorial_console = GetStdHandle(STD_OUTPUT_HANDLE);
#define GREEN_F		(SetConsoleTextAttribute(tutorial_console, FOREGROUND_GREEN))  //sets the console colour to green
#define RED_F		(SetConsoleTextAttribute(tutorial_console, FOREGROUND_RED))  //sets the console colour to red
#define BLUE_F		(SetConsoleTextAttribute(tutorial_console, FOREGROUND_BLUE)) //sets the console colour to blue
#define WHITE_F		(SetConsoleTextAttribute(tutorial_console, FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN)) //defines the colour white


//For the tutorial, we must remove some of the features of the main controller.
//We do not want to check for check as in the tutorial we just want to be moving pieces without constrictions
//Functions are redefined to only look for the available moves of each piece without taking into account checking the king.

bool tutorial_controller::each_turn(board* the_board,std::string information)
{
    std::cout << *the_board << std::endl;
    bool valid_move{ false };
    std::cout << information << std::endl;
    bool end_game{ false };
    
    while (valid_move == false && end_game == false) {
        std::cout << "Enter your move: ";
        std::vector<int> moves = enter_move(the_board);
        if (moves.at(1) == -101) {
            the_board->print_valid_moves(moves.at(0),false);
        }else if (moves.at(1) == -102) {
            std::cout << "No valid move was entered. Enter square e.g e2 for information about available placements." << std::endl;
        }else if (moves.at(1) == -500) {
            end_game = true;
        }else {
            this->make_move(moves.at(0), moves.at(1), the_board);
            valid_move = true;
        }
    }

    return end_game;
}


void tutorial_controller::make_move(int initial_position, int final_position, board* the_board)
{
    std::shared_ptr<piece> the_piece;
    bool legal_move{ false };
    std::vector<std::shared_ptr<piece>> the_pieces = the_board->get_pieces();
    for (auto iterator = the_pieces.begin(); iterator != the_pieces.end(); iterator++) {

        if ((*iterator)->get_position<int>() == initial_position) {
            //tutorial controller must not check for check as many positions will not have a 
            //king in the tutorial.
            //This is the main difference between the tutorial controller and parent class definition.
            for (const auto& allowed_move : (*iterator)->valid_moves_before_check(the_board)) {
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


        //no castling rights after king has moved
        if (the_piece->tag() == 6) {
            the_board->set_white_castle_king(false);
            the_board->set_white_castle_queen(false);
        }
        else if (the_piece->tag() == -6) {
            the_board->set_black_castle_king(false);
            the_board->set_black_castle_queen(false);
        }

        //no castling rights if rook has moved from initial position
        if (abs(the_piece->tag()) == 4) {
            if (initial_position == 21) {
                the_board->set_white_castle_queen(false);
            }
            else if (initial_position == 28) {
                the_board->set_white_castle_king(false);
            }
            else if (initial_position == 91) {
                the_board->set_black_castle_queen(false);
            }
            else if (initial_position == 98) {
                the_board->set_black_castle_king(false);
            }
        }

        //castling only, moving the rook adjacent to the king.
        if (abs(the_piece->tag()) == 6 && abs(final_position - initial_position) == 2) {
            std::shared_ptr<piece> the_rook;
            for (auto iterator = the_pieces.begin(); iterator != the_pieces.end(); iterator++) {
                if ((*iterator)->get_position<int>() == final_position + 1) {
                    the_rook = (*iterator);
                    the_board->move_piece(final_position - 1, the_rook);
                    break;
                }
                else if ((*iterator)->get_position<int>() == final_position - 2) {
                    the_rook = (*iterator);
                    the_board->move_piece(final_position + 1, the_rook);
                    break;
                }
            }
        }


        //en passant occured during this move, remove pawn being taken
        if (abs(the_piece->tag()) == 1 && final_position == the_board->get_en_passant_square()) {
            int remove_piece;
            if (the_piece->get_colour<int>() == 1) {
                remove_piece = -10;
            }
            else if (the_piece->get_colour<int>() == -1) {
                remove_piece = 10;
            }
            the_board->remove_piece(final_position + remove_piece);
        }

        //en passant for future move
        if (abs(the_piece->tag()) == 1 && abs(final_position - initial_position) == 20) {
            if (the_piece->get_colour<int>() == 1) {
                the_board->set_en_passant_square(final_position - 10);
            }
            else if (the_piece->get_colour<int>() == -1) {
                the_board->set_en_passant_square(final_position + 10);
            }
        }
        else {
            the_board->set_en_passant_square(0);
        }

        add_move(initial_position, final_position);
    }
    else {
        std::cout << "Invalid move " << std::endl;
    }

}


void tutorial_controller::print_valid_moves(int position, board* the_board)
{
    int position_in_piece_vector{};
    std::vector<piece>::iterator iterator;
    std::vector<int> this_piece_valid_moves;
    std::vector<std::shared_ptr<piece>> pieces = the_board->get_pieces();
    for (auto iterator = pieces.begin(); iterator != pieces.end(); iterator++) {
        int currentPos = (*iterator)->get_position<int>();
        if (currentPos == position) {
            this_piece_valid_moves = (*iterator)->valid_moves_before_check(the_board);
            break;
        }
        position_in_piece_vector++;
    }

    if (this_piece_valid_moves.size() != 0) {
        std::cout << "Possible moves for " << pieces.at(position_in_piece_vector)->name() << " at " << pieces.at(position_in_piece_vector)->get_position<std::string>() << ":  ";
        for (auto iterator = this_piece_valid_moves.begin(); iterator != this_piece_valid_moves.end(); iterator++) {
            GREEN_F;
            std::cout << square_notation_to_human(*iterator) << " ";
            WHITE_F;
        }
    }
    else {
        std::cout << "Error: no moves from " << square_notation_to_human(position);
    }
    std::cout << std::endl;
}

