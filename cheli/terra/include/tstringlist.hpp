#pragma once

#include "tlist.hpp"
#include "tstring.hpp"

#define PRINT_TSTRINGLIST( STR )    for ( int i = 0; i < STR.count(); i++ ) printf( "%s\n", STR[i].ascii() )

class TStringList : public TList {
  
    public:

        /** Deconstructor **/
        ~TStringList( void );

        /** Modification **/
        void append( const TString & str );
        void update( int position, const TString & str );
        void remove( int position );

        /** Utils **/
        TString getValue( int position ) const;

        /** Operator **/
        void operator+=( const TString & str );
        TString operator[]( int index );
};
