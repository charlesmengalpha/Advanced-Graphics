/**
 * direction is unit vector.
 */

#ifndef __RAY_H__
#define __RAY_H__
#include "common.h"

class Ray
{
	public:
		Ray( const Vector3D& origin, const Vector3D& direction );
		
		Vector3D getOrigin( ) const;
		Vector3D getDirection( ) const;
		
		void setOrigin( const Vector3D& origin );
		void setDirection( const Vector3D& direction );
		
	private:
		Vector3D origin, direction;
};

#endif
