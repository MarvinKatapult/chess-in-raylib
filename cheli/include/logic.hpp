#pragma once

class Board;
class Square;
class TList;
class TList;
typedef char PieceSymbol;

#include "piece.hpp"

class Logic {

    enum HorizontalDirection {
        Left = -1,
        HNone = 0,
        Right = 1
    };

    enum VerticalDirection {
        Up = -1,
        VNone = 0,
        Down = 1
    };
    
    public:

        /** Constructor **/
        Logic( Board * board );

        /** Modification **/
        void removeIllegalMoves( TList * list ) const;

        /** Utils **/
        TList getLegals( bool check_for_checks = true ) const;
        void getLegals( TList * list, const Square & square ) const;
        void getLegals( TList * legals, int x, int y ) const;
        Pieces::PieceColor isCheck( void ) const;
        Pieces::PieceColor isCheckmate( void ) const;

        static bool squareHasEnemy( const Square & square, Pieces::PieceColor color );
        static bool squareHasAlly( const Square & p_square, Pieces::PieceColor p_color );

    private:

        /** These functions have to be called with a square with the correspending piece on it **/
        void getLegalsPawn( TList * list, const Square & square ) const;
        void getLegalsBishop( TList * list, const Square & square ) const;
        void getLegalsRook( TList * list, const Square & square ) const;
        void getLegalsQueen( TList * list, const Square & square ) const;
        void getLegalsKing( TList * list, const Square & square ) const;
        void getLegalsKnight( TList * list, const Square & square ) const;
        void getLegalsPawnMove( TList * list, const Square & square ) const;
        void getLegalsPawnCapture( TList * list, const Square & square ) const;
        void getLegalsPawnEnpassant( TList * list, const Square & start_square ) const;

        bool checkEnpassant( const Square & start_square, int enemy_pawn_start_row, Logic::HorizontalDirection dir ) const;
        void checkPawnCapture( TList * list, const Square & start_square, const Square & dest_square ) const;
        void getLegalsCommon( TList * list, const Square & start_square, HorizontalDirection horizontal, VerticalDirection vertical, int range = 8 ) const;

        Board * myBoard;
};
