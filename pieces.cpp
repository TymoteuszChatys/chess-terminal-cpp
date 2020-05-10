#include<iostream>
#include<string>
#include<array>
#include "board.h"
#include "pieces.h"
#include "controller.h"
#include "tutorial_controller.h"

using namespace chess;

struct compare
{
    int key;
    compare(int const& i) : key(i) {}

    bool operator()(int const& i)
    {
        return (i == key);
    }
};


piece::piece(int the_colour, size_t the_position)
{
    colour = the_colour;
    position = the_position;
}

std::string king::name()
{
    return "king";
}

std::string queen::name()
{
    return "queen";
}

std::string rook::name()
{
    return "rook";
}

std::string bishop::name()
{
    return "bishop";
}

std::string knight::name()
{
    return "knight";
}

std::string pawn::name()
{
    return "pawn";
}

int king::tag()
{
    return 6 * get_colour<int>();
}

int queen::tag()
{
    return 5 * get_colour<int>();
}

int bishop::tag()
{
    return 3 * get_colour<int>();
}
int knight::tag()
{
    return 2 * get_colour<int>();
}
int rook::tag()
{
    return 4 * get_colour<int>();
}
int pawn::tag()
{
    return 1 * get_colour<int>();
}

int king::points()
{
    return 100 * get_colour<int>();
}

int queen::points()
{
    return 9 * get_colour<int>();
}

int rook::points()
{
    return 5 * get_colour<int>();
}

int bishop::points()
{
    return 3 * get_colour<int>();
}

int knight::points()
{
    return 3 * get_colour<int>();
}

int pawn::points()
{
    return 1 * get_colour<int>();
}

void piece::print_piece_data() 
{// Print out pieces data
    std::cout << get_colour<std::string>() << " " << name() << " at " << get_position<std::string>() << std::endl;
}


template<typename colour_type> colour_type piece::get_colour()
{
    if constexpr (std::is_same<colour_type, int>::value) {
        return colour;
    }else if constexpr (std::is_same<colour_type, std::string>::value) {
        if (colour == -1) {
            return "black";
        }else {
            return "white";
        }
    }
}

template<typename colour_type> colour_type piece::get_position()
{
    if constexpr (std::is_same<colour_type, int>::value) {
        return position;
    }else if constexpr (std::is_same<colour_type, std::string>::value) {
        std::string notation = square_notation_to_human(position);
        return notation;
    }

}

void piece::set_position(int new_position)
{
    position = new_position;
}


///////////////
//Valid Moves//
///////////////

std::vector<int> check_moves_validity_for_self_check(int position, std::vector<int> moves, board& the_board)
{
    int move_number{};
    std::vector<int> allowed_moves = moves;
    for (auto move = allowed_moves.begin(); move != allowed_moves.end();){
        controller temporary_controller;
        board temporary_board(&the_board, &temporary_controller);
        std::shared_ptr<piece> the_piece;
        std::vector<std::shared_ptr<piece>> temporary_board_pieces = temporary_board.get_pieces();
        for (auto iterator = temporary_board_pieces.begin(); iterator != temporary_board_pieces.end(); iterator++) {
            if ((*iterator)->get_position<int>() == position) {
                the_piece = (*iterator);
                break;
            }
        }
        for (auto iterator = temporary_board_pieces.begin(); iterator != temporary_board_pieces.end(); iterator++) {
            if ((*iterator)->get_position<int>() == moves.at(move_number)) {
                temporary_board.remove_piece((*iterator)->get_position<int>());
            }
        }
        temporary_board.move_piece(moves.at(move_number), the_piece);
        bool in_check = temporary_board.is_king_in_check(the_piece->get_colour<int>());
        if (in_check == true) {
            move = allowed_moves.erase(move);
        }else {
            ++move;
        }
        move_number++;
    }
    return allowed_moves;
}



