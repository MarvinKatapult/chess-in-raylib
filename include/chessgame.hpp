#pragma once

class Board;
class Square;
struct Texture;
struct Font;

#include "piece.hpp"

class ChessGame {

    public:

        /** Constructor **/
        ChessGame( void );

        /** Deconstructor **/
        ~ChessGame( void );

        /** Utils **/
        void run( void );

    private:

        void loadTextures( void );

        void inputHandeling( void );
        void pressEvent( void );

        void drawBoard( void );
        void drawBoardPieces( void );
        void drawMoveDot( int x, int y );
        void drawPossibleMoves( void );

        Square * mySelectedSquare;
        Texture * myPieceTextures[PIECE_COLOR_COUNT][PIECE_COUNT];
        Board * myBoard;
        Pieces::PieceColor myTurn;
};
