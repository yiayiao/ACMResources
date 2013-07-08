/*
简单题，问一个多边形存不存在核 同poj1474题
使用的编译器	G++
运行使用时间	0 Ms
运行使用内存	696 Kb
*/

#include <iostream>
#include <cstring>
#include <cstdio>
#include <algorithm>
#include <cmath>
using namespace std;

const double eps = 1e-10;
const int M = 105;

struct Point
{
	double x, y;
}pt[M], q[M], p[M];

int  n, m;
double a, b, c;

void getline(Point sp, Point ep)
{
	a = ep.y - sp.y;
	b = sp.x - ep.x;
	c = ep.x*sp.y - sp.x*ep.y;
}

Point intersect(Point sp, Point ep)
{
	double u = fabs(a*sp.x + b*sp.y + c);
	double v = fabs(a*ep.x + b*ep.y + c);
	Point ans;
	ans.x = (sp.x*v + ep.x*u)/(u + v);
	ans.y = (sp.y*v + ep.y*u)/(u + v);
	return ans;
}

void cut()
{
	int cutm = 0;
	for(int i=1; i<=m; i++)
	{
		if(a*p[i].x + b*p[i].y + c >= 0)
		{
			q[++cutm] = p[i];
		}
		else
		{
			if(a*p[i-1].x + b*p[i-1].y + c > 0)
				q[++cutm] = intersect(p[i-1], p[i]);
			if(a*p[i+1].x + b*p[i+1].y + c > 0)
				q[++cutm] = intersect(p[i+1], p[i]);
		}
	}
	for(int i=1; i<=cutm; i++)
	{
		p[i] = q[i];
	}
	p[cutm + 1] = q[1];
	p[0] = q[cutm];
	m = cutm;
}

void solve()
{
	for(int i=1; i<=n; i++)
	{
		p[i] = pt[i];
	}
	pt[n+1] = pt[1];
	p[n+1] = p[1];
	p[0] = p[n];
	m = n;
	for(int i=1; i<=n; i++)
	{
		getline(pt[i], pt[i+1]);
		cut();
	}
}

int main()
{
	int cas, i;
	scanf("%d", &cas);
	while(cas --)
	{
		scanf("%d", &n);
		for(int i=1; i<=n;i++)
		{
			scanf("%lf %lf", &pt[i].x, &pt[i].y);
		}
		solve();
		puts(m == 0 ? "NO" : "YES");
	}
	return 0;
}