//Diagonal function check for Bishops and Queens.
std::vector<int> diagonal_check(chess::piece* the_piece, chess::board* the_board)
{
    int current_position = the_piece->get_position<int>();

    std::array<int, 4> diagonal_directions = { 11,9,-11,-9 };
    std::vector<int> allowed_pieces_to_take = { 0,1,2,3,4,5,6 };
    std::vector<int> possible_moves;

    for (const auto& allowed_move : diagonal_directions) {
        int changing_allowed_move{allowed_move};
        bool good_move_check{ true };
        while (good_move_check == true) {
            //lambda function to look for valid diagonal moves
            if (std::any_of(allowed_pieces_to_take.begin(), allowed_pieces_to_take.end(), [&](int piece)
                {
                    if (the_board->get_piece_at_position(current_position + changing_allowed_move) == piece * -1 * the_piece->get_colour<int>()) {
                        return true;
                    }else {
                        good_move_check = false;
                        return false;
                    }
                }) == true) {
                possible_moves.push_back(current_position + changing_allowed_move);
            }
            //Add allowed move again to look for the next diagonal square
            changing_allowed_move = changing_allowed_move + allowed_move;
        }
    }
    
    return possible_moves;
}

//Horizontal and vertical check for Rooks and Queens
std::vector<int> horizontal_and_vertical_check(chess::piece* the_piece, chess::board* the_board)
{
    int current_position = the_piece->get_position<int>();

    std::array<int, 4> diagonal_directions = { 10,1,-10,-1 };
    std::vector<int> allowed_pieces_to_take = { 0,1,2,3,4,5,6 };
    std::vector<int> possible_moves;

    for (const auto& allowed_move : diagonal_directions) {
        int changing_allowed_move{ allowed_move };
        bool good_move_check{ true };
        while (good_move_check == true) {
            //lambda function to look for valid diagonal moves
            if (std::any_of(allowed_pieces_to_take.begin(), allowed_pieces_to_take.end(), [&](int piece)
                {
                    if (the_board->get_piece_at_position(current_position + changing_allowed_move) == piece * -1 * the_piece->get_colour<int>()) {
                        return true;
                    }
                    else {
                        good_move_check = false;
                        return false;
                    }
                }) == true) {
                possible_moves.push_back(current_position + changing_allowed_move);
            }
            //Add allowed move again to look for the next diagonal square
            changing_allowed_move = changing_allowed_move + allowed_move;
        }
    }
    return possible_moves;
}



std::vector<int> king::valid_moves(chess::board* the_board)
{
    std::vector<int> possible_moves = valid_moves_before_check(the_board);
    std::vector<int> moves = check_moves_validity_for_self_check(this->get_position<int>(), possible_moves, *the_board);
    return moves;
}

std::vector<int> king::valid_moves_before_check(chess::board* the_board)
{
    int current_position = get_position<int>();
    //http://www.chesscorner.com/tutorial/basic/king/king.htm
    //A king can move one square in any direction (horizontally, vertically, or diagonally) 
    //unless the square is already occupied by a friendly piece or the move would place the king in check
    std::array<int, 8> king_moves = { 9,10,11,1,-9,-10,-11,-1 };
    std::vector<int> allowed_pieces_to_take = { 0,1,2,3,4,5,6 };
    std::vector<int> possible_moves;

    for (const auto& allowed_move : king_moves) {
        //lambda function to look for valid knight moves
        if (std::any_of(allowed_pieces_to_take.begin(), allowed_pieces_to_take.end(), [&](int piece)
            {
                if (the_board->get_piece_at_position(current_position + allowed_move) == piece * -1 * this->get_colour<int>()) {
                    return true;
                }
                else {
                    return false;
                }
            }
        ) == true) {
            possible_moves.push_back(current_position + allowed_move);
        }

    }

    //castling needs to be handled independently due to its complexity
    if ((this->get_colour<int>() == 1 && the_board->get_white_castle_king() == true) || (this->get_colour<int>() == -1 && the_board->get_black_castle_king() == true)) {
        int key = 1 + current_position;
        if (std::any_of(possible_moves.begin(), possible_moves.end(), compare(key))) {
            if (the_board->get_piece_at_position(key+1) == 0) {
                possible_moves.push_back(key + 1);
            }
        }       
    }
    if ((this->get_colour<int>() == 1 && the_board->get_white_castle_queen() == true) || (this->get_colour<int>() == -1 && the_board->get_black_castle_queen() == true)) {
        int key = -1 + current_position;
        if (std::any_of(possible_moves.begin(), possible_moves.end(), compare(key))) {
            if (the_board->get_piece_at_position(key-1) == 0 || the_board->get_piece_at_position(key - 2) == 0) {
                possible_moves.push_back(key - 1);
            }
        }
    }
        
    return possible_moves;
}


