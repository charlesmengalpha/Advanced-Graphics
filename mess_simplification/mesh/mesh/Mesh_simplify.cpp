#include"stdafx.h"
#include"Mesh_simplify.h"
#include<vector>
#include<list>
#include<fstream>
#include<iostream>
using namespace std;
//两个顶点尽可能对第一个顶点周围的三角形都造成较小影响情况下，对周围三角的最大影响值
double Mesh_simplify::edgecost(Vertex* v1, Vertex* v2)
{
	Vec3f ttv(v1->getCoord() - v2->getCoord());
	double edgelen = ttv.length();
	double value = 0.0;
	vector<Triangle* > trg;
	int size = v1->adjancent_trig.size(), size1 = 0;
	double min = 0.0, tm = 0.0;
	for(int i = 0; i <size; i++ )
	{
		if( v1->adjancent_trig[i]->effective==true  && v1->adjancent_trig[i]->existVert(v2))
			trg.push_back(v1->adjancent_trig[i]);
	}
	size1 = trg.size();
	for(int i = 0; i <size; i++ )
	{
		if(v1->adjancent_trig[i]->effective == true)
		{
			min = 1.0;
			for( int j = 0; j<size1; j++ )
			{
				//表示一个u为顶点的三角形 与 有u和v的三角形【v1-vn】相差最小vm 
				tm = (1.0 - v1->adjancent_trig[i]->norvet * trg[j]->norvet)*0.5; 
				if(tm < min)
					min = tm;
			}
			//找出相差最小的里面最大的【因为每一个三角形都要考虑】尽可能小的差异里面最大的影响值 
			if( min > value )
				value = min;
		}
	}
	return edgelen * value; //边越长，影响越大，所以我们直接线性相乘 
}
//计算一个顶点的cost
void Mesh_simplify::vertcost(Vertex* v1)
{
	if(v1->adjancent_vert.size() == 0)
	{
		v1->cost = -1.0;
		v1->targetv = NULL; //指针可以为空哦哦
		//cout << "NULL 3"<< endl;
		return; //光棍顶点一个，也就木有什么利用价值
	}
	//在寻找你要塌陷的目标之前，先将其置为空,你的目标就是所有和你有共边的顶点
	v1->targetv = NULL;
	int size = v1->adjancent_vert.size();
	double stand = 0.0;
	for(int i = 0; i<size; i++ )
	{
		if(v1->adjancent_vert[i]->effective==true)
		{
			stand = edgecost(v1, v1->adjancent_vert[i]);
			if(stand <  v1->cost || v1->targetv == NULL)   //重点啊啊！
			{
				v1->targetv = v1->adjancent_vert[i];
				v1->cost  = stand;
			}
		}
	}
}
void Mesh_simplify::collapse(Vertex* v1, Vertex* v2)
{
	v1->effective=false;
	if(v2==NULL)
		return;
	int size;
	size=v1->adjancent_trig.size();
	for( int i =0 ; i<size; i++ )
	{
		if(v1->adjancent_trig[i]->effective == true)
		{
			if(v1->adjancent_trig[i]->existVert(v2))
				v1->adjancent_trig[i]->effective = false;
			else
			{
				v1->adjancent_trig[i]->replaceVert(v1, v2);
				v2->adjancent_trig.push_back(v1->adjancent_trig[i]);
			}
		}
	}
	size = v1->adjancent_vert.size();
	for(int i = 0; i<size; i++)
	{
		if(v1->adjancent_vert[i]->effective == true)
		{
			Mesh_simplify::vertcost(v1->adjancent_vert[i]);
			if(v1->adjancent_vert[i] != v2)
			{
				v1->adjancent_vert[i]->adjancent_vert.push_back(v2);
				v2->adjancent_vert.push_back(v1->adjancent_vert[i]);
			}
		}
	}
}
void Mesh_simplify::choose_edge_collapse(Obj &obj, double ratio)
{
	list<Vertex* > colv;
	int num = (int) (obj.mvertex.size()*(1-ratio));
	int size = obj.mvertex.size();
	for( int i = 0; i < size; i++)
	{
		if(obj.mvertex[i]->effective == false)
			continue;
		else
		{
			//计算所有点的cost来进行筛选需要塌陷哪些边
			Mesh_simplify::vertcost(obj.mvertex[i]);
			colv.push_back(obj.mvertex[i]);
		}
	}
	for(int i = 0; i<num; i++)
	{
		if(colv.size()==0)
			break;
		list<Vertex* >::iterator index;
		list<Vertex* >::iterator min = colv.begin();
		for(index = colv.begin(); index!=colv.end(); ++ index)
		{
			if((**index).cost <(**min).cost)
				min = index;
		}
		Mesh_simplify::collapse(*min, (**min).targetv);
		colv.erase(min);
	}
	
}

