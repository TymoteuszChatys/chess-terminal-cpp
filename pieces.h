#ifndef PIECES_H
#define PIECES_H


#include<string>


namespace chess{
    class piece {
    protected:
        int colour;
        size_t position;
    public:
        piece() {}
        piece(int the_colour, size_t the_position);
        virtual ~piece() {}
        int get_colour();
        virtual std::string name()=0;
        
    };

    class king : public piece {
    public:
        king() {}
        king(int the_colour, size_t the_position);
        ~king(){}

        std::string name();
    };

    class queen : public piece {
    public:
        queen() {}
        queen(int the_colour, size_t the_position);
        ~queen(){}

        std::string name();
    };

    class rook : public piece {
    public:
        rook() {}
        rook(int the_colour, size_t the_position);
        ~rook(){}

        std::string name();
    };

    class bishop : public piece {
    public:
        bishop() {}
        bishop(int the_colour, size_t the_position);
        ~bishop(){}

        std::string name();
    };

    class knight : public piece {
    public:
        knight() {}
        knight(int the_colour, size_t the_position);
        ~knight(){}

        std::string name();
    };

    class pawn : public piece {
    public:
        pawn() {}
        pawn(int the_colour, size_t the_position);
        ~pawn(){}

        std::string name();
    };
}
#endif