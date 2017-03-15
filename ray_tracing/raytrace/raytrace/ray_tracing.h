#ifndef __RAY_TRACING_H__
#define __RAY_TRACING_H__

#include "common.h"
#include "scene.h"

#include <cmath>

#define disLimit    1e20
#define depthLimit  3

#define focusUnitDis 1
#define focusLimit   10

class Engine
{
	public:
		Engine( double X, double Y, double Z, int Width, int Height,
			   double X1, double Y1, double X2, double Y2 );
		~Engine();
		
		void render( );//‰÷»æ
		void focus( const Vector3D& focusPoint );
		
		int* buffer;
		
	private:
		Color multiply( const Color&, const Color& );
		Color check( const Color& );
		int findNearest( const Ray& ray, double& dis );
		
		Color rayTracing( int depth, const Ray& ray, bool isOut, double dis );
		
		int width, height;
		double X1, Y1, X2, Y2;
		Vector3D viewPoint;
		Scene scene;
};

#endif
