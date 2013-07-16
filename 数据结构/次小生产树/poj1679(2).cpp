/***
使用的编译器	G++
题目		1679
作者		heike520
提交时间	2013/7/15 22:38:22
***/

#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <cmath>
using namespace std;

const int inf = 0x7fffffff;
const int N = 1010;

int n, sum;
int edge[N][N], mmax[N][N], lowcost[N];
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

int main()
{
	int cas, m;
	scanf("%d", &cas);
	while(cas --)
	{
		scanf("%d %d", &n, &m);
		for(int i=1; i<=n; i++)
			for(int j=1; j<=n; j++)
				edge[i][j] = inf;
		for(int i=1; i<=m; i++)
		{
			int u, v, w;
			scanf("%d %d %d", &u, &v, &w);
			edge[u][v] = edge[v][u] = w;
		}
		prim(1);

		bool flag = false;
		for(int i=1; i<=n; i++)
			for(int j=1; j<=n; j++)
			{
				if(!used[i][j] && edge[i][j] == mmax[i][j])
				{
					flag = true;
				}
			}

		if(flag)
			printf("Not Unique!\n");
		else
			printf("%d\n", sum);
	}
	return 0;
}
