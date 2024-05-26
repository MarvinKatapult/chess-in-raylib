#include "tvector.hpp"
#include "math.h"

void Vector3::add( const Vector3 & p_other ) {
    x += p_other.x;
    y += p_other.y;
    z += p_other.z;
}

void Vector3::sub( const Vector3 & p_other ) {
    x -= p_other.x;
    y -= p_other.y;
    z -= p_other.z;
}

void Vector3::mult( float p_scale ) {
    x *= p_scale;
    y *= p_scale;
    z *= p_scale;
}

void Vector3::divide( float p_scale ) {
    if ( p_scale == 0.0f ) return;
    x /= p_scale;
    y /= p_scale;
    z /= p_scale;
}

void Vector3::normalize() {
    const float len = length();
    divide( len );
}

Vector3 Vector3::add( const Vector3 & p_first, const Vector3 & p_second ) {
    return Vector3( p_first.x + p_second.x, p_first.y + p_second.y, p_first.z + p_second.z );
}

Vector3 Vector3::sub( const Vector3 & p_first, const Vector3 & p_second ) {
    return Vector3( p_first.x - p_second.x, p_first.y - p_second.y, p_first.z - p_second.z );
}

Vector3 Vector3::mult( const Vector3 & p_vec, float p_scale ) {
    return Vector3( p_vec.x * p_scale, p_vec.y * p_scale, p_vec.z * p_scale );
}

Vector3 Vector3::divide( const Vector3 & p_vec, float p_scale ) {
    if ( p_scale == 0 ) return Vector3( 0, 0, 0 );
    return Vector3( p_vec.x / p_scale, p_vec.y / p_scale, p_vec.z / p_scale );
}

Vector3 Vector3::normalize( const Vector3 & p_vec ) {
    Vector3 ret( p_vec );
    ret.normalize();
    return ret;
}

Vector3 Vector3::crossProd( const Vector3 & p_other ) const {
    Vector3 ret;
    ret.x = y * p_other.z - z * p_other.y;
    ret.y = z * p_other.x - x * p_other.z;
    ret.z = x * p_other.y - y * p_other.x;
    return ret;
}

Vector3 Vector3::crossProd( const Vector3 & first, const Vector3 & second ) {
    return first.crossProd( second ); 
}

float Vector3::dotProd( const Vector3 & p_other ) const {
    return ( x * p_other.x + y * p_other.y + z * p_other.z );
}

float Vector3::dotProd( const Vector3 & p_first, const Vector3 & p_second ) {
    return p_first.dotProd( p_second );
}

float Vector3::length( void ) const {
    return sqrt( x * x + y * y + z * z );
}

void Vector3::operator+=( const Vector3 & p_other ) {
    add( p_other );
}

void Vector3::operator-=( const Vector3 & p_other ) {
    sub( p_other );
}

void Vector3::operator*=( float p_scale ) {
    mult( p_scale );
}

void Vector3::operator/=( float p_scale ) {
    divide( p_scale );
}

Vector3 Vector3::operator+( const Vector3 & p_other ) const {
    return Vector3::add( *this, p_other );
}

Vector3 Vector3::operator-( const Vector3 & p_other ) const {
    return Vector3::sub( *this, p_other );
}

Vector3 Vector3::operator*( float p_scale ) const {
    return Vector3::mult( *this, p_scale );
}

Vector3 Vector3::operator/( float p_scale ) const {
    return Vector3::divide( *this, p_scale );
}

void Vector3::operator=( const Vector3 & p_other ) {
    x = p_other.x;
    y = p_other.y;
    z = p_other.z;
}
