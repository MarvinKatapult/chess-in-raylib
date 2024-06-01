#pragma once

class Square;
class Move;

typedef char Piece;

#define BOARD_WIDTH     8
#define BOARD_HEIGHT    8
#define BOARD_SIZE      64

class Board {

    public:

        /** Constructors **/
        Board( const char * fenstring = "" );
        Board( const Board & other );

        /** Deconstructor **/
        ~Board( void );

        /** Modification **/
        bool set( const char * fenstring );
        void set( const Board & other );
        void playMove( const Move & move );
        void clear( void );

        /** Utils **/
        Square getSquare( int x, int y ) const;
        const Move * getLastMove( void ) const;
        Piece piece( int x, int y ) const;
        void printBoard( void ) const;

        /** Operators **/
        Board & operator=( const Board & other );

    private:

        void initSquares( void );

        Square * mySquares[BOARD_WIDTH][BOARD_HEIGHT];
        Move * myLastMove;
};
