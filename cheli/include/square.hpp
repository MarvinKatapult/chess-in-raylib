#pragma once

#include "piece.hpp"

class TString;

class Square {

    public:

        /** Constructor **/
        Square( void );
        Square( short x, short y, Piece piece = Pieces::NoPiece );
        Square( const Square & other );

        /** Utils **/
        bool isFree( void ) const { return piece == Pieces::NoPiece; }
        TString name( void ) const;

        /** Operators **/
        Square & operator=( const Square & other );

        Piece piece;
        short x;
        short y;
};
