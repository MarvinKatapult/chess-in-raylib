#pragma once

#include "tstring.hpp"

class THash {

    public:

        
        /** Utils **/
        /** These hashfunctions were implemented with the information of http://www.cse.yorku.ca/~oz/hash.html **/
        static unsigned long sdbmHash( const TString & str );
        static unsigned long djb2Hash( const TString & str );

        /* This will just call djb2Hash */
        static unsigned long hash( const TString & str );

        static unsigned long checkSum( const TString & str );

};
