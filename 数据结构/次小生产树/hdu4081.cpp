#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <cmath>
using namespace std;

const double inf = 1e20;
const int N = 1010;

struct Point
{
	int x, y, val;
	Point(){}
	Point(int x, int y, int val):x(x), y(y), val(val){}
}city[N];

int n;
double edge[N][N], mmax[N][N], lowcost[N], sum;
int used[N][N], visited[N], nearvex[N];

void prim(int v0)
{
	sum = 0;
	memset(used, 0, sizeof(used));
	memset(visited, 0, sizeof(visited));
	memset(mmax, 0, sizeof(mmax));
	for(int i=1; i<=n; i++)
	{
		lowcost[i] = edge[v0][i];
		nearvex[i] = v0;
	}
	visited[v0] = 1;
	for(int i=1; i<n; i++)
	{
		double mmin = inf;
		int v = -1;
		for(int j=1; j<=n; j++)
		{
			if(!visited[j] && lowcost[j] < mmin)
			{
				v = j;
				mmin = lowcost[j];
			}
		}
		if(v != -1)
		{
			sum += lowcost[v];
			used[v][nearvex[v]] = used[nearvex[v]][v] = 1;
			visited[v] = 1;
			for(int k=1; k<=n; k++)
			{
				if(visited[k] && k!=v)
					mmax[v][k] = mmax[k][v] = max(mmax[k][nearvex[v]], lowcost[v]);
				if(!visited[k] && edge[v][k] < lowcost[k])
				{
					lowcost[k] = edge[v][k];
					nearvex[k] = v;
				}
			}
		}
	}
}

double _distance(Point a, Point b)
{
	return sqrt((a.x-b.x)*(a.x-b.x) + (a.y-b.y)*(a.y-b.y));
}

int main()
{
	int cas;
	scanf("%d", &cas);
	while(cas --)
	{
		scanf("%d", &n);
		for(int i=1; i<=n; i++)
			scanf("%d %d %d", &city[i].x, &city[i].y, &city[i].val);
		for(int i=1; i<=n; i++)
		{
			edge[i][i] = 0;
			for(int j=i+1; j<=n; j++)
			{
				double dis = _distance(city[i], city[j]);
				edge[i][j] = edge[j][i] = dis;
			}
		}

		prim(1);
		double r = -1;
		for(int i=1; i<=n; i++)
			for(int j=i+1; j<=n; j++)
			{
				if(used[i][j])
				{
					double tr = (city[i].val + city[j].val)*1.0/(sum - edge[i][j]);
					r = max(r, tr);
				}
				else
				{
					double tr = (city[i].val + city[j].val)*1.0/(sum - mmax[i][j]);
					r = max(r, tr);
				}
			}
		printf("%.2lf\n", r);
	}
	return 0;
}
