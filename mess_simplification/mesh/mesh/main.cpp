// mesh_simplication.cpp : 定义控制台应用程序的入口点。
//
#include "stdafx.h"
#include"Mesh_simplify.h"
#include<iostream>
#include<sstream>
#include<string.h>
using namespace std;
int main(int argc, char** argv)
{
	if( argc != 4 )
	{
		cout << "The standard input is .exe  .obj  .obj  double ."<<endl;
		return -1;
	}
	int lens = strlen(argv[1]);
	if(argv[1][lens-4] != '.' || argv[1][lens-3]!='o' || argv[1][lens-2]!='b'|| argv[1][lens-1] != 'j')
	{
		cout << "The argv[1] input is  .obj ."<<endl;
		return -1;
	}
	lens = strlen(argv[2]);
	if(argv[2][lens-4] != '.' || argv[2][lens-3]!='o' || argv[2][lens-2]!='b'|| argv[2][lens-1] != 'j')
	{
		cout << "The argv[2] input is  .obj ."<<endl;
		return -1;
	}
	double ratio =atof(argv[3]);
	if(ratio<0 || ratio >1)
	{
		cout << "The argv[3] input is from 0 to 1." << endl;
		return -1;
	}
	Obj obj(argv[1]);
	Mesh_simplify::choose_edge_collapse(obj,ratio);
	obj.savetofile(argv[2]);
	system("pause");
	return 0;
}

