#include "piece.hpp"

#include <ctype.h>

bool Pieces::isPiece( char p_piece ) {
    char norm_symbol = tolower( p_piece );
    return ( norm_symbol == 'p'
          || norm_symbol == 'b'
          || norm_symbol == 'n'
          || norm_symbol == 'r'
          || norm_symbol == 'q'
          || norm_symbol == 'k' );
}

Pieces::PieceColor Pieces::getColor( Piece p_piece ) {
    if ( p_piece == Pieces::NoPiece ) return Pieces::NoColor;
    return islower( p_piece ) != 0 ? Pieces::Black : Pieces::White;
}

Pieces::NormPiece Pieces::getNormPiece( PieceSymbol p_symbol ) {
    switch ( p_symbol ) {
        case Pieces::WhitePawn:
        case Pieces::BlackPawn:
            return Pieces::Pawn;
        case Pieces::WhiteKnight:
        case Pieces::BlackKnight:
            return Pieces::Knight;
        case Pieces::WhiteBishop:
        case Pieces::BlackBishop:
            return Pieces::Bishop;
        case Pieces::WhiteRook:
        case Pieces::BlackRook:
            return Pieces::Rook;
        case Pieces::WhiteQueen:
        case Pieces::BlackQueen:
            return Pieces::Queen;
        case Pieces::WhiteKing:
        case Pieces::BlackKing:
            return Pieces::King;
        case Pieces::NoPiece:
        default:
            return Pieces::NoNormPiece;
    }

    return Pieces::NoNormPiece;
}
