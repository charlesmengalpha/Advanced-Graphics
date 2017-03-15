#ifndef VERTEX_H
#define VERTEX_H
#include<vector>
#include"Vec3f.h"

using namespace std;
class Triangle;   //类的组合
class Vertex
{
	public:
		friend bool operator< (Vertex, Vertex);
		Vertex(double, double, double);  //顶点的坐标
		Vec3f coord; //一个直接可用的顶点，需要坐标，周围的顶点信息，周围的三角形信息
		Vertex* targetv;//和另一个节点进行边塌陷活动，完成网格简化
		bool effective;
		const Vec3f& getCoord();

		vector<Vertex* > adjancent_vert;
		vector<Triangle*> adjancent_trig;
		double cost;
		
};
#endif