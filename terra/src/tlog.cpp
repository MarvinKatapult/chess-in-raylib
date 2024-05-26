#include <tlog.hpp>

#include <stdio.h>
#include <stdarg.h>

TLog::TLog() {
    myLogLevel = Debug;
    myLogColor = Default;
    myFile = stdout;
}

TLog::TLog( TLogLevel p_log_level, TLogColor p_log_color ) 
    : myLogLevel( p_log_level ), myLogColor( p_log_color ) { 
    myFile = stdout;
}

TLog::TLog( TLogColor p_log_color ) {
    myLogLevel = Debug;
    myLogColor = p_log_color;
    myFile = stdout;
}

TLog::TLog( const char * p_file_path, bool p_clear_file, TLogColor p_log_color ) 
    : myLogColor( p_log_color ) {
    myLogLevel = Debug; 

    const char * mode = p_clear_file ? "w" : "a";
    myFile = fopen( p_file_path, mode );
}

TLog::~TLog() {
    if ( !myFile ) fclose( myFile );
}

bool TLog::print( const char * p_format, ... ) {

    setColor( myLogColor );
    va_list args;
    va_start( args, p_format );
    bool ret = vfprintf( myFile, p_format, args ) >= 0;
    va_end( args );

    resetColor();
    return ret;
}

bool TLog::print( TLogColor p_color, const char * p_format, ... ) {

    setColor( p_color );
    va_list args;
    va_start( args, p_format );
    bool ret = vfprintf( myFile, p_format, args ) >= 0;
    va_end( args );
    resetColor();

    return ret;
}

bool TLog::print( TLogLevel p_level, const char * p_format, ... ) {

    myLogLevel = p_level;
    setColorForLogLevel();

    va_list args;
    va_start( args, p_format );
    bool ret = vfprintf( myFile, p_format, args ) >= 0;
    va_end( args );
    resetColor();

    return ret;
}

bool TLog::log( const char * p_format, ... ) {

    va_list args;
    va_start( args, p_format );
    bool ret = vfprintf( stdout, p_format, args ) >= 0;
    va_end( args );

    return ret;
}

bool TLog::log( TLogColor p_color, const char * p_format, ... ) {
    TLog::setColor( p_color );

    va_list args;
    va_start( args, p_format );
    bool ret = vfprintf( stdout, p_format, args ) >= 0;
    va_end( args );

    resetColor();

    return ret;
}

void TLog::setColor( TLogColor p_color, bool p_is_std_err ) {
    FILE * file = p_is_std_err ? stderr : stdout;
    switch ( p_color ) {
        case Default:
            resetColor();
            break;
        case Black:
            fprintf( file, "\033[0;30m" );
            break;
        case Red:
            fprintf( file, "\033[0;31m" );
            break;
        case Green:
            fprintf( file, "\033[0;32m" );
            break;
        case Yellow:
            fprintf( file, "\033[0;33m" );
            break;
        case Blue:
            fprintf( file, "\033[0;34m" );
            break;
        case Purple:
            fprintf( file, "\033[0;35m" );
            break;
        case Cyan:
            fprintf( file, "\033[0;36m" );
            break;
        case White:
            fprintf( file, "\033[0;37m" );
            break;
    }
}

void TLog::resetColor( bool p_is_stderr ) {
    fprintf( p_is_stderr ? stderr : stdout, "\033[0m" );
}

void TLog::setColorForLogLevel() {
    switch ( myLogLevel ) {
        case Debug:
            setColor( Blue );
            break;
        case Warning:
            setColor( Yellow );
            break;
        case Error:
            setColor( Red );
            break;
    }
}
