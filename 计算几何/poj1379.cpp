/*
Problem: 1379		User: heike520
Memory: 184K		Time: 2375MS
Language: C++		Result: Accepted
*/
#include <iostream>
#include <cstring>
#include <cstdio>
#include <algorithm>
#include <cmath>
using namespace std;

const int M = 1002;
const double eps = 1e-6;

struct Point
{
	double x, y;
}pp[M], tpp[40];
int x, y, m;

double getDis(Point p0)
{
	double ret = 1e8;
	for(int i=0; i<m; i++)
	{
		double dis = sqrt((pp[i].x-p0.x)*(pp[i].x-p0.x) + (pp[i].y-p0.y)*(pp[i].y-p0.y));
		if(ret > dis)
			ret = dis;
	}
	return ret;
}

Point getSaftPoint()
{
	double tmp,T=max(x,y)/sqrt(1.0 * m)+1;
	Point tp;
	for (double i=T;i>=1e-2;i*=0.9)
		for (int j=0;j<30;++j)
			for (int k=0;k<30;++k)
			{
				tmp=rand(); 
				tp.x = tpp[j].x + cos(tmp) * i;
				tp.y = tpp[j].y + sin(tmp) * i;
				if (0<=tp.x && tp.x<=x && 0<=tp.y && tp.y<=y)
				{
					if(getDis(tp) > getDis(tpp[j]))
						tpp[j]=tp;
				}
			}
	for (int i=1;i<30;++i)
		if(getDis(tpp[0]) < getDis(tpp[i]))
			tpp[0] = tpp[i];
	return tpp[0];
}

int main()
{
	int T;
	scanf("%d", &T);
	while(T -- )
	{
		scanf("%d %d %d", &x, &y, &m);
		for(int i=0; i<m; i++)
			scanf("%lf %lf", &pp[i].x, &pp[i].y);
		for(int i=0; i<30; i++)
		{
			tpp[i].x = rand()%x + 1;
			tpp[i].y = rand()%y + 1;
		}
		Point ans = getSaftPoint();
		printf("The safest point is (%.1lf, %.1lf).\n", ans.x, ans.y);
	}
	return 0;
}
