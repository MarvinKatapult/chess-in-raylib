#include "square.hpp"

#include "tstring.hpp"

Square::Square() {
    x = 0;
    y = 0;
    piece = Pieces::NoPiece;
}

Square::Square( short p_x, short p_y, Piece p_piece ) {
    x = p_x;
    y = p_y;
    piece = p_piece;
}


Square::Square( const Square & p_other ) {
    x = p_other.x;
    y = p_other.y;
    piece = p_other.piece;
}

Square & Square::operator=( const Square & p_other ) {
    x = p_other.x;
    y = p_other.y;
    piece = p_other.piece;

    return *this;
}

TString Square::name( void ) const {
    TString str( (char)(97 + x) );
    str += 8 - y;

    return str;
}
