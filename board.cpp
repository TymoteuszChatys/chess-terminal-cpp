#include "board.h"
#include "pieces.h"
#include "controller.h"

using namespace chess;


int* board::board_representation{ nullptr };

std::string square_notation(int square) {
    //function to associate computer array to human notation. Not all array numbers are associated with a square.
    std::string human_notation{};
    switch (square) {
    case 21: human_notation = "a1"; break; case 31: human_notation = "a2"; break; case 41: human_notation = "a3"; break; case 51: human_notation = "a4"; break;
    case 61: human_notation = "a5"; break; case 71: human_notation = "a6"; break; case 81: human_notation = "a7"; break; case 91: human_notation = "a8"; break;
    case 22: human_notation = "b1"; break; case 32: human_notation = "b2"; break; case 42: human_notation = "b3"; break; case 52: human_notation = "b4"; break;
    case 62: human_notation = "b5"; break; case 72: human_notation = "b6"; break; case 82: human_notation = "b7"; break; case 92: human_notation = "b8"; break;
    case 23: human_notation = "c1"; break; case 33: human_notation = "c2"; break; case 43: human_notation = "c3"; break; case 53: human_notation = "c4"; break;
    case 63: human_notation = "c5"; break; case 73: human_notation = "c6"; break; case 83: human_notation = "c7"; break; case 93: human_notation = "c8"; break;
    case 24: human_notation = "d1"; break; case 34: human_notation = "d2"; break; case 44: human_notation = "d3"; break; case 54: human_notation = "d4"; break;
    case 64: human_notation = "d5"; break; case 74: human_notation = "d6"; break; case 84: human_notation = "d7"; break; case 94: human_notation = "d8"; break;
    case 25: human_notation = "e1"; break; case 35: human_notation = "e2"; break; case 45: human_notation = "e3"; break; case 55: human_notation = "e4"; break;
    case 65: human_notation = "e5"; break; case 75: human_notation = "e6"; break; case 85: human_notation = "e7"; break; case 95: human_notation = "e8"; break;
    case 26: human_notation = "f1"; break; case 36: human_notation = "f2"; break; case 46: human_notation = "f3"; break; case 56: human_notation = "f4"; break;
    case 66: human_notation = "f5"; break; case 76: human_notation = "f6"; break; case 86: human_notation = "f7"; break; case 96: human_notation = "f8"; break;
    case 27: human_notation = "g1"; break; case 37: human_notation = "g2"; break; case 47: human_notation = "g3"; break; case 57: human_notation = "g4"; break;
    case 67: human_notation = "g5"; break; case 77: human_notation = "g6"; break; case 87: human_notation = "g7"; break; case 97: human_notation = "g8"; break;
    case 28: human_notation = "h1"; break; case 38: human_notation = "h2"; break; case 48: human_notation = "h3"; break; case 58: human_notation = "h4"; break;
    case 68: human_notation = "h5"; break; case 78: human_notation = "h6"; break; case 88: human_notation = "h7"; break; case 98: human_notation = "h8"; break;
    }
    return human_notation;
}


std::vector<std::string> split(std::string str, char delimiter) 
{
    std::vector<std::string> splitted;
    std::stringstream ss(str); // Turn the string into a stream.
    std::string temporary;
    while (getline(ss, temporary, delimiter)) {
        splitted.push_back(temporary);
    }
    return splitted;
}

size_t board::get_size() const
{
    return size;
}

std::vector<std::unique_ptr<piece>> board::get_pieces()
{
    return pieces;
}

int board::get_piece_at_position(int index)
{
    return board_representation[index];
}

board::board()
{
    board_representation = new int[size] {};
    populate_out_of_range();
    std::string starting_fen{ "r1bqkbnr/ppp1pppp/2n5/3p4/3P4/5N2/PPP1PPPP/RNBQKB1R w KQkq - 0 3" };
    position(starting_fen);
}

