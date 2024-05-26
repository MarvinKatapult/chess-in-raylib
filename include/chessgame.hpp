#pragma once

class Board;
class Texture;

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

        void drawBoard( void );
        void drawBoardPieces( void );

        Texture * myPieceTextures[PIECE_COLOR_COUNT][PIECE_COUNT];
        Board * myBoard;
};