std::vector<int> queen::valid_moves(chess::board* the_board)
{
    std::vector<int> possible_moves = valid_moves_before_check(the_board);
    std::vector<int> moves = check_moves_validity_for_self_check(this->get_position<int>(), possible_moves, *the_board);
    return moves;
}

std::vector<int> queen::valid_moves_before_check(chess::board* the_board)
{
    //http://www.chesscorner.com/tutorial/basic/queen/queen.htm
    //The queen can be moved any number of unoccupied squares in a straight line vertically, horizontally, or diagonally, 
    //thus combining the moves of the rook and bishop. 
    std::vector<int> possible_moves;
    std::vector<int> diagonal_moves = diagonal_check(this, the_board);
    std::vector<int> horizontal_and_vertical_moves = horizontal_and_vertical_check(this, the_board);

    possible_moves.insert(possible_moves.end(), diagonal_moves.begin(), diagonal_moves.end());
    possible_moves.insert(possible_moves.end(), horizontal_and_vertical_moves.begin(), horizontal_and_vertical_moves.end());

    return possible_moves;
}




std::vector<int> rook::valid_moves(chess::board* the_board)
{
    std::vector<int> possible_moves = valid_moves_before_check(the_board);
    std::vector<int> moves = check_moves_validity_for_self_check(this->get_position<int>(), possible_moves, *the_board);
    return moves;
}

std::vector<int> rook::valid_moves_before_check(chess::board* the_board)
{
    //http://www.chesscorner.com/tutorial/basic/rook/rook.htm
    //The rook moves horizontally or vertically, through any number of unoccupied squares
    std::vector<int> possible_moves = horizontal_and_vertical_check(this, the_board);
    return possible_moves;
}

std::vector<int> bishop::valid_moves(chess::board* the_board)
{
    std::vector<int> possible_moves = valid_moves_before_check(the_board);
    std::vector<int> moves = check_moves_validity_for_self_check(this->get_position<int>(), possible_moves, *the_board);
    return moves;
}

std::vector<int> bishop::valid_moves_before_check(chess::board* the_board)
{
    //http://www.chesscorner.com/tutorial/basic/bishop/bishop.htm
    //The bishop has no restrictions in distance for each move, but is limited to diagonal movement
    std::vector<int> possible_moves = diagonal_check(this, the_board);
    return possible_moves;
}

std::vector<int> knight::valid_moves(chess::board* the_board)
{
    std::vector<int> possible_moves = valid_moves_before_check(the_board);
    std::vector<int> moves = check_moves_validity_for_self_check(this->get_position<int>(), possible_moves, *the_board);
    return moves;
}