board::board(controller &the_controller)
{
    board_controller = &the_controller;
    board_representation = new int[size] {};
    populate_out_of_range();
    std::string starting_fen{ "r1bqkbnr/ppp1pppp/2n5/3p4/3P4/5N2/PPP1PPPP/RNBQKB1R w KQkq - 0 3" };
    position(starting_fen);
}

void board::populate_out_of_range()
{
    for (size_t index{}; index < get_size(); index++) {
        if ((index >= 0 && index <= 20) || index >= 99 || (index - 1) % 10 == 8 || (index - 1) % 10 == 9) {
            board_representation[index] = 7;
        }
    }
}

void board::position(std::string FEN) 
{
    std::vector<std::string> splitted_fen = split(FEN, ' ');
    size_t i{};
    int j = 1;
    int file{};
    int rank{};
    char letter{};

    while ((j <= 64) && (i <= splitted_fen[0].length())) {
        letter = splitted_fen[0].at(i);
        i++;
        file = 1 + ((j - 1) % 8);
        rank = 8 - ((j - 1) / 8);
        size_t square;
        size_t squares_64 = (((rank - 1) * 8) + (file - 1));
        if (squares_64 < 8) { square = squares_64 + 21; }
        else if (squares_64 < 16) { square = squares_64 + 23; }
        else if (squares_64 < 24) { square = squares_64 + 25; }
        else if (squares_64 < 32) { square = squares_64 + 27; }
        else if (squares_64 < 40) { square = squares_64 + 29; }
        else if (squares_64 < 48) { square = squares_64 + 31; }
        else if (squares_64 < 56) { square = squares_64 + 33; }
        else if (squares_64 < 64) { square = squares_64 + 35; }
        switch (letter)
        {
        case 'p':
            board_representation[square] = -1;
            pieces.push_back(std::unique_ptr<pawn>(new pawn(-1, square)));
            break;
        case 'n':
            board_representation[square] = -2;
            pieces.push_back(std::unique_ptr<knight>(new knight(-1, square)));
            break;
        case 'b':
            board_representation[square] = -3;
            pieces.push_back(std::unique_ptr<bishop>(new bishop(-1, square)));
            break;
        case 'r':
            board_representation[square] = -4;
            pieces.push_back(std::unique_ptr<rook>(new rook(-1, square)));
            break;
        case 'q':
            board_representation[square] = -5;
            pieces.push_back(std::unique_ptr<queen>(new queen(-1, square)));
            break;
        case 'k':
            board_representation[square] = -6;
            pieces.push_back(std::unique_ptr<king>(new king(-1, square)));
            break;
        case 'P':
            board_representation[square] = 1;
            pieces.push_back(std::unique_ptr<pawn>(new pawn(1, square)));
            break;
        case 'N':
            board_representation[square] = 2;
            pieces.push_back(std::unique_ptr<knight>(new knight(1, square)));
            break;
        case 'B':
            board_representation[square] = 3;
            pieces.push_back(std::unique_ptr<bishop>(new bishop(1, square)));
            break;
        case 'R':
            board_representation[square] = 4;
            pieces.push_back(std::unique_ptr<rook>(new rook(1, square)));
            break;
        case 'Q':
            board_representation[square] = 5;
            pieces.push_back(std::unique_ptr<queen>(new queen(1, square)));
            break;
        case 'K':
            board_representation[square] = 6;
            pieces.push_back(std::unique_ptr<king>(new king(1, square)));
            break;
        case '/':
            j--;
            break;
        case '1':
            break;
        case '2':
            j++;
            break;
        case '3':
            j += 2;
            break;
        case '4':
            j += 3;
            break;
        case '5':
            j += 4;
            break;
        case '6':
            j += 5;
            break;
        case '7':
            j += 6;
            break;
        case '8':
            j += 7;
            break;
        }
        j++;
    }
    if (splitted_fen.size() >= 2) {
        if (splitted_fen.at(1) == "w") {
            board_controller->set_turn_to_move(1); //white
        }
        else if (splitted_fen.at(1) == "b") {
            board_controller->set_turn_to_move(-1); //black
        }
    }
}


