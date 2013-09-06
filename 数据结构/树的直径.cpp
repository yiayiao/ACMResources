//http://acm.tju.edu.cn/toj/showp3517.html
#include <iostream>
#include <cstring>
#include <cstdio>
#include <algorithm>
#include <vector>
using namespace std;

const int maxn = 2010;
struct Node
{
	int v, w;
	Node(int v, int w) :v(v), w(w) {}
};
vector<Node> ve[maxn];
int n, rt, sum, dis[maxn], que[maxn], st, ed;
bool vis[maxn];

void bfs(int u)
{
	memset(dis, 0, sizeof(dis));
	memset(vis, 0, sizeof(vis));
	sum = dis[u] = 0;
	st = ed = 0;
	vis[u] = true;
	que[ed++] = u;
	while(st < ed)
	{
		int uu = que[st++];
		if(dis[uu] > sum)
		{
			sum = dis[uu];
			rt = uu;
		}
		for(int i=0; i<ve[uu].size(); i++)
		{
			int vv = ve[uu][i].v, ww = ve[uu][i].w;
			if(!vis[vv])
			{
				vis[vv] = true;
				dis[vv] = dis[uu] + ww;
				que[ed++] = vv;
			}
		}
	}
}


int main()
{
	int cas;
	scanf("%d", &cas);
	while(cas --)
	{
		scanf("%d", &n);
		for(int i=0; i<=n; i++) ve[i].clear();
		for(int i=0; i<n-1; i++)
		{
			int u, v, w;
			scanf("%d %d %d", &u, &v, &w);
			ve[u].push_back(Node(v, w));
			ve[v].push_back(Node(u, w));
		}
		bfs(1);
		bfs(rt);
		printf("%d\n", sum);
	}
	return 0;
}
