#include "chessgame.hpp"

#include "logic.hpp"
#include "board.hpp"
#include "square.hpp"
#include "move.hpp"

#include "tlog.hpp"
#include "tlist.hpp"
#include "tstring.hpp"

#include "raylib.h"

#define SQUARE_SIZE     110
#define BOARD_WIDTH     8
#define BOARD_HEIGHT    8
#define BOARD_SIZE      64

#define SCREEN_WIDTH    ( BOARD_WIDTH * SQUARE_SIZE )
#define SCREEN_HEIGHT   ( BOARD_HEIGHT * SQUARE_SIZE )

#define MOVE_DOT_RADIUS     10

#define DEFAULT_FENSTRING   "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR"

#include <stdlib.h>

ChessGame::ChessGame() {
    myBoard = new Board( DEFAULT_FENSTRING );
    mySelectedSquare = 0L;
    myTurn = Pieces::White;
    // *myFont = LoadFont( "assets/LiberationMono-Bold.ttf" );
}

ChessGame::~ChessGame() {
    if ( mySelectedSquare ) delete mySelectedSquare;
    for ( int i = 0; i < PIECE_COLOR_COUNT; i++ ) {
        for ( int j = 0; j < PIECE_COUNT; j++ ) {
            delete( myPieceTextures[i][j] );
        }
    } 

    delete myBoard;
    // delete myFont;
}

void ChessGame::run() {
    InitWindow( SCREEN_WIDTH, SCREEN_HEIGHT, "Chess - DEV" ); 
    SetTargetFPS( 60 );
    loadTextures();

    while ( !WindowShouldClose() ) {
        inputHandeling();

        BeginDrawing();
            ClearBackground( WHITE );
            drawBoard();
            drawBoardPieces();
            if ( mySelectedSquare ) drawPossibleMoves();
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

void ChessGame::pressEvent() {
    // Get Square that was pressed
    Vector2 clicked_square = { -1.f, -1.f };
    for ( int i = 0; i < BOARD_WIDTH; i++ ) {
        if ( GetMouseX() <= (i + 1) * SQUARE_SIZE && GetMouseX() >= i * SQUARE_SIZE ) {
            clicked_square.x = i;
        }
        if ( GetMouseY() <= (i + 1) * SQUARE_SIZE && GetMouseY() >= i * SQUARE_SIZE ) {
            clicked_square.y = i;
        }
    }
    Square pressed_square = myBoard->getSquare( (int)clicked_square.x, (int)clicked_square.y );

    if ( Pieces::getColor( pressed_square.piece ) == myTurn ) {
        if ( mySelectedSquare ) delete mySelectedSquare;
        mySelectedSquare = new Square( pressed_square );
        return;
    }

    if ( !mySelectedSquare ) return;

    // Check for movement
    if ( ( pressed_square.piece == Pieces::NoPiece || Pieces::getColor( pressed_square.piece ) != myTurn ) && mySelectedSquare->piece != Pieces::NoPiece ) {
        // Try to move
        Move move( *mySelectedSquare, pressed_square );
        Logic logic( myBoard );
        if ( logic.moveIsLegal( move ) ) {
            myTurn = myTurn == Pieces::White ? Pieces::Black : Pieces::White;
            myBoard->playMove( move );
            TLog::log( "%s\n", move.getNotation().ascii() );
            delete mySelectedSquare;
            mySelectedSquare = 0L;
        }
    }
}

void ChessGame::inputHandeling() {
    if ( IsMouseButtonPressed( MOUSE_BUTTON_LEFT ) ) pressEvent();
}

void ChessGame::drawBoard() {
    const int text_size = 14;
    for ( int y = 0; y < BOARD_HEIGHT; y++ ) {
        for ( int x = 0; x < BOARD_WIDTH; x++ ) {
            Color rect_col = (x + y) % 2 == 0 ? DARKBLUE : WHITE;
            Color other_col = (x + y) % 2 != 0 ? DARKBLUE : WHITE;
            DrawRectangle( x * SQUARE_SIZE, y * SQUARE_SIZE, SQUARE_SIZE, SQUARE_SIZE, rect_col );

            // Draw letters for column
            char column = (char)(97 + x);
            const int x_col_text = ( x + 1 ) * SQUARE_SIZE - 12;
            const int y_col_text = 8 * SQUARE_SIZE - 12;
            DrawText( TString( column ).ascii(), x_col_text, y_col_text, text_size, other_col );
        }
        // Draw Numbers for row
        Color other_col = y % 2 != 0 ? WHITE : DARKBLUE;
        DrawText( TString( y + 1 ).ascii(), 12, ( y + 1 ) * SQUARE_SIZE - 22, text_size, y % 2 == 0 ? WHITE : DARKBLUE );
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

            DrawTexture( piece_tex, x * SQUARE_SIZE, y * SQUARE_SIZE, WHITE );
        }
    }
}

void ChessGame::drawMoveDot( int p_x, int p_y ) {
    Vector2 pos = {
        (float)p_x * (float)SQUARE_SIZE + (float)SQUARE_SIZE / 2,
        (float)p_y * (float)SQUARE_SIZE + (float)SQUARE_SIZE / 2
    };

    DrawCircleV( pos, MOVE_DOT_RADIUS, (Color){ 35, 35, 35, 170 } );
}

void ChessGame::drawPossibleMoves() {
    if ( !mySelectedSquare || mySelectedSquare->piece == Pieces::NoPiece ) return;
    Logic logic( myBoard );
    TList legals;
    logic.getLegals( &legals, *mySelectedSquare );

    for ( int i = 0; i < legals.count(); i++ ) {
        const Move * move = (Move *)legals.getValue( i );
        const Square dest_square = move->destSquare();
        drawMoveDot( dest_square.x, dest_square.y );
    }

    Move::freeMoves( legals );
}