void board::print_pieces()
{
    std::cout << "Pieces in position: " << std::endl;
    int piece_number{ 1 }; // counter 
    for (auto iterator = pieces.begin(); iterator != pieces.end(); iterator++) {
        std::cout << "Piece " << piece_number << " ";
        (*iterator)->print_piece_data();
        piece_number++;
    }
}

void board::remove_piece(int position) 
{
    std::vector<piece>::iterator iterator;
    for (auto iterator = pieces.begin(); iterator != pieces.end(); iterator++) {
        int currentPos = (*iterator)->get_position<int>();
        if (currentPos == position) {
            pieces.erase(iterator);
            break;
        }
    }
    board_representation[position] = 0;
}

void board::move_piece(int position)
{



}

void board::print_valid_moves(int position)
{
    int position_in_piece_vector{};
    std::vector<piece>::iterator iterator;
    std::vector<int> this_piece_valid_moves;
    for (auto iterator = pieces.begin(); iterator != pieces.end(); iterator++) {
        int currentPos = (*iterator)->get_position<int>();
        if (currentPos == position) {
            this_piece_valid_moves = (*iterator)->valid_moves(this);            
            break;
        }
        position_in_piece_vector++;
    }

    if (this_piece_valid_moves.size() != 0) {
        std::cout << "Possible moves for " << pieces.at(position_in_piece_vector)->name() << " at " << pieces.at(position_in_piece_vector)->get_position<std::string>() << std::endl;
        for (auto iterator = this_piece_valid_moves.begin(); iterator != this_piece_valid_moves.end(); iterator++) {
            std::cout << square_notation(*iterator) << std::endl;
        }
    }else {
        std::cout << "Error: no moves from: " << square_notation(position) << std::endl;
    }
}

std::string board::whose_turn_to_move() 
{
    std::string human_colour{};
    int colour = board_controller->get_turn_to_move();
    if (colour == 1) {
        human_colour = "white";
    }else if (colour == -1){
        human_colour = "black";
    }
    return human_colour;
}

namespace chess 
{

    std::string human_output(int computer_output) 
    {
        std::string human_output{};
        switch (computer_output) {
        case 0: human_output = " "; break;
        case 1: human_output = "P"; break;
        case -1: human_output = "p"; break;
        case 2: human_output = "N"; break;
        case -2: human_output = "n"; break;
        case 3: human_output = "B"; break;
        case -3: human_output = "b"; break;
        case 4: human_output = "R"; break;
        case -4: human_output = "r"; break;
        case 5: human_output = "Q"; break;
        case -5: human_output = "q"; break;
        case 6: human_output = "K"; break;
        case -6: human_output = "k"; break;
        case 7: human_output = ""; break;
        }

        return human_output;
    }




    std::ostream& operator<<(std::ostream& out_stream, const board& the_board)
    {
        std::cout << "|";
        if (the_board.get_size() > 0) {
            for (size_t mirror_index{ the_board.get_size() / 10 }; mirror_index > 0; mirror_index--) {
                for (size_t index{ (mirror_index - 1) * 10 }; index < mirror_index * 10; index++) {
                    if (the_board.board_representation[index] != 7) {
                        if ((index + 2) % 10 == 0 && index > 30 && index < 99) {
                            out_stream << human_output(the_board.board_representation[index]) << "|" << std::endl << "|";
                        }else if (index > 20 && index < 99) {
                            out_stream << human_output(the_board.board_representation[index]) << ";";
                        }else{
                            out_stream << human_output(the_board.board_representation[index]) << "|" << std::endl;
                        }
                    }
                }
            }

        }else {
            out_stream << "board is empty" << std::endl;
        }
        return out_stream;
    }
}

