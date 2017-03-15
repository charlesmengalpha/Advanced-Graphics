#include "stdafx.h"
#include"Obj.h"
#include<fstream>
#include<iostream>
#include<stdio.h>
#include<map>

using namespace std;
//map是一种关联容器，定义了一种数据结构，类似于查表，每一个数据都有自己的键值，可以通过键值查找和排序
//pair是单个数据对的操作，pair是struct型的，通过first，second来访问数据，用.
//map里面的数据都是pair型的，通过insert()来插入元素(pair型)
#include<set>
//首先创建这一对数据，然后在map里面寻找，如果可以找到，就不把它加入map中，因为后来迭代的map里面进行边塌陷。
#define findadj( a, b ){\
	pair<Vertex*, Vertex*>  pair_vert(make_pair(a,b));\
	index = alledge.find(pair_vert);\
	if(index == alledge.end()){\
	alledge.insert(pair_vert);\
	a->adjancent_vert.push_back(b);}}

Obj::Obj(char* filename)
{
	set<pair<Vertex*, Vertex*>>   alledge;
	FILE* fin = fopen( filename, "r");
	char str[305];
	double x=0,y=0,z=0;
	while(true)
	{
		if(fscanf(fin, "%s", str) == EOF)
			break;
		if(str[0]=='#')
			fgets(str,1001, fin);
		if(str[0] == 'v')
		{
			fscanf(fin,"%lf%lf%lf", &x,&y,&z);   //lf是double类型的格式符
			mvertex.push_back(new Vertex(x,y,z));
		}
		if(str[0] == 'f')
		{
			int n1,n2,n3;
			fscanf(fin, "%d%d%d", &n1,&n2,&n3);
			Vertex *v1 = mvertex[n1-1];
			Vertex *v2 = mvertex[n2-1];
			Vertex *v3 = mvertex[n3-1];

			set<pair<Vertex*, Vertex*>>::iterator index;
			findadj(v1, v2);
			findadj(v1, v3);
			findadj(v2, v3);
			findadj(v2, v1);
			findadj(v3, v1);
			findadj(v3, v2);

			Triangle *trig = new Triangle(v1,v2,v3);
			mtriangle.push_back(trig);
			v1->adjancent_trig.push_back(trig);
			v2->adjancent_trig.push_back(trig);
			v3->adjancent_trig.push_back(trig);
			
		}
	}
	fclose(fin);
}


Obj :: ~Obj( )
{
	int size = mvertex.size();
	for(int i = 0; i < size; i++ )
		delete mvertex[i];
	size = mtriangle.size();
	for(int i = 0; i < size; i++ )
		delete mtriangle[i];
}
void Obj :: savetofile(char* filename)
{
	FILE* fout = fopen(filename, "w");
	int vnum=0,trinum=0, size=0;
	size = mvertex.size();
	for(int i = 0; i< size; i++ )
	{
		if(mvertex[i]->effective == true)
			vnum++;
	}
	size = mtriangle.size();
	for(int i = 0; i< size; i++ )
	{
		if(mtriangle[i]->effective == true)
			trinum++;
	}
	fprintf(fout, "# %d vertices, %d faces\n",vnum, trinum);
	//下面理论上应该直接写入v格式的和f格式的点，但是呢f格式的点是v格式点的标号
	size = mvertex.size();
	int b=0;
	map<Vertex*, int> signal;
	for(int i = 0; i<size; i++ )
	{
		if( mvertex[i]->effective == true )
		{
			fprintf(fout, "v %lf %lf %lf\n", mvertex[i]->coord.getX(), mvertex[i]->coord.getY(), mvertex[i]->coord.getZ());
			signal[mvertex[i]]=++b;
			//cout << signal[mvertex[i]] << endl;
		}
	}
	size = mtriangle.size();
	for(int i = 0; i<size; i++ )
	{
		if( mtriangle[i]->effective == true )
		{
			fprintf(fout, "f %d %d %d\n", signal[mtriangle[i]->vertex[0]],signal[mtriangle[i]->vertex[1]], signal[mtriangle[i]->vertex[2]]);
		}
	}
	fclose(fout);
}