/*
用的编译器	C++
题目		1688
作者		heike520
提交时间	2013/7/10 11:47:14
*/

#include <iostream>
#include <cstdio>
#include <cmath>
#include <algorithm>
using namespace std;

const double eps = 1e-6;
const int M = 60;

struct Node
{
	double x, y, z;
	Node(){x = y = z = 0;}
}node[M];
int n;

double getdis(Node n1, Node n2)
{
	return sqrt((n1.x-n2.x)*(n1.x-n2.x) + (n1.y-n2.y)*(n1.y-n2.y) + (n1.z-n2.z)*(n1.z-n2.z));
}

int getdir(Node tp)
{
	double tdis = -1; 
	int ret = 0;
	for(int i=0; i<n; i++)
		if(getdis(tp, node[i]) > tdis)
		{
			tdis = getdis(tp, node[i]);
			ret = i;
		}
	return ret;
}

int main()
{
	while(scanf("%d", &n) && n)
	{
		for(int i=0; i<n; i++)
			scanf("%lf %lf %lf", &node[i].x, &node[i].y, &node[i].z);
		double delta = 200;
		double ans = 1e50;
		Node tp;	
		while(delta > eps)
		{
			int dir = getdir(tp);
			double dis = getdis(tp, node[dir]);
			if(dis < ans)
				ans = dis;
			tp.x += (node[dir].x - tp.x)/dis*delta;
			tp.y += (node[dir].y - tp.y)/dis*delta;
			tp.z += (node[dir].z - tp.z)/dis*delta;
			delta *= 0.985;
		}
		printf("%.5lf\n", ans);
	}
	return 0;
}
