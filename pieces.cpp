#include<iostream>
#include<string>
#include "pieces.h"

using namespace chess;

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

int piece::get_colour()
{
    return colour;
}

