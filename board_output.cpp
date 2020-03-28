#include <iostream>

int main() {

    std::string white_king = "\u265A";
    std::string white_queen = "\u265B";
    std::string white_rook = "\u265C";
    std::string white_bishop = "\u265D";
    std::string white_knight = "\u265E";
    std::string white_pawn = "\u265F";

    std::string black_king = "\u2654";
    std::string black_queen = "\u2655";
    std::string black_rook = "\u2656";
    std::string black_bishop = "\u2657";
    std::string black_knight = "\u2658";
    std::string black_pawn = "\u2659";

    std::string black_square = "\u25E6";
    std::string white_square = "\u2022";

    //black pieces
    std::cout << "8 " << black_rook << " " << black_knight << " " << black_bishop << " " << black_queen << " " << black_king << " " <<
                black_bishop << " " << black_knight << " " << black_rook << std::endl;
    std::cout << "7 " << black_pawn << " " << black_pawn << " " << black_pawn << " " << black_pawn << " " << black_pawn << " " << 
                black_pawn << " " << black_pawn << " " << black_pawn << std::endl;
    //empty middle
    std::cout << "6 " << white_square << " " << black_square << " " << white_square << " " << black_square << " " << white_square << " " << 
                black_square << " " << white_square << " " << black_square << 
                std::endl << "5 " << black_square << " " << white_square << " " << black_square << " " << white_square << " " << 
                black_square << " " << white_square << " " << black_square << " " << white_square << 
                std::endl << "4 " << white_square << " " << black_square << " " << white_square << " " << black_square << " " << white_square << " " << 
                black_square << " " << white_square << " " << black_square << 
                std::endl << "3 " << black_square << " " << white_square << " " << black_square << " " << white_square << " " << 
                black_square << " " << white_square << " " << black_square << " " << white_square << 
                std::endl;

    //white pieces
    std::cout << "2 " << white_pawn << " " << white_pawn << " " << white_pawn << " " << white_pawn << " " << white_pawn << " " << 
                white_pawn << " " << white_pawn << " " << white_pawn << " " << std::endl;
    std::cout << "1 " << white_rook << " " << white_knight << " " << white_bishop << " " << white_queen << " " << white_king << " " <<
                white_bishop << " " << white_knight << " " << white_rook << std::endl;

    std::cout << "  A B C D E F G H" << std::endl;
    //initial position would be:

    return 0;


}