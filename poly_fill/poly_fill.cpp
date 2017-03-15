#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"
#include <vector>
#include <list>
#include <math.h>
#include <algorithm>
#include <iostream>
using namespace cv;
using namespace std;

class _points{
public:
	int x,y; 
	_points(int _ox,int _oy) 
	{
		x = _ox;
	    y = _oy;
	}
	_points()
	{
		x = y = 0;
	}
};
vector<_points> _pts;

class edge{
public:	double x;
	double dx;
	int yMAX;
	int yMIN;
	int o_x;
	edge(int t_x, double t_dx, int t_yMAX, int t_yMIN, int t_o_x){
		x = t_x;
		dx = t_dx;
		yMAX = t_yMAX;
		yMIN = t_yMIN;
		o_x = t_o_x;
	}
};


Mat image0;
void drawpixel(int x, int y, uchar c)
{
	int height     = image0.rows;
	int width      = image0.cols;
	int step       = image0.step;
	int channels   = image0.channels();
	uchar* data    = (uchar *)image0.data;
	for (int k = 0; k < channels; k++)
	{
		data[y*step+x*channels+k] = c;
	}	
}
bool compare_edge(edge e_1, edge e_2)
{
	if (e_1.x < e_2.x)
		return true;
	else if (e_1.x > e_2.x) 
		return false;
	else
	    {
		if (e_1.o_x > e_2.o_x) 
			return false;
		else return true;
         }

}
void poly_fill()
{
	int x_MAX = -1, y_MAX = -1,x_MIN = 10000, y_MIN = 10000;
	for (int i = 0; i < _pts.size(); i++)
	{
		int x = _pts[i].x;
		int y = _pts[i].y;
		if (x > x_MAX)
			x_MAX = x;
		if (x < x_MIN)
			x_MIN = x;
		if (y < y_MIN)
			y_MIN = y;
		if (y > y_MAX)
			y_MAX = y;
		
	}
	list<edge> NET[2000];
	for (int i = 0; i < _pts.size(); i++)
	{
		_points node_1 = _pts[i];
		_points node_2 = _pts[(i+1)%_pts.size()];
		int x_1 = node_1.x, x_2 = node_2.x; 
		int y_1 = node_1.y,y_2 = node_2.y;
		if (y_1 > y_2){
			if (y_1 == y_2){
				NET[y_2].push_back(*(new edge((x_1+x_2)/2, 0, y_1, y_2, x_1)));
			}
			else{
				NET[y_2].push_back(*(new edge(x_2, (double)(x_1-x_2)/(y_1-y_2), y_1, y_2, x_1)));
			}
		}
		else
		{
			if (y_1 == y_2){
				NET[y_1].push_back(*(new edge((x_1+x_2)/2, 0, y_2, y_1, x_2)));
			}
			else{
				NET[y_1].push_back(*(new edge(x_1, (double)(x_1-x_2)/(y_1-y_2), y_2, y_1, x_2)));
			}
		}
	}
	list<edge> AET;
	AET.clear();
	for(int i = y_MIN; i <= y_MAX; i++){
		AET.splice(AET.begin(), NET[i]);
		AET.sort(compare_edge);
		list<int> cross;
		cross.clear();
		for(list<edge>::iterator A_it = AET.begin(); A_it != AET.end();){
			edge left_edge = *(A_it);
			int left = (int)(left_edge.x < 0 ? left_edge.x - 0.5 : left_edge.x + 0.5);
			list<edge>::iterator r_it = ++A_it;
			if (r_it == AET.end()){
				if(cross.size() % 2 == 1){
					cross.push_back(left);
				}
				break;
			}
			edge right_edge = *r_it;
			int right = (int)(right_edge.x < 0 ? right_edge.x - 0.5 : right_edge.x + 0.5);
			int y_1 = (left_edge.yMAX != i)?left_edge.yMAX:left_edge.yMIN;
			int y_2 = (right_edge.yMAX != i)?right_edge.yMAX:right_edge.yMIN;
			if (y_1 == i || y_2 == i){
				cross.push_back(left);
				list<edge>::iterator n_it = ++A_it;
				int y_3 = ((*n_it).yMAX != i)?(*n_it).yMAX:(*n_it).yMIN;
				if (n_it == AET.end() && (cross.size() % 2 == 1)){
					cross.push_back((*n_it).x);
					break;
				}
				else if ((y_1 - i) * (y_3 - i) < 0){
					cross.push_back((*n_it).x);
					cross.push_back((*n_it).x);
					A_it++;
				}
				else if ((y_1 - i) * (y_3 - i) > 0){
					cross.pop_back();
					A_it++;
				}
			}
			else if (left == right){
				if (y_1 > i && y_2 > i){
					cross.push_back(left);
					cross.push_back(left + 1);
					A_it++;
				}
				else if ((y_1 > i && y_2 < i) || (y_1 < i && y_2 > i)){
					cross.push_back(left);
					A_it++;
				}
				else{
					A_it++;
				}
			}
			else{
				cross.push_back(left);
			}
		}
		for (list<int>:: iterator it = cross.begin(); it != cross.end(); it++){
			int left = *it;
			int right = *(++it);
			for(int j = left; j < right; j++){
				drawpixel(j, i, 255);
			}
		}
		for(list<edge>::iterator A_it = AET.begin(); A_it != AET.end(); ){
			if ((*A_it).yMAX == i){
				A_it = AET.erase(A_it);
			}
			else{
				(*A_it).x = (*A_it).x + (*A_it).dx;
				A_it++;
			}
		}
	}
}

