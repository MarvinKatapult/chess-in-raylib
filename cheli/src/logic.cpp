#include "logic.hpp"

#include "board.hpp"
#include "square.hpp"
#include "piece.hpp"
#include "move.hpp"

#include "tlog.hpp"
#include "tlist.hpp"

#include <ctype.h>
#include <math.h>

#define GET_PAWN_Y_DIRECTION( X )   ( Pieces::getColor( X ) == Pieces::White ? -1 : 1 )
#define COORD_IS_IN_BOUNDS( X )     ( X >= 0 && X <= 7 )
#define WHITE_PAWN_START_ROW    6
#define BLACK_PAWN_START_ROW    1

Logic::Logic( Board * p_board ) : myBoard( p_board ) { }

TList Logic::getLegals( bool p_check_for_checks ) const {
    TList moves;

    for ( int y = 0; y < BOARD_HEIGHT; y++ ) {
        for ( int x = 0; x < BOARD_WIDTH; x++ ) {
            getLegals( &moves, x, y );        
        }
    }
    
    if ( p_check_for_checks ) {
        removeIllegalMoves( &moves ); 
    }
    return moves;
}

void Logic::removeIllegalMoves( TList * p_list ) const {
    if ( !p_list ) return;

    for ( int i = p_list->count() - 1; i >= 0; i-- ) {
        Move * move = (Move *)p_list->getValue( i );
        if ( !move ) return;

        Board board( *myBoard );
        board.playMove( *move );

        Logic logic( &board );
        Pieces::PieceColor color_that_moves = Pieces::getColor( move->piece() ); 
        if ( logic.isCheck() == color_that_moves ) {
            delete( (Move *)p_list->getValue( i ) );
            p_list->remove( i );
        }
    }
}

void Logic::getLegals( TList * p_legals, const Square & p_square ) const {
    if ( !p_legals ) return;

    const Piece piece = p_square.piece;
    switch( piece ) {
        case Pieces::BlackPawn:
        case Pieces::WhitePawn:
            getLegalsPawn( p_legals, p_square );
            break;
        case Pieces::BlackBishop:
        case Pieces::WhiteBishop:
            getLegalsBishop( p_legals, p_square );
            break;
        case Pieces::BlackRook:
        case Pieces::WhiteRook:
            getLegalsRook( p_legals, p_square );
            break;
        case Pieces::BlackQueen:
        case Pieces::WhiteQueen:
            getLegalsQueen( p_legals, p_square );
            break;
        case Pieces::BlackKing:
        case Pieces::WhiteKing:
            getLegalsKing( p_legals, p_square );
            break;
        case Pieces::BlackKnight:
        case Pieces::WhiteKnight:
            getLegalsKnight( p_legals, p_square );
            break;
    }
}

void Logic::getLegals( TList * p_legals, int p_x, int p_y ) const { 
    if ( !p_legals ) return;

    Square square = myBoard->getSquare( p_x, p_y );
    getLegals( p_legals, square );
}

void Logic::getLegalsPawn( TList * p_list, const Square & p_start_square ) const {
    if ( !p_list ) return; 

    getLegalsPawnMove( p_list, p_start_square );
    getLegalsPawnCapture( p_list, p_start_square );
    getLegalsPawnEnpassant( p_list, p_start_square );
}

void Logic::getLegalsBishop( TList * p_list, const Square & p_start_square ) const {
    if ( !p_list ) return;
    getLegalsCommon( p_list, p_start_square, Left,    Up   );
    getLegalsCommon( p_list, p_start_square, Right,   Up   );
    getLegalsCommon( p_list, p_start_square, Left,    Down );
    getLegalsCommon( p_list, p_start_square, Right,   Down );
}

void Logic::getLegalsRook( TList * p_list, const Square & p_start_square ) const {
    if ( !p_list ) return;
    getLegalsCommon( p_list, p_start_square, Left,    VNone );
    getLegalsCommon( p_list, p_start_square, Right,   VNone );
    getLegalsCommon( p_list, p_start_square, HNone,   Up    );
    getLegalsCommon( p_list, p_start_square, HNone,   Down  );
}

void Logic::getLegalsQueen( TList * p_list, const Square & p_start_square ) const {
    if ( !p_list ) return;
    getLegalsCommon( p_list, p_start_square, Left,    VNone );
    getLegalsCommon( p_list, p_start_square, Right,   VNone );
    getLegalsCommon( p_list, p_start_square, HNone,   Up    );
    getLegalsCommon( p_list, p_start_square, HNone,   Down  );
    getLegalsCommon( p_list, p_start_square, Left,    Up    );
    getLegalsCommon( p_list, p_start_square, Right,   Up    );
    getLegalsCommon( p_list, p_start_square, Left,    Down  );
    getLegalsCommon( p_list, p_start_square, Right,   Down  );
}

