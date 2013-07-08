//可以作为模版使用
#include <iostream>
#include <cstring>
#include <cstdio>
#include <algorithm>
#include <cmath>
using namespace std;

const double eps = 1e-8;
const int M = 1600;

struct Point
{
	double x, y;
}points[M], p[M], q[M];

int n, cnt, cur_n;

int dplcmp(double x)
{
	return fabs(x)<eps?0:(x>eps?1:-1);
}

Point intersect(Point sp, Point ep, double a, double b, double c)
{
	double u = fabs(a*sp.x + b*sp.y + c);
	double v = fabs(a*ep.x + b*ep.y + c);
	Point tmp;
	tmp.x = (sp.x*v + ep.x*u) / (u+v);
	tmp.y = (sp.y*v + ep.y*u) / (u+v);
	return tmp;
}

void cut(double a, double b, double c)
{
	cur_n = 0;
	for(int i=1; i<=cnt; i++)
	{
		if(dplcmp(a*p[i].x + b*p[i].y + c) <= 0)
			q[++cur_n] = p[i];
		else
		{
			if(dplcmp(a*p[i-1].x + b*p[i-1].y + c) < 0)
				q[++cur_n] = intersect(p[i], p[i-1], a, b, c);
			if(dplcmp(a*p[i+1].x + b*p[i+1].y + c) < 0)
				q[++cur_n] = intersect(p[i], p[i+1], a, b, c);
		}
	}
	for(int i=1; i<=cur_n; i++)
		p[i] = q[i];
	p[cur_n+1] = q[1];
	p[0] = q[cur_n];
	cnt = cur_n;
}

double getarea()
{
	double ret = 0.0;
	for(int i=1; i<=cnt; i++)
	{
		ret += p[i].x*p[i+1].y - p[i].y*p[i+1].x;
	}
	return ret/2.0;
}

void solve()
{
	for(int i=1; i<=n; i++)
		p[i] = points[i];
	p[0] = p[n], p[n+1] = p[1];
	cnt = n;

	double a, b, c;
	for(int i=1; i<=n; i++)
	{
		a = points[i].y - points[i+1].y;
		b = points[i+1].x - points[i].x;
		c = points[i].x*points[i+1].y - points[i+1].x*points[i].y;
		cut(a, b, c);
	}
}

int main()
{
	int cas;
	scanf("%d", &cas);
	while(cas --)
	{
		scanf("%d", &n);
		for(int i=1; i<=n; i++)
		{
			scanf("%lf %lf", &points[i].x, &points[i].y);
		}
		points[n+1] = points[1];
		solve();
		double area = fabs(getarea());
		printf("%.2lf\n", area);
	}
	return 0;
}

