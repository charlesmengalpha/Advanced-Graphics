#include "StdAfx.h"
#include "vector3D.h"

// member functions
Vector3D :: Vector3D( )
	: x(0.0), y(0.0), z(0.0) { }

Vector3D :: Vector3D( double a, double b, double c )
	: x(a), y(b), z(c) { }

Vector3D :: Vector3D( const Vector3D & rhs )
	: x( rhs.x ), y( rhs.y ), z( rhs.z ) { }

Vector3D& Vector3D :: operator= ( const Vector3D& rhs )
{
	x = rhs.x; y = rhs.y; z = rhs.z;
	return *this;
}

Vector3D& Vector3D :: operator+= ( const Vector3D& rhs )
{
	x += rhs.x; y += rhs.y; z += rhs.z;
	return *this;
}

Vector3D& Vector3D :: operator-= ( const Vector3D& rhs )
{
	x -= rhs.x; y -= rhs.y; z -= rhs.z;
	return *this;
}

Vector3D& Vector3D :: operator*= ( double rhs )
{
	x *= rhs; y *= rhs; z *= rhs;
	return *this;
}

Vector3D Vector3D :: operator- ( ) const
{
	return Vector3D( -x, -y, -z );
}

double Vector3D :: getX( ) const
{
	return x;
}

double Vector3D :: getY( ) const
{
	return y;
}

double Vector3D :: getZ( ) const
{
	return z;
}

void Vector3D :: set( double X, double Y, double Z )
{
	x = X; y = Y; z = Z;
}

double Vector3D :: len( ) const
{
	return sqrt( x * x + y * y + z * z );
}

Vector3D& Vector3D :: normalize( )
{
	*this *= 1 / len( );
	return *this;
}

// nonmember functions
const Vector3D operator+ ( const Vector3D& lhs, const Vector3D& rhs )
{
	Vector3D ret( lhs );
	ret += rhs;
	return ret;
}

const Vector3D operator- ( const Vector3D& lhs, const Vector3D& rhs )
{
	Vector3D ret( lhs );
	ret -= rhs;
	return ret;
}

const Vector3D operator* ( const Vector3D& lhs, double rhs )
{
	Vector3D ret( lhs );
	ret *= rhs;
	return ret;
}

const Vector3D operator* ( double lhs, const Vector3D& rhs )
{
	Vector3D ret( rhs );
	ret *= lhs;
	return ret;
}

double operator* ( const Vector3D& lhs, const Vector3D& rhs )
{
	return lhs.x * rhs.x + lhs.y * rhs.y + lhs.z * rhs.z;
}
