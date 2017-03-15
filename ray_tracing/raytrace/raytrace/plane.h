/**
 * normal vector is unit vector.
 * color: color1( cP ) -->(gradual change)--> color2( lim )
 */

#ifndef __PLANE_H__
#define __PLANE_H__

#include "object.h"

// implicit expression : N*P + D = 0
// P = (x, y, z), N is normal vector
class Plane : public Object
{
	public:
		Plane( const Vector3D& N, double D, const Color& c1,
			   const Color& c2, const Vector3D& cP, double lim );
		
		double intersect( const Ray& ray );
		Vector3D getNormalVector( const Vector3D& pos ) const;
		Color getColor( const Vector3D& pos ) const;
	
	private:
		double D, lim;
		Vector3D N;
		Color color1, color2;
		Vector3D cP;
};

#endif
