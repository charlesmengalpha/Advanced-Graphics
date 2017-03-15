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
	//输入视点坐标、屏幕的宽高、宽高的坐标
	Engine engine( X, Y, Z, Width, Height, X1, Y1, X2, Y2 );
	//使用光线追踪，找到每一个像素点的颜色值，存入buffer。
	engine.render( );
	//绘制每一个像素点的图像
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
