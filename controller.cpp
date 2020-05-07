#include "board.h"
#include "pieces.h"
#include "controller.h"
#include<cmath>
#include<windows.h>

//Colours
HANDLE controllerConsole = GetStdHandle(STD_OUTPUT_HANDLE);
#define GREEN_F		(SetConsoleTextAttribute(controllerConsole, FOREGROUND_GREEN))  //sets the console colour to green
#define RED_F		(SetConsoleTextAttribute(controllerConsole, FOREGROUND_RED))  //sets the console colour to red
#define BLUE_F		(SetConsoleTextAttribute(controllerConsole, FOREGROUND_BLUE)) //sets the console colour to blue
#define WHITE_F		(SetConsoleTextAttribute(controllerConsole, FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN)) //defines the colour white


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

bool controller::each_turn(board* the_board) 
{
    std::cout << *the_board << std::endl;
    this->print_move_history();
    std::cout << std::endl;
    bool valid_move{ false };
    std::string player_to_move = the_board->whose_turn_to_move();
    bool end_game{ false };
    while (valid_move == false && end_game == false) {
        if (the_board->is_king_in_check(get_turn_to_move()) == true && the_board->is_there_any_valid_moves(player_to_move) == false) {
            GREEN_F; std::cout << player_to_move << " has been checkmated. Game over." << std::endl; WHITE_F;
            end_game = true;
        }else if (the_board->is_king_in_check(get_turn_to_move()) == true) {
            GREEN_F; std::cout << player_to_move << "'s king is in check" << std::endl; WHITE_F;
        }else if (the_board->is_there_any_valid_moves(player_to_move) == false) {
            GREEN_F; std::cout << "Game has been drawn by stalemate " << std::endl; WHITE_F;
            end_game = true;
        }
        if (end_game == true) {
            std::string key;
            std::cout << std::endl << "enter any key to go back to the main menu" << std::endl;
            std::cin >> key;
        }else {
            std::cout << player_to_move << "'s turn to move. Enter your move: ";
            std::vector<int> moves = enter_move(the_board);
            if (moves.at(1) == -101) {
                the_board->print_valid_moves(moves.at(0));
            }
            else if (moves.at(1) == -102) {
                std::cout << "No valid move was entered. Enter square e.g e2 for information about available placements." << std::endl;
            }
            else if (moves.at(1) == -110) {
                std::cout << "Error: You can only move " << the_board->whose_turn_to_move() << " pieces" << std::endl;
            }
            else {
                this->make_move(moves.at(0), moves.at(1), the_board);
                valid_move = true;
            }

        }    
    } 
    std::system("cls");
    return end_game;
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
    double move_number{ 1 }; // counter 
    for (auto iterator = move_history.begin(); iterator != move_history.end(); iterator++) {
        if (fmod(move_number, 1.0) == 0) {
            std::cout << move_number << ".";
        }
        std::cout << *iterator << " ";
        move_number = move_number + 0.5;
    }
}

void controller::save_game(board* the_board) 
{
    double move_number{1};
    auto end = std::chrono::system_clock::now();
    //std::time_t end_time = std::chrono::system_clock::to_time_t(end);

    bool started = false;
    std::ofstream out_file;
    while (true) {
        if (!started) {
            int file_no = 1;
            bool success = false;
            while (success && file_no < INT_MAX) {
                std::ifstream if_stream("games/game" + std::to_string(file_no) + ".txt", std::ios::out);// attempt read file to check if it exists
                success = if_stream.good();
                if_stream.close();
                file_no++;//increase by one to get a new file name
            }
            out_file.open("games/game" + std::to_string(file_no) + ".txt", std::ios::app);
            started = true;
        }
    }
    
    //out_file << "Date: " << std::ctime(&end_time) << std::endl;
    
    for (auto iterator = move_history.begin(); iterator != move_history.end(); iterator++) {
        if (fmod(move_number, 1.0) == 0) {
            out_file << std::endl << move_number << ".";
        }
        out_file << *iterator << " ";
        move_number = move_number + 0.5;
    }

    out_file.close(); //moved out of loop so that it is not closed
    }

std::vector<int> controller::enter_move(board* the_board)
{
    std::vector<int> initial_and_final_moves;
    std::string moves;
    getline(std::cin, moves);
    if (moves.length() == 4) {
        std::vector<std::string> move_vector = split_string(moves, 2);
        if ((the_board->get_piece_at_position(square_notation_to_computer(move_vector.at(0)))) * get_turn_to_move() > 0) {
            initial_and_final_moves.push_back(square_notation_to_computer(move_vector.at(0)));
            initial_and_final_moves.push_back(square_notation_to_computer(move_vector.at(1)));
        }else {
            initial_and_final_moves.push_back(-1);
            initial_and_final_moves.push_back(-110);
        }
    }else if (moves.length() == 2) {
        initial_and_final_moves.push_back(square_notation_to_computer(moves));
        initial_and_final_moves.push_back(-101);
    }else {
        initial_and_final_moves.push_back(-1);
        initial_and_final_moves.push_back(-102);
    }


    return initial_and_final_moves;
}


//function to make the move on the board occur
void controller::make_move(int initial_position, int final_position, board* the_board)
{
    std::shared_ptr<piece> the_piece;
    bool legal_move{ false };
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
        

        //no castling rights after king has moved
        if (the_piece->tag() == 6) {
            the_board->set_white_castle_king(false);
            the_board->set_white_castle_queen(false);
        }else if (the_piece->tag() == -6) {
            the_board->set_black_castle_king(false);
            the_board->set_black_castle_queen(false);
        }

        //no castling rights if rook has moved from initial position
        if (abs(the_piece->tag()) == 4) {
            if (initial_position == 21) {
                the_board->set_white_castle_queen(false);
            }else if (initial_position == 28) {
                the_board->set_white_castle_king(false);
            }else if (initial_position == 91) {
                the_board->set_black_castle_queen(false);
            }else if (initial_position == 98) {
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
                }else if ((*iterator)->get_position<int>() == final_position - 2) {
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
            }else if (the_piece->get_colour<int>() == -1) {
                the_board->set_en_passant_square(final_position + 10);
            }
        }else {
            the_board->set_en_passant_square(0);
        }
       
        add_move(initial_position, final_position);
        change_turn_to_move();
        add_ply();
        if (get_ply() % 2) {
            add_turn_number();
        }
    }else{
        std::cout << "Invalid move " << std::endl;
    }

}