std::vector<int> knight::valid_moves_before_check(chess::board* the_board)
{
    int current_position = get_position<int>();
    //http://www.chesscorner.com/tutorial/basic/knight/knight.htm
    //It moves to a square that is two squares away horizontally and one square vertically, or two squares vertically and one square horizontally
    std::array<int,8> knight_moves = {8,12,19,21,-8,-12,-19,-21};
    std::vector<int> allowed_pieces_to_take = {0,1,2,3,4,5,6};
    std::vector<int> possible_moves;

    for (const auto& allowed_move : knight_moves) {
        //lambda function to look for valid knight moves
        if (std::any_of(allowed_pieces_to_take.begin(), allowed_pieces_to_take.end(), [&](int piece) 
            {
                if (the_board->get_piece_at_position(current_position + allowed_move) == piece * -1 * this->get_colour<int>()) {
                    return true;
                }else{
                    return false;
                }      
            }
        ) == true){
            possible_moves.push_back(current_position + allowed_move);
        }
       
    }
    return possible_moves;


}

std::vector<int> pawn::valid_moves(chess::board* the_board)
{
    std::vector<int> possible_moves = valid_moves_before_check(the_board);
    std::vector<int> moves = check_moves_validity_for_self_check(this->get_position<int>(), possible_moves, *the_board);
    return moves;
}

std::vector<int> pawn::valid_moves_before_check(chess::board* the_board)
{
    int current_position = get_position<int>();
    bool one_step_valid{false}; 
    //http://www.chesscorner.com/tutorial/basic/pawn/pawn.htm
    //pawn moves by advancing a single square, but the first time a pawn moves it can move twice. 
    //the pawn does not capture in the same direction that it moves. A pawn captures diagonally forward one square to the left or right
    //so extensive checks have to be done to permit all these possibilities
    std::array<int, 4> pawn_moves = {9,10,11,20}; 
    std::vector<int> allowed_pieces_to_take_diagonal = { 1,2,3,4,5,6 };
    std::vector<int> possible_moves;

    //If black, pieces move backwards in the view of the white player
    if (this->get_colour<int>() == -1) {
        for (auto& allowed_move : pawn_moves) {
            allowed_move = allowed_move * -1;
        }
    }


    for (const auto& allowed_move : pawn_moves) {
        //lambda function to look for valid pawn diagonal moves
        if (abs(allowed_move) == 9 || abs(allowed_move) == 11) {
            if (std::any_of(allowed_pieces_to_take_diagonal.begin(), allowed_pieces_to_take_diagonal.end(), [&](int piece)
                {
                    if (the_board->get_piece_at_position(current_position + allowed_move) == piece * -1 * this->get_colour<int>()) {
                        return true;
                    }else {
                        return false;
                    }
                }
            ) == true) {
                possible_moves.push_back(current_position + allowed_move);
            }
        //one step forward
        }else if (abs(allowed_move) == 10) {
            if (the_board->get_piece_at_position(current_position + allowed_move) == 0) {
                possible_moves.push_back(current_position + allowed_move);
                //white and black two square pawn move validity check, only applicable if on 2nd rank and 7th rank respectively.
                if (this->get_colour<int>() == 1 && current_position >30 && current_position < 39){
                    one_step_valid = true;
                }else if (this->get_colour<int>() == -1 && current_position > 80 && current_position < 89) {
                    one_step_valid = true;
                }
            }
        //two steps forward, checks for empty space
        }else if (abs(allowed_move) == 20 && one_step_valid == true) {
            if (the_board->get_piece_at_position(current_position + allowed_move) == 0) {
                possible_moves.push_back(current_position + allowed_move);
            }
        }

    }

    //special chess move "en passant" must be handled seperately due to its complexity

    int en_passant_square = the_board->get_en_passant_square();
    if (en_passant_square != 0) {
        if (this->get_colour<int>() == -1 && current_position > 50 && current_position < 59) {
            if (this->position == en_passant_square + 11 || this->position == en_passant_square + 9) {
                possible_moves.push_back(en_passant_square);
            }
        }else if (this->get_colour<int>() == 1 && current_position > 60 && current_position < 69) {
            if (this->position == en_passant_square - 11 || this->position == en_passant_square - 9) {
                possible_moves.push_back(en_passant_square);
            }
        }
    }
    return possible_moves;
}