void Logic::getLegalsKing( TList * p_list, const Square & p_start_square ) const {
    if ( !p_list ) return;
    getLegalsCommon( p_list, p_start_square, Left,    VNone, 1 );
    getLegalsCommon( p_list, p_start_square, Right,   VNone, 1 );
    getLegalsCommon( p_list, p_start_square, HNone,   Up   , 1 );
    getLegalsCommon( p_list, p_start_square, HNone,   Down , 1 );
    getLegalsCommon( p_list, p_start_square, Left,    Down , 1 );
    getLegalsCommon( p_list, p_start_square, Right,   Down , 1 );
    getLegalsCommon( p_list, p_start_square, Left,    Up,    1 );
    getLegalsCommon( p_list, p_start_square, Right,   Up,    1 );
}

void Logic::getLegalsKnight( TList * p_list, const Square & p_start_square ) const {
    if ( !p_list ) return;

    const Piece knight = p_start_square.piece;

    for ( int x = -2; x <= 2; x++ ) {
        for ( int y = -2; y <= 2; y++ ) {
            const int square_x = p_start_square.x + x;
            const int square_y = p_start_square.y + y;
            if ( abs( x ) == abs( y )
              || x == 0 || y == 0 
              || !COORD_IS_IN_BOUNDS( square_x ) 
              || !COORD_IS_IN_BOUNDS( square_y ) ) continue;
            Square dest_square = myBoard->getSquare( square_x, square_y );

            if ( !squareHasAlly( dest_square, Pieces::getColor( knight ) ) ) {
                Move * move = new Move( p_start_square, dest_square );
                p_list->append( (void *)move );
            }
        }
    }
}

void Logic::getLegalsPawnMove( TList * p_list, const Square & p_start_square ) const {
    if ( !p_list ) return;

    Piece pawn = p_start_square.piece;
    const int move_dir = GET_PAWN_Y_DIRECTION( pawn );

    // One Square movement
    Square dest_one_square = myBoard->getSquare( p_start_square.x, p_start_square.y + move_dir );
    bool can_move_one_square = false;
    if ( dest_one_square.isFree() ) {
        Move * move = new Move( p_start_square, dest_one_square );
        p_list->append( (void *)move );
        can_move_one_square = true;
    }
    if ( !can_move_one_square ) return;

    // Two Square movement
    Pieces::PieceColor color = Pieces::getColor( pawn );
    const int start_row = color == Pieces::White ? WHITE_PAWN_START_ROW : BLACK_PAWN_START_ROW;
    bool pawn_on_starting_row = p_start_square.y == start_row;
    if ( !pawn_on_starting_row ) return; 

    Square dest_two_square = myBoard->getSquare( p_start_square.x, p_start_square.y + move_dir * 2 );
    if ( pawn_on_starting_row && dest_two_square.isFree() ) {
        Move * move = new Move( p_start_square, dest_two_square );
        p_list->append( (void *)move );
    }
}

void Logic::getLegalsPawnCapture( TList * p_list, const Square & p_start_square ) const {
    if ( !p_list ) return;
    
    const Piece pawn = p_start_square.piece;

    const int start_x = p_start_square.x;
    const int start_y = p_start_square.y;
    const int move_dir_y = GET_PAWN_Y_DIRECTION( pawn );

    if ( start_x > 0 ) {
        // Capture to the left    
        Square dest_square = myBoard->getSquare( start_x - 1, start_y + move_dir_y );
        checkPawnCapture( p_list, p_start_square, dest_square );
    }

    if ( start_x < 7 ) {
        // Capture to the right
        Square dest_square = myBoard->getSquare( start_x + 1, start_y + move_dir_y );
        checkPawnCapture( p_list, p_start_square, dest_square );
    }
} 

void Logic::checkPawnCapture( TList * p_list, const Square & p_start_square, const Square & p_dest_square ) const {
    if ( !p_list ) return;

    
    const Piece pawn = p_start_square.piece;
    if ( squareHasEnemy( p_dest_square, Pieces::getColor( pawn ) ) ) {
        Move * move = new Move( p_start_square, p_dest_square );
        p_list->append( (void *)move );
    }
}

