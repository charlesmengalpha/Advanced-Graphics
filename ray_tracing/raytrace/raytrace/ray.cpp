#include "StdAfx.h"
#include "ray.h"

Ray :: Ray( const Vector3D& ori, const Vector3D& dir )
	: origin( ori ), direction( dir )
{
	direction.normalize( );
}

Vector3D Ray :: getOrigin( ) const
{
	return origin;
}

void Ray :: setOrigin( const Vector3D& ori )
{
	origin = ori;
}

void Ray :: setDirection( const Vector3D& dir )
{
	direction = dir;
	direction.normalize( );
}
Vector3D Ray :: getDirection( ) const
{
	return direction;
}