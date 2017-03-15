
#include <vector>
#include <iostream>
#include <math.h>
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"
using namespace cv;
using namespace std;
class _points
{
public:
	int x; 
	int y;
	_points() {x = y = 0;}
	_points(int _ox,int _oy) {x = _ox; y = _oy;}
};

vector<_points> _pts;

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
void MPoint_line(int x0,int y0, int x1, int y1)
{
	int a,b,d,d1,d2,dx,dy,x,y;
	 a = y0-y1;b = x1-x0;
	 d = 2*a+b;
	 d1 = 2*a;
	 d2 = 2*(a+b);
	 dx =dy = 1;
	if(y0 >= y1){dy = -1;}
	else{dy = 1;}
    if(x0 > x1){
		swap(x0,x1);
		swap(y0,y1);
	}
	drawpixel(x0, y0, 255);
	drawpixel(x1, y1, 255);
	if(abs(a) <= abs(b)){
		d = 2*a + (dy*b);
		d1 = 2*a;
		d2 = 2*(a+(dy*b));
		x = x0;y = y0;
	    if(x1 == x0)
     	{int _Start = y0;int _End = y0;
	    	if(y0 > y1){_Start = y1;_End = y0;}
	    	for(int i = _Start; i <= _End; i++)
	    	{	drawpixel(x0, i, 255);}
			return;
     	}
		if(y0 <= y1)
		{
  	        while(x < x1)
			{
		        if(d < 0){
			        x++;y++;d += d2;
         		}
				else{
	         		x++;d += d1;
				}
		        drawpixel(x, y, 255);
        	}
		}
		else
		{
			while(x < x1)
			{
				if(d < 0){ x++;d += d1; }
				else{x++;y--;d += d2; }   
				drawpixel(x, y, 255);
			}
		}
	}
	else
	{
		x = x0;	y = y0;
		d = a+(dy*2*b);
		d1 = dy*2*b;
		d2 = 2*(a+(b*dy));
		if(y0 == y1)
		{
			int _Start = x0;
			int _End = x1;
			for (int i = _Start; i<=_End; i++)
			{drawpixel(i,y0,255);}
		}
		if(y0 <= y1)
		{
		   while( y < y1)
		   {
			   if(d < 0){ y++;   d += d1;}
			   else{y++;x++;d += d2;
		     	}
			    drawpixel(x, y, 255);
		    }
		}
		else
		{
			while(y > y1)
			{
				if(d < 0){y--;x++;d += d2;}
				else
				{y--;d += d1;}
     			drawpixel(x, y, 255);
			}
		}
	}
}

static void onMouse( int event, int x, int y, int, void* )
{
    if( event != EVENT_LBUTTONDOWN )
        return;
	int chan = img_1.channels();
	int _x = img_1.rows;
	int _y = img_1.cols;
	_pts.push_back(_ptsoints(x,y));
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
			 MPoint_line(_pts[i2].x,_pts[i2].y,_pts[i1].x,_pts[i1].y);
		}
		else
		{

			MPoint_line(_pts[i1].x,_pts[i1].y,_pts[i2].x,_pts[i2].y);		
		}
	}
	imshow("image",img_1);
}


int main( int argc, char** argv )
{

    img_1.create(480,640,CV_8UC3);
    if( img_1.empty() )
    {
        cout << "Empty image  \n";
        return 0;
    }
    namedWindow( "Image", 0 );
    setMouseCallback( "Image", onMouse, 0 );
    for(;;)
    {
        imshow("Image",img_1);

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


