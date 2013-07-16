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


Point intersect(Point sp, Point ep, double a, double b, double c)
{
	double u = fabs(a*sp.x + b*sp.y + c);
	double v = fabs(a*ep.x + b*ep.y + c);
	Point tmp;
	tmp.x = (sp.x*v + ep.x*u) / (u+v);
	tmp.y = (sp.y*v + ep.y*u) / (u+v);
	return tmp;
}


int dplcmp(double x)
{
	if(fabs(x) < eps)
		return 0;
	else if(x > eps)
		return 1;
	return -1;
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

double getdis(Point a, Point b)
{
	return sqrt((a.x - b.x)*(a.x - b.x) + (a.y - b.y)*(a.y - b.y));
}

int main()
{
	double r;
	scanf("%d %lf", &n , &r);
	for(int i=1; i<=n; i++)
	{
		scanf("%lf %lf", &points[i].x, &points[i].y);
		p[i] = points[i];
	}
	points[n+1] = points[1];
	p[0] = p[n], p[n+1] = p[1];
	cnt = n;

	double a, b, c;
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

		a = ta.y - tb.y;
		b = tb.x - ta.x;
		c = ta.x*tb.y - tb.x*ta.y;
		cut(a, b, c);
	}

	int ansx = 0,ansy = 0;  
	double res = 0;  
	for(int i = 1; i <= cnt; ++i){  
		for(int j = i + 1; j <= cnt; ++j){  
			double tmp = getdis(p[i],p[j]);  
			if(tmp > res){  
				res = tmp;  
				ansx = i;  
				ansy = j;  
			}  
		}  
	}  
	printf("%.4lf %.4lf %.4lf %.4lf\n",p[ansx].x,p[ansx].y,p[ansy].x,p[ansy].y);  
	return 0;
}