void Logic::getLegalsPawnEnpassant( TList * p_list, const Square & p_start_square ) const {
    if ( !p_list ) return;
    const int start_x = p_start_square.x;
    const int start_y = p_start_square.y;
    const Pieces::PieceColor pawn_color = Pieces::getColor( p_start_square.piece );

    // Pawn has to be on y = 4 || y = 3
    bool white_pawn_correct_row = start_y == BLACK_PAWN_START_ROW + 2;
    bool black_pawn_correct_row = start_y == WHITE_PAWN_START_ROW - 2;
    bool pawn_is_correct_row = ( white_pawn_correct_row && pawn_color == Pieces::White ) || ( black_pawn_correct_row && pawn_color == Pieces::Black );
    if ( !pawn_is_correct_row ) return;

    const int enemy_pawn_start_row = pawn_color == Pieces::White ? BLACK_PAWN_START_ROW : WHITE_PAWN_START_ROW;
    bool left_enpassant = checkEnpassant( p_start_square, enemy_pawn_start_row, Left );
    bool right_enpassant = checkEnpassant( p_start_square, enemy_pawn_start_row, Right );
    bool found = left_enpassant || right_enpassant;
    if ( found ) {
        HorizontalDirection dir = left_enpassant ? Left : Right;
        const Square dest_square = myBoard->getSquare( start_x + dir, start_y + GET_PAWN_Y_DIRECTION( p_start_square.piece ) );
        Move * new_move = new Move( p_start_square, dest_square );
        p_list->append( (void *)new_move );
    }
}

bool Logic::checkEnpassant( const Square & p_start_square, int p_enemy_pawn_start_row, Logic::HorizontalDirection p_dir ) const {
    const int start_x = p_start_square.x;
    const int start_y = p_start_square.y;
    const int other_pawn_x = start_x + p_dir;
    if ( !COORD_IS_IN_BOUNDS( other_pawn_x ) ) return false;

    Square other_pawn_sq = myBoard->getSquare( other_pawn_x, start_y );
    // Check if there is enemy pawn on neighboring square
    if ( tolower( other_pawn_sq.piece ) == 'p' && squareHasEnemy( other_pawn_sq, Pieces::getColor( p_start_square.piece ) ) ) {
        // Check if last move was double pawn movement
        const Move * last_move = myBoard->getLastMove();
        if ( !last_move ) return false;
        bool last_move_was_double_pawn = last_move->startY() == p_enemy_pawn_start_row 
                                      && last_move->destY() == p_start_square.y
                                      && last_move->destX() == other_pawn_x;
                                    
        return last_move_was_double_pawn;
    }

    return false;
}

void Logic::getLegalsCommon( TList * p_list, const Square & p_start_square, HorizontalDirection p_horizontal, VerticalDirection p_vertical, int p_range ) const {
    if ( !p_list ) return;
    
    const Piece piece = p_start_square.piece;

    int i = 1;
    do {
        const int x = p_start_square.x + p_horizontal * i;
        const int y = p_start_square.y + p_vertical * i;
        if ( !COORD_IS_IN_BOUNDS( x ) || !COORD_IS_IN_BOUNDS( y ) ) break;

        Square dest_square = myBoard->getSquare( x, y );

        // Check for ally
        if ( squareHasAlly( dest_square, Pieces::getColor( piece ) ) ) return;
        
        // Add move
        Move * move = new Move( p_start_square, dest_square );
        p_list->append( (void *)move );

        // Check for enemy
        if ( squareHasEnemy( dest_square, Pieces::getColor( piece ) ) ) break;
    } while( i++ < p_range );
} 

Pieces::PieceColor Logic::isCheck() const {
    TList legals = this->getLegals( false );

    for ( int i = 0; i < legals.count(); i++ ) {
        Move * move = (Move *)legals.getValue( i );
        if ( !move ) return Pieces::NoColor;
        Square dest_square = move->destSquare();
        Piece piece = dest_square.piece;

        if ( piece == Pieces::BlackKing || piece == Pieces::WhiteKing ) {
            Move::freeMoves( legals );
            return Pieces::getColor( piece );
        }
    }

    Move::freeMoves( legals );
    return Pieces::NoColor;
}

Pieces::PieceColor Logic::isCheckmate() const {
    Pieces::PieceColor in_check = isCheck();
    if ( in_check == Pieces::NoColor ) return Pieces::NoColor;

    TList legals = this->getLegals();
    TList moves_for_in_check = Move::getMoves( legals, in_check );

    Pieces::PieceColor checkmate = Pieces::NoColor;
    if ( moves_for_in_check.count() == 0 ) {
        checkmate = in_check; 
    }
    
    Move::freeMoves( legals );
    return checkmate;
}

bool Logic::squareHasEnemy( const Square & p_square, Pieces::PieceColor p_color ) {
    Piece piece = p_square.piece;

    if ( piece == Pieces::NoPiece ) return false;
    return Pieces::getColor( piece ) != p_color;
}

bool Logic::squareHasAlly( const Square & p_square, Pieces::PieceColor p_color ) {
    Piece piece = p_square.piece;

    if ( piece == Pieces::NoPiece ) return false;
    return Pieces::getColor( piece ) == p_color;
}
