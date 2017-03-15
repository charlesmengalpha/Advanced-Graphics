#ifndef __LIGHT_H__
#define __LIGHT_H__

#include "common.h"

class Light
{
	public:
		Light( const Vector3D& position, const Color& intensity );
		
		Vector3D getPosition( ) const;
		Color getIntensity( ) const;
				
	private:
		Vector3D position;
		Color intensity;
};

#endif
