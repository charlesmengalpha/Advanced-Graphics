#include "StdAfx.h"
#include "ray_tracing.h"

Engine :: Engine( double X, double Y, double Z, int w, int h,
				  double x1, double y1, double x2, double y2 )
	: viewPoint( X, Y, Z ), width( w ), height( h ),
	  X1( x1 ), Y1( y1 ), X2( x2 ), Y2( y2 ) { }

Color Engine :: multiply( const Color& c1, const Color& c2 )
{
	return Color( c1.getX( ) * c2.getX( ), c1.getY( ) * c2.getY( ),
		          c1.getZ( ) * c2.getZ( ) );
}

Color Engine :: check( const Color& c )
{
	double x = c.getX( ), y = c.getY( ), z = c.getZ( );
	return Color( x > 1 ? 1 : x, y > 1 ? 1 : y, z > 1 ? 1 : z );
}
Engine::~Engine()
{
	delete[] buffer;
}
int Engine :: findNearest( const Ray& ray, double& dis )
{
	int k = 0, s;
	//光线两条，物体7个
	s = scene.lSize;
	for( int i = 0; i < s; ++i )
	{
		Vector3D v( scene.lList[i]->getPosition( ) - ray.getOrigin( ) );
		double x = v.len( ), y = v * ray.getDirection( ) - x;
		if( y < eps && y > -eps && x < dis )
			dis = x, k = - i - 1;
	}
	s = scene.oSize;
	for( int i = 0; i < s; ++i )
	{
		double x = scene.oList[i]->intersect( ray );
		if( x > 0 && x < dis )
			dis = x, k = i + 1;
	}
	return k;
}

