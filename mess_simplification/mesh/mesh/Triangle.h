#ifndef TRIANGLE_H
#define TRIANGLE_H
#include"Vertex.h"
class Triangle
{
	public:
		Triangle(Vertex* , Vertex* , Vertex*);  //һ����������3������
		bool existVert(Vertex*);
		void replaceVert(Vertex*, Vertex*);
		Vertex* vertex[3];
		Vec3f norvet;
		bool effective;
};
#endif