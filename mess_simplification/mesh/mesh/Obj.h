#ifndef OBJ_H
#define OBJ_H
#include"vertex.h"
#include"triangle.h"
#include<vector>
using namespace std;
class Obj
{
	public:
		Obj( char*);
		~Obj();
		void savetofile(char*);
		vector< Vertex* >  mvertex;
		vector< Triangle* >  mtriangle;
};
#endif