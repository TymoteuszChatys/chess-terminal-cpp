#include "board.h"
#include "pieces.h"
#include "controller.h"
#include "ctype.h"
#include <cctype>

//Colours
HANDLE boardConsole = GetStdHandle(STD_OUTPUT_HANDLE);
#define GREEN_F		(SetConsoleTextAttribute(boardConsole, FOREGROUND_GREEN))  //sets the console colour to green
#define RED_F		(SetConsoleTextAttribute(boardConsole, FOREGROUND_RED))  //sets the console colour to red
#define BLUE_F		(SetConsoleTextAttribute(boardConsole, FOREGROUND_BLUE)) //sets the console colour to blue
#define WHITE_F		(SetConsoleTextAttribute(boardConsole, FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN)) //defines the colour white



using namespace chess;


std::string square_notation_to_human(int square) 
{
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

constexpr unsigned int string_to_integer(const char* string, int h = 0)
{
    return !string[h] ? 5381 : (string_to_integer(string, h + 1) * 33) ^ string[h];
}

int square_notation_to_computer(std::string square)
{
    //function to associate human notation to a numerical value;
    int computer_notation{};
    switch (string_to_integer(square.c_str())) {
    case string_to_integer("a1"): computer_notation = 21; break; case string_to_integer("a2"): computer_notation = 31; break; 
    case string_to_integer("a3"): computer_notation = 41; break; case string_to_integer("a4"): computer_notation = 51; break;
    case string_to_integer("a5"): computer_notation = 61; break; case string_to_integer("a6"): computer_notation = 71; break; 
    case string_to_integer("a7"): computer_notation = 81; break; case string_to_integer("a8"): computer_notation = 91; break;
    case string_to_integer("b1"): computer_notation = 22; break; case string_to_integer("b2"): computer_notation = 32; break; 
    case string_to_integer("b3"): computer_notation = 42; break; case string_to_integer("b4"): computer_notation = 52; break;
    case string_to_integer("b5"): computer_notation = 62; break; case string_to_integer("b6"): computer_notation = 72; break; 
    case string_to_integer("b7"): computer_notation = 82; break; case string_to_integer("b8"): computer_notation = 92; break;
    case string_to_integer("c1"): computer_notation = 23; break; case string_to_integer("c2"): computer_notation = 33; break; 
    case string_to_integer("c3"): computer_notation = 43; break; case string_to_integer("c4"): computer_notation = 53; break;
    case string_to_integer("c5"): computer_notation = 63; break; case string_to_integer("c6"): computer_notation = 73; break; 
    case string_to_integer("c7"): computer_notation = 83; break; case string_to_integer("c8"): computer_notation = 93; break;
    case string_to_integer("d1"): computer_notation = 24; break; case string_to_integer("d2"): computer_notation = 34; break; 
    case string_to_integer("d3"): computer_notation = 44; break; case string_to_integer("d4"): computer_notation = 54; break;
    case string_to_integer("d5"): computer_notation = 64; break; case string_to_integer("d6"): computer_notation = 74; break; 
    case string_to_integer("d7"): computer_notation = 84; break; case string_to_integer("d8"): computer_notation = 94; break;
    case string_to_integer("e1"): computer_notation = 25; break; case string_to_integer("e2"): computer_notation = 35; break; 
    case string_to_integer("e3"): computer_notation = 45; break; case string_to_integer("e4"): computer_notation = 55; break;
    case string_to_integer("e5"): computer_notation = 65; break; case string_to_integer("e6"): computer_notation = 75; break; 
    case string_to_integer("e7"): computer_notation = 85; break; case string_to_integer("e8"): computer_notation = 95; break;
    case string_to_integer("f1"): computer_notation = 26; break; case string_to_integer("f2"): computer_notation = 36; break; 
    case string_to_integer("f3"): computer_notation = 46; break; case string_to_integer("f4"): computer_notation = 56; break;
    case string_to_integer("f5"): computer_notation = 66; break; case string_to_integer("f6"): computer_notation = 76; break; 
    case string_to_integer("f7"): computer_notation = 86; break; case string_to_integer("f8"): computer_notation = 96; break;
    case string_to_integer("g1"): computer_notation = 27; break; case string_to_integer("g2"): computer_notation = 37; break; 
    case string_to_integer("g3"): computer_notation = 47; break; case string_to_integer("g4"): computer_notation = 57; break;
    case string_to_integer("g5"): computer_notation = 67; break; case string_to_integer("g6"): computer_notation = 77; break; 
    case string_to_integer("g7"): computer_notation = 87; break; case string_to_integer("g8"): computer_notation = 97; break;
    case string_to_integer("h1"): computer_notation = 28; break; case string_to_integer("h2"): computer_notation = 38; break; 
    case string_to_integer("h3"): computer_notation = 48; break; case string_to_integer("h4"): computer_notation = 58; break;
    case string_to_integer("h5"): computer_notation = 68; break; case string_to_integer("h6"): computer_notation = 78; break; 
    case string_to_integer("h7"): computer_notation = 88; break; case string_to_integer("h8"): computer_notation = 98; break;
    }
    return computer_notation;
}

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

std::vector<std::shared_ptr<piece>> board::get_pieces()
{
    return pieces;
}

int board::get_piece_at_position(int index)
{
    return board_representation[index];
}

int* board::get_board_representation() 
{
    return board_representation;
}

std::string board::get_fen() const
{
    std::string fen;
    if (get_size() > 0) {
        for (size_t mirror_index{ (get_size() / 10)-2 }; mirror_index > 2; mirror_index--) {
            size_t number{};
            for (size_t index{ (mirror_index - 1) * 10 }; index < mirror_index * 10; index++) {
                if (board_representation[index] != 7) {
                    if (board_representation[index] == 0) {
                        number++;
                    }
                    else {
                        if (number != 0) {
                            fen = fen + std::to_string(number);
                            fen = fen + human_output(board_representation[index]);
                            number = 0;
                        }
                        else {
                            fen = fen + human_output(board_representation[index]);
                        }
                    }
                }
            
            }
            if (number != 0) {
                fen = fen + std::to_string(number);
            }
            fen = fen + "/";
            
        }
        if (!fen.empty()) {
            fen.pop_back();
        }
        int turn_to_move = board_controller->get_turn_to_move();
        if (turn_to_move == 1) {
            fen = fen + " w";
        }else if (turn_to_move == -1) {
            fen = fen + " b";
        }

        fen = fen + " ";

        if (white_castle_king == true) {
            fen = fen + "K";
        }
        if (white_castle_queen == true) {
            fen = fen + "Q";
        }
        if (black_castle_king == true) {
            fen = fen + "k";
        }
        if (black_castle_queen == true) {
            fen = fen + "q";
        }
    }
    return fen;
}



board::board()
{
    board_representation = new int[size] {};
    populate_out_of_range();
    std::string starting_fen{ "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1" };
    position(starting_fen);
}

board::board(controller *the_controller)
{
    board_controller = the_controller;
    board_representation = new int[size] {};
    populate_out_of_range();
    std::string starting_fen{ "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1" };
    position(starting_fen);
}


//Copy constructor
board::board(const board& a_board, controller *a_controller)
{
    board_controller = a_controller;
    board_representation = new int[size] {};
    populate_out_of_range();
    position(a_board.get_fen());
}


void board::populate_out_of_range()
{
    for (size_t index{}; index < get_size(); index++) {
        if ((index >= 0 && index <= 20) || index >= 99 || (index - 1) % 10 == 8 || (index - 1) % 10 == 9) {
            board_representation[index] = 7;
        }
    }
}

//FEN string parser. Takes in the FEN strings and makes the baord as appropriate.
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
            pieces.push_back(std::shared_ptr<pawn>(new pawn(-1, square)));
            break;
        case 'n':
            board_representation[square] = -2;
            pieces.push_back(std::shared_ptr<knight>(new knight(-1, square)));
            break;
        case 'b':
            board_representation[square] = -3;
            pieces.push_back(std::shared_ptr<bishop>(new bishop(-1, square)));
            break;
        case 'r':
            board_representation[square] = -4;
            pieces.push_back(std::shared_ptr<rook>(new rook(-1, square)));
            break;
        case 'q':
            board_representation[square] = -5;
            pieces.push_back(std::shared_ptr<queen>(new queen(-1, square)));
            break;
        case 'k':
            board_representation[square] = -6;
            pieces.push_back(std::shared_ptr<king>(new king(-1, square)));
            break;
        case 'P':
            board_representation[square] = 1;
            pieces.push_back(std::shared_ptr<pawn>(new pawn(1, square)));
            break;
        case 'N':
            board_representation[square] = 2;
            pieces.push_back(std::shared_ptr<knight>(new knight(1, square)));
            break;
        case 'B':
            board_representation[square] = 3;
            pieces.push_back(std::shared_ptr<bishop>(new bishop(1, square)));
            break;
        case 'R':
            board_representation[square] = 4;
            pieces.push_back(std::shared_ptr<rook>(new rook(1, square)));
            break;
        case 'Q':
            board_representation[square] = 5;
            pieces.push_back(std::shared_ptr<queen>(new queen(1, square)));
            break;
        case 'K':
            board_representation[square] = 6;
            pieces.push_back(std::shared_ptr<king>(new king(1, square)));
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

    set_white_castle_king(true);
    set_white_castle_queen(true);
    set_black_castle_king(true);
    set_black_castle_queen(true);

    if (splitted_fen.size() >= 3){ 
        if (splitted_fen.at(2).find('K') == std::string::npos) {
            set_white_castle_king(false);
        }

        if (splitted_fen.at(2).find('Q') == std::string::npos) {
            set_white_castle_queen(false);
        }

        if (splitted_fen.at(2).find('k') == std::string::npos) {
            set_black_castle_king(false);
        }

        if (splitted_fen.at(2).find('q') == std::string::npos) {
            set_black_castle_queen(false);
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

void board::move_piece(int final_position, std::shared_ptr<piece> the_piece)
{
    board_representation[the_piece->get_position<int>()] = 0;
    the_piece->set_position(final_position);
    board_representation[final_position] = the_piece->tag();
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
        std::cout << "Possible moves for " << pieces.at(position_in_piece_vector)->name() << " at " << pieces.at(position_in_piece_vector)->get_position<std::string>() << ":  ";
        for (auto iterator = this_piece_valid_moves.begin(); iterator != this_piece_valid_moves.end(); iterator++) {
            GREEN_F;
            std::cout << square_notation_to_human(*iterator) << " ";
            WHITE_F;
        }
    }else {
        std::cout << "Error: no moves from " << square_notation_to_human(position);
    }
    std::cout << std::endl;
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

bool board::get_white_castle_king()
{
    return white_castle_king;
}

bool board::get_white_castle_queen()
{
    return white_castle_queen;
}

bool board::get_black_castle_king()
{
    return black_castle_king;
}

bool board::get_black_castle_queen()
{
    return black_castle_queen;
}

void board::set_white_castle_king(bool true_or_false) 
{
    if (true_or_false == true) {
        white_castle_king = true;
    }else {
        white_castle_king = false;
    }
}

void board::set_white_castle_queen(bool true_or_false)
{
    if (true_or_false == true) {
        white_castle_queen = true;
    }else {
        white_castle_queen = false;
    }
}

void board::set_black_castle_king(bool true_or_false)
{
    if (true_or_false == true) {
        black_castle_king = true;
    }else {
        black_castle_king = false;
    }
}

void board::set_black_castle_queen(bool true_or_false)
{
    if (true_or_false == true) {
        black_castle_queen = true;
    }else {
        black_castle_queen = false;
    }
}

namespace chess 
{

    std::ostream& operator<<(std::ostream& out_stream, const board& the_board)
    {
        std::string alignment("                  ");
        std::cout << std::endl << std::endl;
        std::vector<std::string> side_board {"8", "7", "6", "5", "4", "3", "2", "1"};
        int side_of_board_counter{};
        GREEN_F; std::cout << alignment << side_board.at(side_of_board_counter); WHITE_F;
        std::cout << "|";
        if (the_board.get_size() > 0) {
            for (size_t mirror_index{ the_board.get_size() / 10 }; mirror_index > 0; mirror_index--) {
                for (size_t index{ (mirror_index - 1) * 10 }; index < mirror_index * 10; index++) {
                    if (the_board.board_representation[index] != 7) {
                        std::string output = human_output(the_board.board_representation[index]);
                        char output_character = output[0];
                        bool colour_blue{};
                        if (isupper(output_character)) {
                           colour_blue = true;
                        }

                        if ((index + 2) % 10 == 0 && index > 30 && index < 99) {
                            side_of_board_counter++;
                            if (colour_blue == true) {
                                BLUE_F;
                            }else{
                                RED_F;
                            }
                            out_stream << output; WHITE_F;
                            out_stream << "|" << std::endl;
                            GREEN_F; std::cout << alignment << side_board.at(side_of_board_counter); WHITE_F;
                            out_stream << "|";
                        }else if (index > 20 && index < 99) {
                            if (colour_blue == true) {
                                BLUE_F;
                            }else {
                                RED_F;
                            }
                            out_stream << output; WHITE_F;
                            out_stream << ":";
                        }else{
                            if (colour_blue == true) {
                                BLUE_F;
                            }else {
                                RED_F;
                            }
                            out_stream << output; WHITE_F;
                            out_stream << "|" << std::endl;
                        }
                    }
                }
            }
            GREEN_F; out_stream << std::endl << alignment << "  a b c d e f g h" << std::endl; WHITE_F;
        }else {
            out_stream << "board is empty" << std::endl;
        }
        return out_stream;
    }

    bool board::is_king_in_check(int colour)
    {
        std::shared_ptr<piece> the_king;
        bool in_check{ false };
        int position_in_piece_vector{};

        //Get the king piece
        for (auto iterator = pieces.begin(); iterator != pieces.end(); iterator++) {
            int tag = (*iterator)->tag();
            if (tag == colour * 6) {
                the_king = (*iterator);
                break;
            }
        }

   
        //Check if any opponent piece can take it if it were its move. If it is. The king is in check.
        std::vector<int> this_piece_valid_moves;
        for (auto iterator = pieces.begin(); iterator != pieces.end(); iterator++) {
            int piece_colour = (*iterator)->get_colour<int>();
            if (piece_colour == colour * -1) {
                this_piece_valid_moves = (*iterator)->valid_moves_before_check(this);
                for (auto iterator = this_piece_valid_moves.begin(); iterator != this_piece_valid_moves.end(); iterator++) {
                    if ((*iterator) == the_king->get_position<int>()) {
                        in_check = true;
                    }
                }   
            }           
        }
        return in_check;
    }

}



