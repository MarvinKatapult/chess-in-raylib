#include "thash.hpp"

unsigned long THash::hash( const TString & p_str ) {
    return djb2Hash( p_str );
}

unsigned long THash::sdbmHash( const TString & p_str ) {
    unsigned long hash = 0;
    
    for ( int i = 0; i < p_str.length(); i++ ) {
        char c = p_str[i];
        hash = c + (hash << 6) + (hash << 16) - hash;
    }

    return hash;
}

unsigned long THash::djb2Hash( const TString & p_str ) {
    unsigned long hash = 5381;

    for ( int i = 0; i < p_str.length(); i++ ) {
        char c = p_str[i];
        hash = c + (hash << 6) + (hash << 16) - hash;
    }

    return hash;
}

unsigned long THash::checkSum( const TString & p_str ) {
    unsigned long hash = 0;
    for ( int i = 0; i < p_str.length(); i++ ) {
        hash += p_str[i]; 
    }

    return hash;
}
