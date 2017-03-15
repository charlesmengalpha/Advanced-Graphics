#include "StdAfx.h"
#include "plane.h"
#include<cmath>

Plane :: Plane( const Vector3D& n, double d, const Color& c1,const Color& c2, const Vector3D& P, double l )
	: N( n ), D( d ), color1( c1 ), color2( c2 ), cP( P ), lim( l )
{
	N.normalize( );
}

double Plane :: intersect( const Ray& ray )
{
	double t = N * ray.getDirection( );
	if( t < eps && t > -eps ) return FAIL;
	
	t = -( D + N * ray.getOrigin( ) ) / t;
	if( t > eps )
		return t;
	return FAIL;
}

Vector3D Plane :: getNormalVector( const Vector3D& pos ) const
{
	return N;
}

Color Plane :: getColor( const Vector3D& pos ) const
{
	//¹ý³ÌÎÆÀí

	double xx,yy;
	xx=pos.getX()-pos.getZ()/sqrt(2.0);
	yy=pos.getY()-pos.getZ()/sqrt(2.0);
	int value;
	value = (int)(floor(xx)+floor(yy));
	//value = abs((xx-yy)*10000);
	if (value%2)
		return Color(0.2, 0.2,0.2);
	else
		return Color(0,0,0);
}
