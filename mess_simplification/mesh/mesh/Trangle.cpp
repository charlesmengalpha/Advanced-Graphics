#include"StdAfx.h"
#include<iostream>

using namespace std;
#include"Triangle.h"
Triangle::Triangle(Vertex* v0, Vertex* v1, Vertex* v2):effective(true)  //一个三角形有3个顶点
{
		vertex[0] = v0;
		vertex[1] = v1;
		vertex[2] = v2;
		double x1,y1,z1,x2,y2,z2;
		Vec3f tp1(v0->getCoord() - v1->getCoord()), tp2(v0->getCoord() - v2->getCoord());
		x1 =tp1.getX();
		y1 =tp1.getY();
		z1 =tp1.getZ();
		x2 =tp2.getX();
		y2 =tp2.getY();
		z2 =tp2.getZ();
		norvet.set(y1*z2-y2*z1,z1*x2-z2*x1, x1*y2-y1*x2 );
		norvet.normal();

}
bool Triangle::existVert(Vertex* v)
{
	if(vertex[0]==v || vertex[1]==v || vertex[2] ==v )
			return true;
	return false;
}
void Triangle::replaceVert(Vertex* v1, Vertex* v2)
{
		if(vertex[0] == v1)
			vertex[0] = v2;
		else if(vertex[1] == v1)
			vertex[1] = v2;
		else if(vertex[2] == v1)
			vertex[2] = v2;
}