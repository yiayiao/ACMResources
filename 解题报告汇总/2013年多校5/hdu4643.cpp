#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cmath>
#define zero(x) (((x)>0?(x):-(x))<eps)
using namespace std;

const int maxn = 50;
const double eps = 1e-7;
struct point 
{
	double x, y;
	point() {}
	point(double x, double y):x(x), y(y) {}
}city[maxn], base[maxn], cui[maxn], head;
int n, m, q;

double getdis(point a, point b)
{
	return sqrt((a.x-b.x)*(a.x-b.x) + (a.y-b.y)*(a.y-b.y));
}

double xmult(point op, point sp, point ep)
{
	return ((sp.x - op.x)*(ep.y - op.y) - (ep.x - op.x)*(sp.y - op.y));
}

point intersection(point u1, point u2, point v1, point v2)
{
	point ret=u1;
	double t=((u1.x-v1.x)*(v1.y-v2.y)-(u1.y-v1.y)*(v1.x-v2.x))
		/((u1.x-u2.x)*(v1.y-v2.y)-(u1.y-u2.y)*(v1.x-v2.x));
	ret.x+=(u2.x-u1.x)*t;
	ret.y+=(u2.y-u1.y)*t;
	return ret;
}

point cross(point a, point b, point u, point v)
{
	point u1, u2;
	u1.x = (a.x + b.x) / 2;
	u1.y = (a.y + b.y) / 2;
	u2.x = u1.x - a.y + b.y;
	u2.y = u1.y + a.x - b.x;
	return intersection(u1, u2, u, v);
}

bool dot_online_in(point p,point l1,point l2)
{
	bool f1 = zero(xmult(p,l1,l2));	//p在直线l1-l2上
	bool f2 = (l1.x-p.x)*(l2.x-p.x)<eps;
	bool f3 = (l1.y-p.y)*(l2.y-p.y)<eps;
	return f1&&f2&&f3;
}

void solve(int u, int v)
{
	int cot = 0;
	for(int i=1; i<m; i++)
		for(int j=i+1; j<=m; j++)
		{
			point n_cro = cross(base[i], base[j], city[u], city[v]);
			if(!dot_online_in(n_cro, city[u], city[v]))
				continue;
			double mdis = getdis(base[i], n_cro);
			bool flag = false;
			for(int k=1; k<=m; k++)
			{
				if(k != i && k != j && getdis(base[k], n_cro) < mdis + eps)
					flag = true;
				//cout<<getdis(base[k], n_cro)<<endl;
			}
			if(!flag) cot ++;
		}
	printf("%d\n", cot);
}

int main()
{
	while(scanf("%d %d", &n, &m) == 2) 
	{
		for(int i=1; i<=n; i++)
		{
			scanf("%lf %lf", &city[i].x, &city[i].y);
		}
		for(int i=1; i<=m; i++)
		{
			scanf("%lf %lf", &base[i].x, &base[i].y);
		}
		scanf("%d", &q);
		while(q --)
		{
			int u, v;
			scanf("%d %d", &u, &v);
			if(u > v)
				swap(u, v);
			solve(u, v);
		}
	}
	return 0;
}
