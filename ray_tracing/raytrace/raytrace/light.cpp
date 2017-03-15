#include "StdAfx.h"
#include "light.h"

Light :: Light( const Vector3D& pos, const Color& inte )
	: position( pos ), intensity( inte ) { }

Vector3D Light :: getPosition( ) const
{
	return position;
}

Color Light :: getIntensity( ) const
{
	return intensity;
}
