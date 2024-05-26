#pragma once

typedef char Piece;

#define PIECE_COUNT         6
#define PIECE_COLOR_COUNT   2

namespace Pieces {

    enum NormPiece {
        Pawn = 0,
        Knight,
        Bishop,
        Rook,
        Queen,
        King,
        NoNormPiece
    };

    enum PieceSymbol {
        BlackPawn = 'p',
        WhitePawn = 'P',
        BlackKnight = 'n',
        WhiteKnight = 'N',
        BlackBishop = 'b',
        WhiteBishop = 'B',
        BlackRook = 'r',
        WhiteRook = 'R',
        BlackQueen = 'q',
        WhiteQueen = 'Q',
        BlackKing = 'k',
        WhiteKing = 'K',

        NoPiece = ' '
    };

    enum PieceColor {
        White = 0,
        Black,
        NoColor
    };

    /** Utils **/
    bool isPiece( char piece );
    PieceColor getColor( Piece piece );
    NormPiece getNormPiece( PieceSymbol symbol );

};
