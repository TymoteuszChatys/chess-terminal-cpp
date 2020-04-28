#ifndef PIECES_H
#define PIECES_H


#include<string>
#include<vector>

namespace chess
{
    class board;
    class piece
    {
    protected:
        int colour{};
        size_t position{};
    public:
        piece() {};
        piece(int the_colour, size_t the_position);
        virtual ~piece() {}
        template<typename colour_type> colour_type get_colour();
        template<typename colour_type> colour_type get_position();
        virtual std::string name() = 0;
        virtual int tag() = 0;
        virtual std::vector<int> valid_moves(chess::board* the_board) = 0;
        void print_piece_data();

    };

    class king : public piece
    {
    public:
        king() {}
        king(int the_colour, size_t the_position) : piece{ the_colour, the_position } {};
        ~king() {}

        std::string name();
        int tag();
        std::vector<int> valid_moves(chess::board* the_board);
    };

    class queen : public piece
    {
    public:
        queen() {}
        queen(int the_colour, size_t the_position) : piece{ the_colour, the_position } {};
        ~queen() {}

        std::string name();
        int tag();
        std::vector<int> valid_moves(chess::board* the_board);
    };

    class rook : public piece
    {
    public:
        rook() {}
        rook(int the_colour, size_t the_position) : piece{ the_colour, the_position } {};
        ~rook() {}

        std::string name();
        int tag();
        std::vector<int> valid_moves(chess::board* the_board);
    };

    class bishop : public piece
    {
    public:
        bishop() {}
        bishop(int the_colour, size_t the_position) : piece{ the_colour, the_position } {};
        ~bishop() {}

        std::string name();
        int tag();
        std::vector<int> valid_moves(chess::board* the_board);
    };

    class knight : public piece
    {
    public:
        knight() {}
        knight(int the_colour, size_t the_position) : piece{ the_colour, the_position } {};
        ~knight() {}

        std::string name();
        int tag();
        std::vector<int> valid_moves(chess::board* the_board);
    };

    class pawn : public piece
    {
    public:
        pawn() {}
        pawn(int the_colour, size_t the_position) : piece{ the_colour, the_position } {};
        ~pawn() {}

        std::string name();
        int tag();
        std::vector<int> valid_moves(chess::board* the_board);
    };




}
#endif