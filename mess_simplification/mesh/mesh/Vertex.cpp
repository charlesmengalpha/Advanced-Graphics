#include "StdAfx.h"
#include"Vertex.h"

Vertex::Vertex(double x, double y, double z):coord(x,y,z),effective(true),cost(0.0)
{
}
const Vec3f& Vertex::getCoord()  //得到这点的坐标
{
		return this->coord;
}