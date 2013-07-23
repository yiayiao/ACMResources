/*
在一个有向图中选择一个环，使得环的点权值与边权值的比最大
Problem: 3621		User: heike520
Memory: 304K		Time: 594MS
Language: C++		Result: Accepted
*/
#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <queue>
using namespace std;

const int maxn = 1010;
const double eps = 1e-4, inf = 1e30;
int n, m;
struct Edge
{
	int u, w;
	Edge(int a, int b):u(a), w(b){}
	Edge(){}
};
vector<Edge> edge[maxn];
int val[maxn], cnt[maxn];
bool vis[maxn];
double dis[maxn];

bool spfa(int src, double mid)
{
	queue<int> que;
	for(int i=1; i<=n; i++)
	{
		dis[i] = inf;
		vis[i] = false;
		cnt[i] = 0;
	}
	dis[src] = 0;
	vis[src] = true;
	cnt[src] ++;
	que.push(src);
	while(!que.empty())
	{
		int fv = que.front();
		que.pop();
		vis[fv] = false;
		for(int j=0; j<edge[fv].size(); j++)
		{
			int tv = edge[fv][j].u, tw = edge[fv][j].w;
			if(dis[tv] > dis[fv] + tw*mid - val[tv])
			{
				dis[tv] = dis[fv] + tw*mid - val[tv];
				if(!vis[tv])
				{
					vis[tv] = true;
					que.push(tv);
					cnt[tv] ++ ;
					if(cnt[tv] >= n)
						return true;
				}
			}
		}
	}
	return false;
}

int main()
{
	while(scanf("%d %d", &n, &m) != EOF)
	{
		for(int i=1; i<=n; i++)
		{
			scanf("%d", &val[i]);
			edge[i].clear();
		}
		for(int i=1; i<=m; i++)
		{
			int u, v, c;
			scanf("%d %d %d", &u, &v, &c);
			edge[u].push_back(Edge(v, c));
		}
		double low = 0, high = 10000.0;
		while(low + eps < high)
		{
			double mid = (low + high) / 2;
			if(spfa(1, mid))
				low = mid;
			else
				high = mid;
		}
		printf("%.2lf\n", low);
	}
	return 0;
}
