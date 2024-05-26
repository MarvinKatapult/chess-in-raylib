#pragma once

#define PRINT_VECTOR( VEC ) printf( "X:%f;Y:%f;Z:%f\n", VEC.x, VEC.y, VEC.z );
#define PRINT_VECTOR2( VEC ) printf( "X:%.2f;Y:%.2f;Z:%.2f\n", VEC.x, VEC.y, VEC.z );

struct Vector3 {
    
    public:

        /** Constructor **/
        Vector3( int _x = 0, int _y = 0, int _z = 0 ) : x( _x ), y( _y ), z( _z ) { }
        Vector3( const Vector3 & other ) : x( other.x ), y( other.y ), z( other.z ) { }

        /** Modification **/
        void add( const Vector3 & other );
        void sub( const Vector3 & other );
        void mult( float scale );
        void divide( float scale );
        void normalize( void );

        /** Utils **/
        Vector3 crossProd( const Vector3 & other ) const;
        float dotProd( const Vector3 & other ) const;
        float length( void ) const;

        static Vector3 add( const Vector3 & first, const Vector3 & second ); 
        static Vector3 sub( const Vector3 & first, const Vector3 & second ); 
        static Vector3 mult( const Vector3 & vec, float scale ); 
        static Vector3 divide( const Vector3 & vec, float scale ); 
        static Vector3 normalize( const Vector3 & vec );
        static Vector3 crossProd( const Vector3 & first, const Vector3 & second );
        static float dotProd( const Vector3 & first, const Vector3 & second );

        /** Operator **/
        Vector3 operator+( const Vector3 & other ) const;
        Vector3 operator-( const Vector3 & other ) const;
        Vector3 operator*( float scale ) const;
        Vector3 operator/( float scale ) const;

        void operator+=( const Vector3 & other );
        void operator-=( const Vector3 & other );
        void operator*=( float scale );
        void operator/=( float scale );

        void operator=( const Vector3 & other );

        float x, y, z;
};
