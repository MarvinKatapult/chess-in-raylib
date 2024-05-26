#pragma once

#include "tstring.hpp"

class TString;
typedef struct _IO_FILE FILE;

class TFile {

    public:

        enum FileMode {
            Read,
            Write
        };

        /** Constructor **/
        TFile( const TString & filename, FileMode mode = Read );
        ~TFile( void );

        /** Utils **/
        TString readLine( int line_number );
        int lineCount( void ) { return myLineCount; }
        TString path( void );

        static int calcLineCount( FILE * file );

    private:

        FILE * myFile;
        int myLineCount;
        TString * myFilepath;
};
