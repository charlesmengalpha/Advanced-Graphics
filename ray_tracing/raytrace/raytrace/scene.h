/**
 * lSize/lList        light
 * oSize/oList        object
 * refrIdx            refraction index of medium
 * attenuation        attenuation coefficient of light
 *                    expr : color * ( 1 - atten * dis )
 * ambient            ambient light
 */

#ifndef __SCENE_H__
#define __SCENE_H__

#include "light.h"
#include "sphere.h"
#include "plane.h"

class Scene
{
	public:
		Scene( );
		~Scene( );
		
		int lSize, oSize;
		Light** lList;
		Object** oList;
		
		double refrIdx, attenuation;
		Color ambient;
};

#endif