Color Engine :: rayTracing( int depth, const Ray& ray, bool isOut, double dis )
{
	if( depth > depthLimit )
		return scene.ambient;  //如果到达递归深度，还木有返回颜色，就直接返回背景色

	double d = disLimit;
	
	// 找这条光线与物体的交点中离光线最近的物体
	int k = findNearest( ray, d );
	if( k == 0 ) return scene.ambient;   //如果木有找到交点，就返回背景色
	if( k < 0 ) return scene.lList[-k-1]->getIntensity( );//如果最近的交点是和光线相交，则返回光线的颜色
	
	dis += d;
	double attenuation = 1.0 - dis* scene.attenuation;
	//
	if( attenuation < eps )
		return scene.ambient;
	//最近的交点是和物体相交
	Object* nearest = scene.oList[k-1];
	const Material& material = nearest->getMaterial( );
	
	Vector3D p( ray.getOrigin( ) + ray.getDirection( ) * d );
	
	Color color( 0, 0, 0 );
	double amb = material.getAmbient( );
	if( amb > eps )
		//环境光
		color = multiply( nearest->getColor( p ), scene.ambient * amb );
	
	for( int i = 0; i < scene.lSize; ++i )
	{
		//考虑物体是否被其他物体遮挡产生了阴影
		Vector3D L( scene.lList[i]->getPosition( ) - p ); //点p指向光源
		double atten = attenuation - L.len( ) * scene.attenuation;
		if( atten < eps )
			continue;
		
		Color I( scene.lList[i]->getIntensity( ) ); //I表示入射光强
		
		bool shade = false;
		Ray r( p, L );
		for( int j = 0; j < scene.oSize; ++j )
		{
			double x = scene.oList[j]->intersect( r );
			if( x > 0 && x < L.len( ) )
			{
				shade = true;
				break;
			}
		}
		if( shade ) continue;
		
		// Phong reflection model  phong反射模型
		// diffuse reflection   漫反射 133页
		Vector3D N( nearest->getNormalVector( p ) ); //物理表面p处的法向量
		L.normalize( );
		double diff = material.getDiffuse( ); //漫反射系数变化量
		if( diff > eps )
		{
			double dot = N * L;
			if( dot > eps )
				color += multiply( I, diff * nearest->getColor( p ) * dot ) * atten;
		}
		// specular reflection镜面反射光
		//得到spec：镜面反射系数----高光光强
		double spec = material.getSpecular( );
		if( spec > eps )
		{
			//dot视线方向v*反射方向R
			double dot = ray.getDirection( ) * ( L - N * ( 2 * ( N * L ) ) );
			if( dot > eps )
				color += I * ( spec * pow( dot, material.getReflIndex( ) ) ) * atten;
		}
	}

	Vector3D N( nearest->getNormalVector( p ) );
	if( !isOut ) N = -N;
	Vector3D L( ray.getDirection( ) );
	// calculate reflection 反射方向
	double reflect = material.getSpecular( );
	if( reflect > eps )
	{
		Vector3D R( L - N * ( 2 * ( N * L ) ) );  //R 是反射方向
		color += rayTracing( depth + 1, Ray( p, R ), isOut, dis ) * reflect;
	}
	
	// calculate refraction  折射方向
	double refract = material.getTransmit( );
	if( refract > eps )
	{
		double idx;
		if( isOut ) idx = scene.refrIdx / material.getRefrIndex( );
		else idx = material.getRefrIndex( ) / scene.refrIdx;
		double cosI = -( L * N );
		double cosT2 = 1 - idx * idx * ( 1 - cosI * cosI );
		if( cosT2 > eps )
		{
			Vector3D T(	idx * L + ( idx * cosI - sqrt( cosT2 ) ) * N ); //T是折射方向 143页
			color += multiply( rayTracing( depth + 1, Ray( p + T * 1e-3, T ), !isOut, dis ),
				     nearest->getColor( p ) ) * refract;
		}
	}
	
	return check( color );
}
//
void Engine :: render( )
{
	buffer = new int[width * height + 5];
	
	int index = 0;
	double delY = ( Y2 - Y1 ) / height, delX = ( X2 - X1 ) / width;
	double curY = Y2, curX;
	for( int i = 0; i < height; ++i, curY -= delY )
	{
		curX = X1;
		for( int j = 0; j < width; ++j, curX += delX )
		{
			//从递归深度，【视点，目标点--这条光线】，确定这个像素点的颜色
			Color c = rayTracing( 0, Ray(viewPoint,Vector3D(curX,0,curY)-viewPoint), true, 0.0 );
			//乘以16和8，存到buffer里面
			buffer[index++] = ( ((int)( c.getZ( ) * 255 )) << 16 ) +
						      ( ((int)( c.getY( ) * 255 )) << 8 ) +
						      ((int)( c.getX( ) * 255 ));
		}
	}
}

void Engine :: focus( const Vector3D& focusPoint )
{
	int *buffer1( new int[width * height + 5] );

	int index = 0;
	double delY = ( Y2 - Y1 ) / height, delX = ( X2 - X1 ) / width;
	double curY = Y2, curX;
	for( int i = 0; i < height; ++i, curY -= delY )
	{
		curX = X1;
		for( int j = 0; j < width; ++j, curX += delX) 
		{
			Ray ray( viewPoint, Vector3D(curX,0,curY)-viewPoint );

			double dis = disLimit;
			findNearest( ray, dis );
			 
			Vector3D l( ray.getOrigin( ) + ray.getDirection( ) * dis - focusPoint );
			dis = l.len( );
			
			int k;
			if( dis > focusUnitDis * focusLimit )
				k = focusLimit;
			else k = (int) dis / focusUnitDis;

			int s = 0, R = 0, G = 0, B = 0;
			for( int ii = (i-k>0?i-k:0); ii < height && ii <= i+k; ++ii )
				for( int jj = (j-k>0?j-k:0); jj < width && jj <= j+k; ++jj )
				{
					int temp = buffer[ ii*width + jj ];
					B += temp >> 16;
					G += ( temp >> 8 ) & (( 1 << 8 ) - 1);
					R += temp & (( 1 << 8 ) - 1);
					++s;
				}
			
			buffer1[index++] = (( B / s ) << 16) + ((G / s) << 8) + R / s;
		}
	}

	buffer = buffer1;
	//delete[] buffer1;
}