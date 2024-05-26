#include "tstring.hpp"

#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>

#define MAX_LONG_LENGTH  20

TString::TString() {
    initializeBuffer();
}

TString::TString( const char * p_str ) {
    initializeBuffer();
    copyCString( p_str );
}

TString::TString( const unsigned char * p_str ) {
    initializeBuffer();
    copyCString( (const char *)p_str );
}

TString::TString( char p_character ) {
    myBuffer = (char *)malloc( sizeof( char * ) * 2 );
    myBuffer[0] = p_character;
    myBuffer[1] = '\0';
}

TString::TString( int p_number ) {
    myBuffer = convertNumberToString( p_number );
}

TString::TString( long p_number ) {
    myBuffer = convertNumberToString( p_number );
}

TString::TString( const TString & p_str ) {
    initializeBuffer();
    copyCString( p_str.ascii() );
}

TString::~TString() {
    free( myBuffer );
}

TString & TString::clear() {
    free( myBuffer );
    myBuffer = (char *)malloc( sizeof( char * ) );
    *myBuffer = '\0';

    return  *this;
}

void TString::initializeBuffer() {
    myBuffer = (char *)malloc( sizeof( char * ) );
    myBuffer[0] = '\0';
}

char * TString::convertNumberToString( long p_number ) {
    char * buffer = (char *)malloc( MAX_LONG_LENGTH * sizeof( char ) );
    if ( !buffer ) return NULL;
    snprintf( buffer, 12, "%ld", p_number );

    return buffer;
}

TString & TString::append( const TString & p_str ) {
    const int start_length = strlen( myBuffer );
    const int end_length = p_str.length() + start_length;

    char * buffer = (char *)malloc( sizeof( char * ) * end_length + 1 );
    strcpy( buffer, myBuffer );
    
    strcat( buffer, p_str.buffer() );

    free( myBuffer );
    myBuffer = buffer;

    return *this;
}

TString & TString::prepend( const TString & p_str ) {
    const int start_length = strlen( myBuffer );
    const int end_length = p_str.length() + start_length;

    char * buffer = (char *)malloc( sizeof( char * ) * end_length + 1 );
    strcpy( buffer, p_str.buffer() );
    
    strcat( buffer, myBuffer );

    free( myBuffer );
    myBuffer = buffer;

    return *this;
}

TString & TString::remove( const TString & p_str, bool p_only_first ) {
    char * pos;
    int len = strlen( p_str.ascii() );
    
    while ( ( pos = strstr( buffer(), p_str.buffer() ) ) != 0L ) {
        memmove( pos, pos + len, strlen( pos + len ) + 1 );
        if ( p_only_first ) break;
    }

    return *this;
}

TString & TString::insert( int p_position, const TString & p_str ) {
    const int new_length = length() + p_str.length() + 1;
    char * buffer = (char *)malloc( sizeof( char * ) * new_length );

    for ( int i = 0; i < p_position; i++ ) {
        buffer[i] = myBuffer[i];
    }

    int start = p_position;
    for ( int i = start; i < p_str.length() + start; i++ ) {
        buffer[i] = p_str[i - start];
    }

    start = p_position + p_str.length();
    for ( int i = start; i < start + length() - p_position; i++ ) {
        buffer[i] = myBuffer[i - p_str.length()];
    }  
    buffer[new_length] = '\0';

    free( myBuffer );
    myBuffer = buffer;

    return *this;
}

TString & TString::replace( const TString & p_r_str, const TString & p_d_str ) {
    for ( int i = find( p_r_str ); i != -1; i = find( p_r_str ) ) {
        remove( p_r_str, true );
        insert( i, p_d_str );
    }

    return *this;
}

const char * TString::ascii() const {
    return (const char *)myBuffer;
}

int TString::toInt() const {
    return strtol( ascii(), 0L, 10 );
}

int TString::length() const {
    unsigned int count = 0;
    char * current = myBuffer;
    while( *current != '\0' ) {
        current++;
        count++;
    }
    return count;
}

TString TString::toLower() const {
    char * buffer = (char *)malloc( sizeof( myBuffer ) * length() + 1 );
    for ( int i = 0; i < length() + 1; i++ ) {
        buffer[i] = tolower( myBuffer[i] ); 
        if ( i == length() ) buffer[i] = '\0';
    }

    return TString( buffer );
}

TString TString::toUpper() const {
    char * buffer = (char *)malloc( sizeof( myBuffer ) * length() + 1 );
    for ( int i = 0; i < length() + 1; i++ ) {
        buffer[i] = toupper( myBuffer[i] ); 
        if ( i == length() ) buffer[i] = '\0';
    }

    return TString( buffer );
}

bool TString::contains( const TString & p_str ) const {
    return strstr( myBuffer, p_str.ascii() ) != NULL;
}

int TString::find( const TString & p_str ) const {
    char * found = strstr( myBuffer, p_str.ascii() );
    if ( !found ) return -1;

    return found - myBuffer;
}

int TString::find( int p_position, const TString & p_str ) const {
    if ( p_position > length() ) return -1;
    if ( p_position < 0 ) p_position = 0;

    char * buffer = myBuffer + p_position;

    char * found = strstr( buffer, p_str.ascii() );
    if ( !found ) return -1;

    return found - myBuffer;
}

char TString::character( int p_position ) const {
    if ( p_position > length() ) return '\0';
    return myBuffer[p_position];
}

void TString::copyCString( const char * p_str ) {
    free( myBuffer );

    myBuffer = (char *)malloc( sizeof( char * ) * strlen( p_str ) + 1 );
    if ( !myBuffer ) return;
    strcpy( myBuffer, p_str );
}

void TString::copyUnsignedCString( const unsigned char * p_str ) {
    free( myBuffer );

    myBuffer = (char *)malloc( sizeof( char * ) * strlen( (const char *)p_str ) + 1 );
    if ( !myBuffer ) return;
    memcpy( myBuffer, p_str, strlen( (const char *)p_str ) );
}

void TString::operator+=( const TString & p_str ) {
    append( p_str );
}

TString TString::operator+( const TString & p_str ) {
    TString ret( myBuffer );
    ret.append( p_str );
    return ret;
}

bool TString::operator==( const TString & p_str ) const {
    return strcmp( ascii(), p_str.ascii() ) == 0;
}

void TString::operator=( const TString & p_str ) {
    copyCString( p_str.ascii() );
}

char TString::operator[]( int p_index ) const {
    return character( p_index );
}
