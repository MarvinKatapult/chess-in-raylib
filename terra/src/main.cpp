
#include "tlist.hpp"
#include "tlog.hpp"

int main() {

    TList list;

    int nums[] = { 1, 2, 3, 4, 5, 6, 7, 8, 9 };
    for ( int i = 0; i < 9; i++ ) list.append( nums + i );

    TLog::log( "Count:%d\n", list.count() );
    list.remove( 3 );
    list.remove( 6 ); 
    list.remove( 6 ); 
    list.remove( 5 ); 
    TLog::log( "Count:%d\n", list.count() );

    TList list2;
    list2 = list;

    TLog::log( "Count:%d\n", list2.count() );
    list2.remove( 3 );
    TLog::log( "Count:%d\n", list2.count() );

    return 0;
}
