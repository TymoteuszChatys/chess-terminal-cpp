#include "board.h"
#include "pieces.h"
#include "controller.h"
#include "checkmate_controller.h"

using namespace chess;

//Colours
HANDLE checkmate_console = GetStdHandle(STD_OUTPUT_HANDLE);
#define GREEN_F		(SetConsoleTextAttribute(checkmate_console, FOREGROUND_GREEN))  //sets the console colour to green
#define RED_F		(SetConsoleTextAttribute(checkmate_console, FOREGROUND_RED))  //sets the console colour to red
#define BLUE_F		(SetConsoleTextAttribute(checkmate_console, FOREGROUND_BLUE)) //sets the console colour to blue
#define WHITE_F		(SetConsoleTextAttribute(checkmate_console, FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN)) //defines the colour white

std::vector<std::string> split_string(const std::string& string, int split_length);


//for the checkmate controller we must redefine the each_turn function to only allow the "best moves" that will lead to the checkmate
bool checkmate_controller::each_turn(board* the_board, std::string information, std::string correct_move)
{
    std::cout << *the_board << std::endl;
    std::cout << information << std::endl;
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
            std::cout << std::endl << "enter any key to continue" << std::endl;
            getline(std::cin, key);
        }else {
            std::cout << player_to_move << "'s turn to move. Enter your move: ";
            std::vector<int> moves = enter_move(the_board);
            if (moves.at(1) == -101) {
                the_board->print_valid_moves(moves.at(0), true);
            }else if (moves.at(1) == -102) {
                std::cout << "No valid move was entered. Enter square e.g e2 for information about available placements." << std::endl;
            }else if (moves.at(1) == -110) {
                std::cout << "Error: You can only move " << the_board->whose_turn_to_move() << " pieces" << std::endl;
            }else if (moves.at(1) == -500) {
                end_game = true;
            }else {
                std::vector<int> checkmate_move;
                std::vector<std::string> move_vector = split_string(correct_move, 2);
                checkmate_move.push_back(square_notation_to_computer(move_vector.at(0)));
                checkmate_move.push_back(square_notation_to_computer(move_vector.at(1)));
                if (moves.at(0) == checkmate_move.at(0) && moves.at(1) == checkmate_move.at(1)) {
                    this->make_move(moves.at(0), moves.at(1), the_board);
                    valid_move = true;
                }else {
                    std::cout << "Incorrect move " << std::endl;
                }
                
            }

        }
    }
    std::system("cls");
    return end_game;
}
