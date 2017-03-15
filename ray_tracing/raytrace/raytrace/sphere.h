#ifndef __SPHERE_H__
#define __SPHERE_H__

#include "object.h"

#include <cmath>

class Sphere : public Object
{
	public:
		Sphere( const Vector3D& center, double radius, const Color& color );
		
		double intersect( const Ray& ray );
		Vector3D getNormalVector( const Vector3D& pos ) const;
		Color getColor( const Vector3D& pos ) const;
	
	private:
		double radius;
		Vector3D center;
		Color color;
};

#endif
