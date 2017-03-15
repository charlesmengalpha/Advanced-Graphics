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
	//��������������7��
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
		return scene.ambient;  //�������ݹ���ȣ���ľ�з�����ɫ����ֱ�ӷ��ر���ɫ

	double d = disLimit;
	
	// ����������������Ľ�������������������
	int k = findNearest( ray, d );
	if( k == 0 ) return scene.ambient;   //���ľ���ҵ����㣬�ͷ��ر���ɫ
	if( k < 0 ) return scene.lList[-k-1]->getIntensity( );//�������Ľ����Ǻ͹����ཻ���򷵻ع��ߵ���ɫ
	
	dis += d;
	double attenuation = 1.0 - dis* scene.attenuation;
	//
	if( attenuation < eps )
		return scene.ambient;
	//����Ľ����Ǻ������ཻ
	Object* nearest = scene.oList[k-1];
	const Material& material = nearest->getMaterial( );
	
	Vector3D p( ray.getOrigin( ) + ray.getDirection( ) * d );
	
	Color color( 0, 0, 0 );
	double amb = material.getAmbient( );
	if( amb > eps )
		//������
		color = multiply( nearest->getColor( p ), scene.ambient * amb );
	
	for( int i = 0; i < scene.lSize; ++i )
	{
		//���������Ƿ����������ڵ���������Ӱ
		Vector3D L( scene.lList[i]->getPosition( ) - p ); //��pָ���Դ
		double atten = attenuation - L.len( ) * scene.attenuation;
		if( atten < eps )
			continue;
		
		Color I( scene.lList[i]->getIntensity( ) ); //I��ʾ�����ǿ
		
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
		
		// Phong reflection model  phong����ģ��
		// diffuse reflection   ������ 133ҳ
		Vector3D N( nearest->getNormalVector( p ) ); //�������p���ķ�����
		L.normalize( );
		double diff = material.getDiffuse( ); //������ϵ���仯��
		if( diff > eps )
		{
			double dot = N * L;
			if( dot > eps )
				color += multiply( I, diff * nearest->getColor( p ) * dot ) * atten;
		}
		// specular reflection���淴���
		//�õ�spec�����淴��ϵ��----�߹��ǿ
		double spec = material.getSpecular( );
		if( spec > eps )
		{
			//dot���߷���v*���䷽��R
			double dot = ray.getDirection( ) * ( L - N * ( 2 * ( N * L ) ) );
			if( dot > eps )
				color += I * ( spec * pow( dot, material.getReflIndex( ) ) ) * atten;
		}
	}

	Vector3D N( nearest->getNormalVector( p ) );
	if( !isOut ) N = -N;
	Vector3D L( ray.getDirection( ) );
	// calculate reflection ���䷽��
	double reflect = material.getSpecular( );
	if( reflect > eps )
	{
		Vector3D R( L - N * ( 2 * ( N * L ) ) );  //R �Ƿ��䷽��
		color += rayTracing( depth + 1, Ray( p, R ), isOut, dis ) * reflect;
	}
	
	// calculate refraction  ���䷽��
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
			Vector3D T(	idx * L + ( idx * cosI - sqrt( cosT2 ) ) * N ); //T�����䷽�� 143ҳ
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
			//�ӵݹ���ȣ����ӵ㣬Ŀ���--�������ߡ���ȷ��������ص����ɫ
			Color c = rayTracing( 0, Ray(viewPoint,Vector3D(curX,0,curY)-viewPoint), true, 0.0 );
			//����16��8���浽buffer����
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