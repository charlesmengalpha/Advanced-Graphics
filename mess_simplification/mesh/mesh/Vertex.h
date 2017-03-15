#ifndef VERTEX_H
#define VERTEX_H
#include<vector>
#include"Vec3f.h"

using namespace std;
class Triangle;   //������
class Vertex
{
	public:
		friend bool operator< (Vertex, Vertex);
		Vertex(double, double, double);  //���������
		Vec3f coord; //һ��ֱ�ӿ��õĶ��㣬��Ҫ���꣬��Χ�Ķ�����Ϣ����Χ����������Ϣ
		Vertex* targetv;//����һ���ڵ���б����ݻ����������
		bool effective;
		const Vec3f& getCoord();

		vector<Vertex* > adjancent_vert;
		vector<Triangle*> adjancent_trig;
		double cost;
		
};
#endif