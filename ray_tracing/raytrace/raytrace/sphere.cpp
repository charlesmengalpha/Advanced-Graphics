#include "StdAfx.h"
#include "sphere.h"
#include<cmath>
#define pi 3.141592653
Sphere :: Sphere( const Vector3D& cen, double rad, const Color& c )
	: center( cen ), radius( rad ), color( c ) { }

double Sphere :: intersect( const Ray& ray )
{
	Vector3D v = center - ray.getOrigin( );
	double oc2 = v * v;
	double ca = v * ray.getDirection( );
	if( ca < eps ) return FAIL;
	
	double hc2 = radius * radius + ca * ca - oc2;
	if( hc2 < eps ) return FAIL;
	
	double hc = sqrt( hc2 ), d1 = ca - hc, d2 = ca + hc;
	if( d1 < eps )
		return d2;
	return d1;
}

Vector3D Sphere :: getNormalVector( const Vector3D& pos ) const
{
	Vector3D N( pos - center );
	N.normalize( );
	return N;
}

Color Sphere :: getColor( const Vector3D& pos ) const
{
	/*double xx,yy,r,theta,fai;
	double x = pos.getX(), y = pos.getY(), z = pos.getZ();
	r = sqrt( double(x*x +y*y + z*z));
	theta = pi - acos(pos.getZ()/r);
	fai = pi/2 - atan(pos.getY()/pos.getX());

	xx =theta/pi;
	yy =fai/pi;
	if(x==0 && y==0)
		xx=0,yy=0;
	
	int value;
	value = (int)(floor(xx*8)+floor(yy*8));
	//value = abs((xx-yy)*10000);
	if (value%2)
		return Color(0.6, 0.6,0.6);
	else
		return color;
	//*/return this->color;

}