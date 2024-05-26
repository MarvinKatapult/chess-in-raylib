
#include "board.hpp"
#include "logic.hpp"
#include "move.hpp"

#include "tlog.hpp"
#include "tstring.hpp"
#include "tlist.hpp"

int main() {

    TLog log;

    // Board board( "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR" );
    // Board board( "r7/2K5/8/8/8/8/8/8" );
    // Board board( "8/Rpk5/8/8/8/8/8/8" );
    // Board board( "8/1p6/8/2P5/8/8/8/8" );
    // Board board( "8/8/8/1pP5/8/8/8/8" );
    Board board( "2k5/6N1/8/3N1B2/8/1R6/6K1/8" );

    // Move move( board.getSquare( 1, 1 ), board.getSquare( 1, 3 ) );
    // board.playMove( move );

    Logic logic( &board );
    TList list = logic.getLegals();

    log.print( "Momentanes Board:\n" );
    board.printBoard();

    TString str;
    Pieces::PieceColor checkmate = logic.isCheckmate();
    if ( checkmate == Pieces::White ) str = "White";
    else if ( checkmate == Pieces::Black ) str = "Black";
    else if ( checkmate == Pieces::NoColor ) str = "No side";

    TLog::log( "%s is checkmate\n", str.ascii() );

    Move::freeMoves( list );
    return 0;
}
