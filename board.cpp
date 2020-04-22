#include "board.h"
#include "pieces.h"

using namespace chess;


std::vector<std::string> split(std::string str, char delimiter) {
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

board::board()
{
    board_representation = new int[size] {};
    populate_out_of_range();
    std::string starting_fen{ "rnbqkbnr/pp1ppppp/8/2p5/4P3/8/PPPP1PPP/RNBQKBNR w KQkq - 0 2" };
    position(starting_fen);
}

void board::populate_out_of_range()
{
    for (size_t index{}; index < get_size(); index++) {
        if ((index >= 0 && index <= 20) || index >= 99 || (index - 1) % 10 == 8 || (index - 1) % 10 == 9) {
            std::cout << "hi" << std::endl;
            board_representation[index] = 7;
        }
    }
}

void board::position(std::string FEN) {
    std::vector<std::string> splitted_fen = split(FEN, ' ');
    int j = 1;
    int i{};
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
            //new pawn(-1,square); 
            break;
        case 'n':
            board_representation[square] = -2;
            // new knight(-1,square); 
            break;
        case 'b':
            board_representation[square] = -3;
            //new bishop(-1,square); 
            break;
        case 'r':
            board_representation[square] = -4;
            // new rook(-1,square); 
            break;
        case 'q':
            board_representation[square] = -5;
            // new queen(-1,square); 
            break;
        case 'k':
            board_representation[square] = -6;
            // new king(-1,square); 
            break;
        case 'P':
            board_representation[square] = 1;
            // new pawn(1,square); 
            break;
        case 'N':
            board_representation[square] = 2;
            // new knight(1,square); 
            break;
        case 'B':
            board_representation[square] = 3;
            // new bishop(1,square); 
            break;
        case 'R':
            board_representation[square] = 4;
            // new rook(1,square); 
            break;
        case 'Q':
            board_representation[square] = 5;
            // new queen(1,square); 
            break;
        case 'K':
            board_representation[square] = 6;
            // new king(1,square); 
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
}

namespace chess {
    std::ostream& operator<<(std::ostream& out_stream, const board& the_board)
    {
        if (the_board.get_size() > 0) {
            for (size_t mirror_index{ the_board.get_size() / 10 }; mirror_index > 0; mirror_index--) {
                for (size_t index{ (mirror_index - 1) * 10 }; index < mirror_index * 10; index++) {
                    if ((index + 1) % 10 == 0) {
                        out_stream << the_board.board_representation[index] << std::endl;
                    }
                    else {
                        out_stream << the_board.board_representation[index] << ";";
                    }
                }
            }

        }
        else {
            out_stream << "board is empty" << std::endl;
        }
        return out_stream;
    }
}

