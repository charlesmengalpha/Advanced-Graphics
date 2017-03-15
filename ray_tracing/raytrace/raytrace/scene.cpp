#include "StdAfx.h"
#include "scene.h"

Scene :: Scene( )
	: lSize( 2 ), oSize( 5 ), refrIdx( 1.0 ), attenuation( 1e-2 ), ambient(0.2, 0.2, 0.2 )
{
	
	lList = new Light* [ lSize ];
	lList[0] = new Light( Vector3D( 15, -5, 20 ), Color( 1, 0.5, 0 )*2 );
	lList[1] = new Light( Vector3D( -15, -5, 20 ), Color( 0.2, 0, 1 )*2 );
	
	
	Material* material;
	oList = new Object* [ oSize ];
	int k = 0;

	oList[k] = new Sphere( Vector3D( 3, -2,  0  ), 1,Color( 0.5, 0.2, 0.1 ) );
	material = &( oList[k]->getMaterial( ) );
	material->setDiffuse( 0.8 );
	material->setSpecular( 0.5 );
	material->setReflIndex( 50 );
	material->setTransmit( 0.7 );
	material->setRefrIndex( 0.99 );
	++k;

	oList[k] = new Sphere( Vector3D( 0, 3,  -0.2  ), 0.8,Color( 0.2, 1, 0 ) );
	material = &( oList[k]->getMaterial( ) );
	material->setDiffuse( 0.8 );
	material->setSpecular( 0.5 );
	material->setReflIndex( 50 );
	material->setTransmit( 0.7 );
	material->setRefrIndex( 0.99 );
	++k;
	
	oList[k] = new Sphere( Vector3D( -2, -2,  -0.4  ), 0.6,Color( 1, 1, 0.5 ) );
	material = &( oList[k]->getMaterial( ) );
	material->setDiffuse( 0.8 );
	material->setSpecular( 0.5 );
	material->setReflIndex( 50 );
	material->setTransmit( 0.7 );
	material->setRefrIndex( 0.99 );
	++k;
	
	oList[k] = new Sphere( Vector3D( -2, 2,  -0.6 ), 0.4,Color( 0, 0.5, 0 ) );
	material = &( oList[k]->getMaterial( ) );
	material->setDiffuse( 0.6 );
	material->setSpecular( 0.5 );
	material->setReflIndex( 50 );
	material->setTransmit( 0.7 );
	material->setRefrIndex( 0.99 );
	++k;
	
	/*oList[k] = new Sphere(Vector3D( 2, 2,  -0.5  ), 0.5,Color( 1, 0, 0.5 ) );
	material = &( oList[k]->getMaterial( ) );
	material->setDiffuse( 0.8 );
	material->setSpecular( 0.5 );
	++k;
	
	oList[k] = new Sphere( Vector3D( 3, 3, -0.5 ),0.5 ,Color( 0.8, 1, 1 ) );
	material = &( oList[k]->getMaterial( ) );
	material->setDiffuse( 0.8 );
	material->setSpecular( 0.5 );
	++k;*/
	
	oList[k] = new Plane( Vector3D( 0, 0, 1 ), 1,Color( 0.2,0.7,0.1 ), Color( 0.9,0.8,0.2 ),Vector3D( 0, 1, -1 ), 6 );
	material = &( oList[k]->getMaterial( ) );
	material->setDiffuse( 0.8 );
	material->setSpecular( 0.5 );
	material->setReflIndex( 50 );
	material->setTransmit( 0.7 );
	material->setRefrIndex( 0.99 );
	++k;
}

Scene :: ~Scene( )
{
	for( int i = 0; i < lSize; ++i )
		delete lList[i];
	delete[] lList;
	
	for( int i = 0; i < oSize; ++i )
		delete oList[i];
	delete[] oList;
}
