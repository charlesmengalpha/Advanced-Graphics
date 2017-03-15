#include "stdafx.h"
#include "opencv2\opencv.hpp"
#include "ray_tracing.h"

// argument of screen
#define Width 640
#define Height 480

#define X1 -5.0
#define Y1 -5.0
#define X2 5.0
#define Y2 5.0

// position of viewpoint
#define X 1.0
#define Y 10.0
#define Z 1.0

int main( int argc, char* argv[] )
{
	cv::Mat img( Height, Width, CV_8UC3 ); 
	//�����ӵ����ꡢ��Ļ�Ŀ�ߡ���ߵ�����
	Engine engine( X, Y, Z, Width, Height, X1, Y1, X2, Y2 );
	//ʹ�ù���׷�٣��ҵ�ÿһ�����ص����ɫֵ������buffer��
	engine.render( );
	//����ÿһ�����ص��ͼ��
	int k = 0;
	for( int i = 0; i < img.rows; ++i )
		for( int j = 0; j < img.cols; ++j )
		{
			int temp = engine.buffer[k++];
			img.ptr<uchar>(i)[j*3] = temp >> 16;
			img.ptr<uchar>(i)[j*3 + 1] = ( temp >> 8 ) & (( 1 << 8 ) - 1);
			img.ptr<uchar>(i)[j*3 + 2] = temp & (( 1 << 8 ) - 1);
		}
		
	//cv::imwrite("ray_tracing.png", img);

	
	engine.focus( Vector3D( 0, 0, 0 ) ); // focus point is ( 0, 0, 0 )
	
	k = 0;
	for( int i = 0; i < img.rows; ++i )
		for( int j = 0; j < img.cols; ++j )
		{
			int temp = engine.buffer[k++];
			img.ptr<uchar>(i)[j*3] = temp >> 16;
			img.ptr<uchar>(i)[j*3 + 1] = ( temp >> 8 ) & (( 1 << 8 ) - 1);
			img.ptr<uchar>(i)[j*3 + 2] = temp & (( 1 << 8 ) - 1);
		}
		cv::imshow("show",img);
		cv::waitKey(0);
	//cv::imwrite("ray_tracing_focus.png", img);
	system("pause");
	return 0;
}
