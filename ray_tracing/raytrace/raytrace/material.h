/**
 * arguments of material  model     range   default
 * ambient                Phong             0
 * diffuse reflectance    Phong             0
 * specular reflectance   Phong             0
 * reflective index       Phong     1~2000  100
 * transmissivity         Whitted           0
 * refractive index                         1
 */

#ifndef __MATERIAL_H__
#define __MATERIAL_H__

#include "common.h"

class Material
{
	public:
		Material( );
		
		double getAmbient( ) const;
		double getDiffuse( ) const;
		double getSpecular( ) const;
		double getReflIndex( ) const;
		double getTransmit( ) const;
		double getRefrIndex( ) const;
		
		void setAmbient( double );
		void setDiffuse( double );
		void setSpecular( double );
		void setReflIndex( double );
		void setTransmit( double );
		void setRefrIndex( double );
		
	private:
		//背景色、漫反射、镜面反射、反射深度、传输、折射深度
		double ambient, diffuse, specular, reflIndex, transmit, refrIndex;
};

#endif
