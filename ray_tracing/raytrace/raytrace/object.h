/**
 * when intersect fail, return -1
 */

#ifndef __OBJECT_H__
#define __OBJECT_H__

#include "common.h"
#include "material.h"

#define FAIL -1

class Object
{
	public:
		virtual double intersect( const Ray& ) = 0;
		virtual Vector3D getNormalVector( const Vector3D& pos ) const = 0;
		virtual Color getColor( const Vector3D& pos ) const = 0;
		
		Material& getMaterial( );
		
	private:
		Material material;
};

#endif
