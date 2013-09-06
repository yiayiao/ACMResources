#include <iostream>
#include <cstring>
#include <cstdio>
#include <algorithm>
#include <vector>
using namespace std;

const int maxn = 40001;

struct Node
{
	int v, len;
	Node(){}
	Node(int a, int b):v(a), len(b){}
};
vector<Node> mp[maxn];
struct Que
{
	int u, v, id;
	Que(){}
	Que(int u, int v, int id): u(u), v(v), id(id){}
};
vector<Que> que[maxn];

int n, m, q;
int fa[maxn], dist[maxn], ans[maxn];
bool vis[maxn];

void init()
{
	for(int i=1; i<=n; i++)
	{
		mp[i].clear();
		que[i].clear();
		vis[i] = false;
	}
}

int find(int x)
{
	if(fa[x] != x)
		fa[x] = find(fa[x]);
	return fa[x];
}

void _union(int x, int y)
{
	int xx = find(x), yy = find(y);
	if(xx == yy) return;
	fa[yy] = xx;	//注意xx为父亲节点
}

void tarjan(int u, int dd)
{
	vis[u] = true;
	fa[u] = u;
	dist[u] = dd;
	for(int i=0; i<mp[u].size(); i++)
	{
		int v = mp[u][i].v;
		if(!vis[v])
		{
			tarjan(v, dd + mp[u][i].len);
			_union(u, v);
		}
	}
	for(int i=0; i<que[u].size(); i++)
	{
		int v = que[u][i].v;
		if(vis[v])
			ans[que[u][i].id] = dist[u] + dist[v] - 2*dist[find(v)];
	}
}

int main()
{
	while(scanf("%d%d", &n, &m) != EOF)
	{
		init();
		for(int i=0; i<m; i++)
		{
			int u, v, w; char tt[3];
			scanf("%d %d %d %s", &u, &v, &w, tt);
			mp[u].push_back(Node(v, w));
			mp[v].push_back(Node(u, w));
		}
		scanf("%d", &q);
		for(int i=0; i<q; i++)
		{
			int u, v;
			scanf("%d %d", &u, &v);
			que[u].push_back(Que(u, v, i));
			que[v].push_back(Que(v, u, i));
		}
		tarjan(1, 0);
		for(int i=0; i<q; i++)
			printf("%d\n", ans[i]);
	}
	return 0;
}
