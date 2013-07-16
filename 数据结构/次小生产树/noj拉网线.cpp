/*求多组特定a, b两点不相连情况下的最小生成树
使用的编译器	GPP
运行使用时间	1140 Ms
运行使用内存	97840 Kb
*/
#include <iostream>
#include <cstring>
#include <algorithm>
#include <cstdio>
#include <vector>
#include <cmath>
using namespace std;

const int inf = 0x7fffffff;
const int N = 3005;
struct edge
{
	int a, b, dis;
	edge(){}
	edge(int a, int b, int dis):a(a),b(b),dis(dis) {}
	friend bool operator<(edge a, edge b)
	{
		return a.dis < b.dis;
	}
}sta[N*N], lx[N*N];
int use[N][N], fa[N], mp[N][N], dp[N][N], n, id;
vector<int> ve[N];

void init(int n)
{
	for(int i=0; i<n; i++)
	{
		ve[i].clear();
		for(int j=0; j<n; j++)
			dp[i][j] = inf;
	}
}

int find(int x)
{
	if(fa[x] != x)
		fa[x] = find(fa[x]);
	return fa[x];
}

int gaoMST()
{
	for(int i=0; i<id; i++)
		lx[i] = sta[i];
	for(int i=0; i<n; i++)
		fa[i] = i;
	memset(use, 0, sizeof(use));
	sort(lx, lx + id);
	int ans = 0;
	for(int i=0, t=0; t<n-1; i++)
	{
		int u = lx[i].a, v = lx[i].b;
		int uu = find(u), vv = find(v);
		if(uu == vv)
			continue;
		fa[uu] = vv;
		ans += lx[i].dis;
		t ++;
		use[u][v] = use[v][u] = 1;
		ve[v].push_back(u);
		ve[u].push_back(v);
	}
	return ans;
}

int gaoTree(int rt, int p, int s)
{
	int ans = inf;
	for(int i=0; i<ve[s].size(); i++)
	{
		int ss = ve[s][i];
		if(ss == p) continue;
		int t = gaoTree(rt, s, ss);
		ans = min(t, ans);
	}
	if(p != rt) 
		ans = min(ans, mp[rt][s]);
	if(p != s)
		dp[s][p] = dp[p][s] = min(dp[s][p], ans);
	return ans;
}

int main()
{
	int cas, q;
	scanf("%d", &cas);
	while(cas --)
	{
		scanf("%d", &n);
		init(n);
		id = 0;
		for(int i=1; i<n; i++)
			for(int j=0; j<i; j++)
			{
				int tmp;
				scanf("%d", &tmp);
				mp[i][j] = mp[j][i] = tmp;
				sta[id++] = edge(i, j, tmp);
			}
		int sum = gaoMST();
		for(int i=0; i<n; i++)
			gaoTree(i, i, i);

		int a , b;
		scanf("%d", &q);
		long long ans = 0;
		for(int i=0; i<q; i++)
		{
			scanf("%d %d", &a, &b);
			if(!use[a][b]) ans += sum;
			else
			{
				ans += sum - mp[a][b] + dp[a][b];
			}
		}
		printf("%.4lf\n", 1.0*ans/q);
	}
	return 0;
}