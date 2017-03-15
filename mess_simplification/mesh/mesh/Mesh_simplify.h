#ifndef MESH_SIMPLIFY
#define MESH_SIMPLIFY
#include "Obj.h"

class Mesh_simplify
{
	public:
		static double edgecost(Vertex*, Vertex*);
		static void vertcost(Vertex*);
		static void choose_edge_collapse(Obj&, double);
		static void collapse(Vertex*, Vertex*);
};
#endif