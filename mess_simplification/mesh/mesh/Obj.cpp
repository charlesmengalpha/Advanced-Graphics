#include "stdafx.h"
#include"Obj.h"
#include<fstream>
#include<iostream>
#include<stdio.h>
#include<map>

using namespace std;
//map��һ�ֹ���������������һ�����ݽṹ�������ڲ��ÿһ�����ݶ����Լ��ļ�ֵ������ͨ����ֵ���Һ�����
//pair�ǵ������ݶԵĲ�����pair��struct�͵ģ�ͨ��first��second���������ݣ���.
//map��������ݶ���pair�͵ģ�ͨ��insert()������Ԫ��(pair��)
#include<set>
//���ȴ�����һ�����ݣ�Ȼ����map����Ѱ�ң���������ҵ����Ͳ���������map�У���Ϊ����������map������б����ݡ�
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
			fscanf(fin,"%lf%lf%lf", &x,&y,&z);   //lf��double���͵ĸ�ʽ��
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
	//����������Ӧ��ֱ��д��v��ʽ�ĺ�f��ʽ�ĵ㣬������f��ʽ�ĵ���v��ʽ��ı��
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