#include "tfile.hpp"

#include <stdio.h>
#include <stdlib.h>

#include <limits.h>

TFile::TFile( const TString & p_filename, FileMode p_mode ) {
    myFile = fopen( p_filename.ascii(), p_mode == Read ? "r" : "a" );
    myLineCount = calcLineCount( myFile );
    myFilepath = new TString( p_filename );
}

TFile::~TFile() {
    fclose( myFile );
    delete myFilepath;
}

TString TFile::readLine( int p_line_number ) {
    if ( p_line_number <= 0 || p_line_number > lineCount() ) return "";
    char buffer[1024];
    for ( int i = 0; i < p_line_number; i++ ) {
        if ( !fgets( buffer, sizeof( buffer ), myFile ) ) break;
    }
    fseek( myFile, 0, SEEK_SET );
    return TString( buffer ).remove( "\n" );
}

TString TFile::path() {
    char absolute_path[PATH_MAX];
    return realpath( myFilepath->ascii(), absolute_path );
}

int TFile::calcLineCount( FILE * p_file ) {
    int count = 0;
    char buffer[1024];
    while( fgets( buffer, sizeof( buffer ), p_file) != NULL ) {
        count++;
    }
    fseek( p_file, 0, SEEK_SET );
    return count;
}
