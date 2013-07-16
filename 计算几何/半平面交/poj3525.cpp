#include <iostream>
#include <cstring>
#include <cstdio>
#include <algorithm>
#include <cmath>
using namespace std;

const double eps = 1e-10;
const int M = 200;

struct Point
{
	double x, y;
}points[M], p[M], q[M];

int n, cnt, cur_n;

void getline(Point sp, Point ep, double &a, double &b, double &c)
{
	a = ep.y - sp.y;
	b = sp.x - ep.x;
	c = ep.x*sp.y - sp.x*ep.y;
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
		if(a*p[i].x + b*p[i].y + c > eps)
			q[++cur_n] = p[i];
		else
		{
			if(a*p[i-1].x + b*p[i-1].y + c > eps)
				q[++cur_n] = intersect(p[i], p[i-1], a, b, c);
			if(a*p[i+1].x + b*p[i+1].y + c > eps)
				q[++cur_n] = intersect(p[i], p[i+1], a, b, c);
		}
	}
	for(int i=1; i<=cur_n; i++)
		p[i] = q[i];
	p[cur_n+1] = q[1];
	p[0] = q[cur_n];
	cnt = cur_n;
}

void initial()
{
	for(int i=1; i<=n; i++)
		p[i] = points[i];
	p[n+1] = p[1];
	p[0] = p[n];
	cnt = n;
}

bool solve(double r)
{
	initial();
	for(int i=1; i<=n; i++)
	{
		Point ta, tb, tt;
		tt.x = points[i+1].y - points[i].y;  
        tt.y = points[i].x - points[i+1].x;  
        double k = r / sqrt(tt.x * tt.x + tt.y * tt.y);  
        tt.x = tt.x * k;  
        tt.y = tt.y * k;  
        ta.x = points[i].x + tt.x;  
        ta.y = points[i].y + tt.y;  
        tb.x = points[i+1].x + tt.x;  
        tb.y = points[i+1].y + tt.y; 
	
		double a, b, c;
		getline(ta, tb, a, b, c);
		cut(a, b, c);
	}

	if(cnt <= 0)
		return false;
	return true;
}


int main()
{
	while(scanf("%d", &n) && n)
	{
		for(int i=1; i<=n; i++)
			scanf("%lf %lf", &points[i].x, &points[i].y);
		for(int i=1; i<(n+1)/2; i++)	//顶点是逆时针给出的
			swap(points[i], points[n-i]);
		points[n+1] = points[1];

		double high = 1000000000.0, low = 0, mid;
		while(low + eps <= high)
		{
			mid = (high + low)/2.0;
			if(solve(mid))
				low = mid;
			else
				high = mid;
		}
		printf("%.6lf\n", high);
	}
	return 0;
}

