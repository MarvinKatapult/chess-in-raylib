#include "chessgame.hpp"

#include <board.hpp>

#include "tlog.hpp"

#include "raylib.h"

#define SQUARE_SIZE     110
#define BOARD_WIDTH     8
#define BOARD_HEIGHT    8
#define BOARD_SIZE      64

#define SCREEN_WIDTH    ( BOARD_WIDTH * SQUARE_SIZE )
#define SCREEN_HEIGHT   ( BOARD_HEIGHT * SQUARE_SIZE )

#define DEFAULT_FENSTRING   "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR"

#include <stdlib.h>

ChessGame::ChessGame() {
    myBoard = new Board( DEFAULT_FENSTRING );
}

ChessGame::~ChessGame() {
    delete myBoard;
    for ( int i = 0; i < PIECE_COLOR_COUNT; i++ ) {
        for ( int j = 0; j < PIECE_COUNT; j++ ) {
            delete( myPieceTextures[i][j] );
        }
    } 
}

void ChessGame::run() {
    InitWindow( SCREEN_WIDTH, SCREEN_HEIGHT, "Chess - DEV" ); 
    SetTargetFPS( 60 );
    loadTextures();

    while ( !WindowShouldClose() ) {
        
        BeginDrawing();
            ClearBackground( WHITE );
            drawBoard();
            drawBoardPieces();
        EndDrawing();
    }

    CloseWindow();
}

void ChessGame::loadTextures() {
    Image temp_images[PIECE_COLOR_COUNT][PIECE_COUNT] = {
        {
            LoadImage( "assets/white-pawn.png" ),
            LoadImage( "assets/white-knight.png" ),
            LoadImage( "assets/white-bishop.png" ),
            LoadImage( "assets/white-rook.png" ),
            LoadImage( "assets/white-queen.png" ),
            LoadImage( "assets/white-king.png" )
        },
        {
            LoadImage( "assets/black-pawn.png" ),
            LoadImage( "assets/black-knight.png" ),
            LoadImage( "assets/black-bishop.png" ),
            LoadImage( "assets/black-rook.png" ),
            LoadImage( "assets/black-queen.png" ),
            LoadImage( "assets/black-king.png" )
        }
    };

    for ( int i = 0; i < PIECE_COLOR_COUNT; i++ ) {
        for ( int j = 0; j < PIECE_COUNT; j++ ) {
            myPieceTextures[i][j] = (Texture *)malloc( sizeof( Texture ) );
            ImageResize( &temp_images[i][j], SQUARE_SIZE, SQUARE_SIZE );
            (*myPieceTextures[i][j]) = LoadTextureFromImage( temp_images[i][j] );
        }
    } 
}

void ChessGame::drawBoard() {
    for ( int y = 0; y < BOARD_HEIGHT; y++ ) {
        for ( int x = 0; x < BOARD_WIDTH; x++ ) {
            Color rect_col = (x + y) % 2 == 0 ? DARKBLUE : WHITE;
            DrawRectangle( x * SQUARE_SIZE, y * SQUARE_SIZE, SQUARE_SIZE, SQUARE_SIZE, rect_col );
        }
    } 
}

void ChessGame::drawBoardPieces() {
    for ( int y = 0; y < BOARD_HEIGHT; y++ ) {
        for ( int x = 0; x < BOARD_WIDTH; x++ ) {
            Piece piece = myBoard->piece( x, y );
            if ( piece == Pieces::NoPiece ) continue;
            const int color_index = Pieces::getColor( piece );
            const int piece_index = Pieces::getNormPiece( (Pieces::PieceSymbol)piece );
            Texture piece_tex = *myPieceTextures[color_index][piece_index];

            TLog::log( "Drawing Texture with %c\n", piece );
            TLog::log( "ColorInd:%d; PieceIndex:%d; Width:%d\n", color_index, piece_index, piece_tex.width );

            DrawTexture( piece_tex, x * SQUARE_SIZE, y * SQUARE_SIZE, WHITE );
        }
    }
}
