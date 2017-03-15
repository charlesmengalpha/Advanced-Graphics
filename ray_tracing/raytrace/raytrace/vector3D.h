#ifndef __VECTOR3D_H__
#define __VECTOR3D_H__

#include <cmath>

class Vector3D
{
	public:
		Vector3D( );
		Vector3D( double x, double y, double z );
		Vector3D( const Vector3D & );
		
		Vector3D& operator= ( const Vector3D& );
		Vector3D& operator+= ( const Vector3D& );
		Vector3D& operator-= ( const Vector3D& );
		Vector3D& operator*= ( double );
		Vector3D operator- ( ) const;
		
		double getX( ) const;
		double getY( ) const;
		double getZ( ) const;
		
		friend double operator* ( const Vector3D&, const Vector3D& );
		
		
		void set( double x, double y, double z );
		
		double len( ) const;
		Vector3D& normalize( );

	private:
		double x, y, z;
};
const Vector3D operator+ ( const Vector3D&, const Vector3D& );
const Vector3D operator- ( const Vector3D&, const Vector3D& );
const Vector3D operator* ( const Vector3D&, double );
const Vector3D operator* ( double, const Vector3D& );

#endif
