#include<iostream>
#include<string>
#include "pieces.h"
#include "board.h"

using namespace chess;

piece::piece(int the_colour, size_t the_position)
{
    colour = the_colour;
    position = the_position;
    std::cout << "Piece constructor" << std::endl;
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


void piece::print_piece_data() 
{// Print out pieces data
    std::cout << get_colour<std::string>() << " " << name() << " at " <<  std::endl;
}
