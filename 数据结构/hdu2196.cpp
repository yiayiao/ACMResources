#include <iostream>
#include <cstring>
#include <cstdio>
#include <algorithm>
#include <vector>
using namespace std;

const int maxn = 10010;
struct Node
{
	int v, w;
	Node(int v, int w) :v(v), w(w) {}
};
vector<Node> ve[maxn];
int n, rt, sum, dis[2][maxn], que[maxn], st, ed;
bool vis[maxn];

void bfs(int u, int id)
{
	memset(dis[id], 0, sizeof(dis[id]));
	memset(vis, 0, sizeof(vis));
	sum = dis[id][u] = 0;
	st = ed = 0;
	vis[u] = true;
	que[ed++] = u;
	while(st < ed)
	{
		int uu = que[st++];
		if(dis[id][uu] > sum)
		{
			sum = dis[id][uu];
			rt = uu;
		}
		for(int i=0; i<ve[uu].size(); i++)
		{
			int vv = ve[uu][i].v, ww = ve[uu][i].w;
			if(!vis[vv])
			{
				vis[vv] = true;
				dis[id][vv] = dis[id][uu] + ww;
				que[ed++] = vv;
			}
		}
	}
}


int main()
{
	int cas;
	while(scanf("%d", &n) != EOF)
	{
		for(int i=0; i<=n; i++) ve[i].clear();
		for(int i=2; i<=n; i++)
		{
			int v, w;
			scanf("%d %d", &v, &w);
			ve[i].push_back(Node(v, w));
			ve[v].push_back(Node(i, w));
		}
		bfs(1, 0);
		bfs(rt, 0);
		bfs(rt, 1);
		for(int i=1; i<=n; i++)
		{
			//printf("i: %d %d %d\n", i, dis[0][i], dis[1][i]);
			printf("%d\n", max(dis[0][i], dis[1][i]));
		}
	}
	return 0;
}
