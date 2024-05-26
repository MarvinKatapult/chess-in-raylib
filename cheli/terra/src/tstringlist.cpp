#include "tstringlist.hpp"

TStringList::~TStringList() {
    for ( int i = 0; i < count(); i++ ) {
        delete( (TString *)TList::getValue( i ) );
    }

    TList::~TList();
}

/** Modification **/
void TStringList::append( const TString & p_str ) {
    TString * new_str = new TString( p_str );
    TList::append( (void *)new_str );
}

void TStringList::update( int p_position, const TString & p_str ) {
    TString * new_str = new TString( p_str );
    TList::update( p_position, (void *)new_str );
}

void TStringList::remove( int p_position ) {
    TString * str = (TString *)TList::getValue( p_position );
    delete( str );
    TList::remove( p_position );
}

TString TStringList::getValue( int p_position ) const {
    return *( (TString *)TList::getValue( p_position ) );
}

void TStringList::operator+=( const TString & p_str ) {
    append( p_str );
}

TString TStringList::operator[]( int p_index ) {
    return getValue( p_index );
}
