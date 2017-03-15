#include"stdafx.h"
#include"Mesh_simplify.h"
#include<vector>
#include<list>
#include<fstream>
#include<iostream>
using namespace std;
//�������㾡���ܶԵ�һ��������Χ�������ζ���ɽ�СӰ������£�����Χ���ǵ����Ӱ��ֵ
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
				//��ʾһ��uΪ����������� �� ��u��v�������Ρ�v1-vn�������Сvm 
				tm = (1.0 - v1->adjancent_trig[i]->norvet * trg[j]->norvet)*0.5; 
				if(tm < min)
					min = tm;
			}
			//�ҳ������С���������ġ���Ϊÿһ�������ζ�Ҫ���ǡ�������С�Ĳ�����������Ӱ��ֵ 
			if( min > value )
				value = min;
		}
	}
	return edgelen * value; //��Խ����Ӱ��Խ����������ֱ��������� 
}
//����һ�������cost
void Mesh_simplify::vertcost(Vertex* v1)
{
	if(v1->adjancent_vert.size() == 0)
	{
		v1->cost = -1.0;
		v1->targetv = NULL; //ָ�����Ϊ��ŶŶ
		//cout << "NULL 3"<< endl;
		return; //�������һ����Ҳ��ľ��ʲô���ü�ֵ
	}
	//��Ѱ����Ҫ���ݵ�Ŀ��֮ǰ���Ƚ�����Ϊ��,���Ŀ��������к����й��ߵĶ���
	v1->targetv = NULL;
	int size = v1->adjancent_vert.size();
	double stand = 0.0;
	for(int i = 0; i<size; i++ )
	{
		if(v1->adjancent_vert[i]->effective==true)
		{
			stand = edgecost(v1, v1->adjancent_vert[i]);
			if(stand <  v1->cost || v1->targetv == NULL)   //�ص㰡����
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
			//�������е��cost������ɸѡ��Ҫ������Щ��
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

