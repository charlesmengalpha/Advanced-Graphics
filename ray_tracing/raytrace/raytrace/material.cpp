#include "StdAfx.h"
#include "material.h"

Material :: Material( )
	: ambient( 0.0 ), diffuse( 0.0 ),
	  specular( 0.0 ), reflIndex( 100.0 ), transmit( 0.0 ), refrIndex( 1 ) { }

double Material :: getAmbient( ) const
{
	return ambient;
}

double Material :: getDiffuse( ) const
{
	return diffuse;
}

double Material :: getSpecular( ) const
{
	return specular;
}
//·´ÉäÖ¸Êý
double Material :: getReflIndex( ) const
{
	return reflIndex;
}

double Material :: getTransmit( ) const
{
	return transmit;
}

double Material :: getRefrIndex( ) const
{
	return refrIndex;
}

void Material :: setAmbient( double amb )
{
	ambient = amb;
}

void Material :: setDiffuse( double dif )
{
	diffuse = dif;
}

void Material :: setReflIndex( double rldx )
{
	reflIndex = rldx;
}

void Material :: setTransmit( double trans )
{
	transmit = trans;
}
void Material :: setSpecular( double spe )
{
	specular = spe;
}

void Material :: setRefrIndex( double rrdx )
{
	refrIndex = rrdx;
}