void IntegerBresenhamline(int x0, int y0, int x1, int y_1)
{
	int x, y, dx, dy, e;
	dx = x1 - x0;
	dy = y_1 - y0;
	x = x0;
	y = y0;

	if (x1==x0)
	{
		int _start = y0;
		int _end = y_1;
		if (y0>y_1)
		{
			_start = y_1;
			_end= y0;
		}

		for (int i = _start; i<=_end; i++)
		{
			drawpixel(x0,i,255);
		}
		return;
	}
	
	if (y_1==y0)
	{
		int _start = x0;
		int _end = x1;
		if (x0>x1)
		{
			_start = x1;
			_end= x0;
		}

		for (int i = _start; i<=_end; i++)
		{
			drawpixel(i,y0,255);
		}
		return;
	}

	if(dx == dy)
	{
		int _start = 0;
		int _end = x1 - x0;

		for (int i = _start; i<=_end; i++)
		{
			drawpixel(x0 + i,y0 + i,255);
		}
		return;
	}

	if(dx == -dy)
	{
		int _start = 0;
		int _end = x1 - x0;

		for (int i = _start; i<=_end; i++)
		{
			drawpixel(x0 + i,y0 - i,255);
		}
		return;
	}


	if(dy > 0 && dy < dx)
	{
		e = -dx;
		for(int i = 0; i <= dx; i++)
		{
			drawpixel(x,y, 255);
			x++;
			e += 2  * dy;
			if(e >= 0)
			{
				y++;
				e -= 2 * dx;
			}
		}
	}
	else if(dy < 0 && -dy < dx)
	{
		e = dx;
		for(int i = 0; i <= dx; i++)
		{
			drawpixel(x,y,255);
			x++;
			e += 2  * dy;
			if(e <= 0)
			{
				y--;
				e += 2 * dx;
			}
		}
		

	}
	else if(dy > 0 && dy > dx)
	{
		e = -dy;
		for(int i = 0; i <= dy; i++)
		{
			drawpixel(x,y,255);
			y++;
			e += 2  * dx;
			if(e >= 0)
			{
				x++;
				e -= 2 * dy;
			}
		}
		
	}
	else
	{
		e = -dy;
		for(int i = 0; i <= -dy; i++)
		{
			drawpixel(x,y,255);
			y--;
			e -= 2  * dx;
			if(e <= 0)
			{
				x++;
				e -= 2 * dy;
			}
		}

	}

}
static void onMouse( int event, int x, int y, int, void* )
{
    if( event == EVENT_LBUTTONDOWN ){
		int ch = image0.channels();
		int _x = image0.rows;
		int _y = image0.cols;
		_pts.push_back(_points(x,y));
		if (_pts.size()==1)
		{
			drawpixel(x,y,255);
		}
		else
		{
			int i1 = _pts.size()-1;
			int i2 = _pts.size()-2;
			if (_pts[i2].x<_pts[i1].x)
			{
				  IntegerBresenhamline(_pts[i2].x,_pts[i2].y,_pts[i1].x,_pts[i1].y);
			}
			else
			{

				 IntegerBresenhamline(_pts[i1].x,_pts[i1].y,_pts[i2].x,_pts[i2].y);		
			}
		}
		imshow("image",image0);
	}
	else if (event == EVENT_RBUTTONDOWN){
		poly_fill();
		imshow("image",image0);
		_pts.clear();
	}
	else return;
}

int main( int argc, char** argv )
{

    image0.create(480,640,CV_8UC3);
    if( image0.empty() )
    {
        cout << "Image empty. \n";
        return 0;
    }
    namedWindow( "image", 0 );
    setMouseCallback( "image", onMouse, 0 );
    for(;;)
    {
        imshow("image",image0);

        int c = waitKey(0);
        if( (c & 255) == 27 )
        {
            cout << "Exiting ...\n";
            break;
        }
		switch( (char)c )
		{
		case 'c':

			break;
        }
    }

    return 0;
}
