#include "board.hpp"

#include <ctype.h>

#include "tlog.hpp"

#include "move.hpp"
#include "piece.hpp"
#include "square.hpp"

Board::Board( const char * p_fenstring ) {
    initSquares();
    set( p_fenstring );

    myLastMove = 0L;
}

Board::Board( const Board & p_other ) {
    initSquares();
    set( p_other ); 

    myLastMove = 0L;
}

void Board::initSquares() {
    for ( int y = 0; y < BOARD_HEIGHT; y++ ) {
        for ( int x = 0; x < BOARD_WIDTH; x++ ) {
            mySquares[y][x] = new Square( x, y );
        } 
    }
}

Board::~Board() {
    for ( int y = 0; y < BOARD_HEIGHT; y++ ) {
        for ( int x = 0; x < BOARD_WIDTH; x++ ) {
            delete mySquares[y][x];
        } 
    }

    if ( myLastMove ) delete myLastMove;
}

bool Board::set( const char * p_fenstring ) {
    clear();

    int square_index = 0;
    int char_index = 0; 
    char current_char = '0';

    while ( current_char != '\0' ) {
        current_char = p_fenstring[char_index++]; 

        // Calculate x and y of square
        int x_index = square_index % BOARD_HEIGHT;
        int y_index = square_index / BOARD_WIDTH;
        if ( x_index > BOARD_HEIGHT - 1 ) return false;
        if ( y_index > BOARD_WIDTH - 1  ) return false;

        // If Char is a number skip fields
        if ( isdigit( current_char ) ) {
            // Convert to number
            int empty_fields = current_char - '0';
            square_index += empty_fields;
            continue;
        }

        // Skip / 
        if ( current_char == '/' || !Pieces::isPiece( current_char ) )
            continue;

        // If current char is alpha read piece
        if ( isalpha( current_char ) ) {
            // Create New Piece
            mySquares[y_index][x_index]->piece = current_char;

            // Add Piece to square
            square_index++; 
            continue;
        } 
    }
      
    return true;
}

void Board::set( const Board & p_other ) {
    for ( int y = 0; y < BOARD_HEIGHT; y++ ) {
        for ( int x = 0; x < BOARD_WIDTH; x++ ) {
            mySquares[y][x]->piece = p_other.piece( x, y );
        }
    }
}

Square Board::getSquare( int p_x, int p_y ) const {
    return *mySquares[p_y][p_x];
}

const Move * Board::getLastMove() const {
    return myLastMove;
}

Piece Board::piece( int p_x, int p_y ) const {
    return mySquares[p_y][p_x]->piece;
}

void Board::printBoard() const {
    TLog log( TLog::Red );
    log.print( "  " );
    for ( int i = 0; i < BOARD_WIDTH; i++ ) {
        log.print( TLog::White, "%c ", 97 + i );
    }
    log.print( "\n" );

    for ( int y = 0; y < BOARD_HEIGHT; y++ ) {
        log.print( TLog::White, "%d ", 8 - y );
        for ( int x = 0; x < BOARD_WIDTH; x++ ) {
            log.print( Pieces::getColor( mySquares[y][x]->piece ) == Pieces::White ? TLog::Green : TLog::Blue, "%c ", mySquares[y][x]->piece );
        }
        log.print( "\n" );
    }
}

Board & Board::operator=( const Board & p_other ) {
    set( p_other ); 
    return *this;
}

void Board::playMove( const Move & p_move ) {
    mySquares[p_move.startY()][p_move.startX()]->piece = Pieces::NoPiece;
    mySquares[p_move.destY()][p_move.destX()]->piece = p_move.piece();

    myLastMove = new Move( p_move );
}

void Board::clear() {
    for ( int y = 0; y < BOARD_HEIGHT; y++ ) {
        for ( int x = 0; x < BOARD_WIDTH; x++ ) {
            mySquares[y][x]->piece = Pieces::NoPiece;
        }
    }
}
