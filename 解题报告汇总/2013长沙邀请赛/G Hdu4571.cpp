/*
训练赛的时候遇到了这道题，真的是个大坑，写了整整四个小时，别人都是直接贴以前的代码过的，不过感觉磨练很大。
在两个点之间选一些点经过，路径和点都有花费，求收益最大
使用的编译器	G++
运行使用时间	1171 Ms
运行使用内存	592 Kb
*/
#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
using namespace std;

const int maxn = 107, maxt = 400;
const int inf = 0x3fffff;
struct Node
{
	int id, c, s;
}city[maxn];
int n, m, s, t, e, ans;
int map[maxn][maxn];
int dp[maxn][maxt];
vector<int> ve[maxn];

void input()
{
	scanf("%d %d %d %d %d", &n, &m, &t, &s, &e);
	s++, e++;
	for(int i=1; i<=n; i++)
	{
		city[i].id = i;
		scanf("%d", &city[i].c);
	}
	for(int i=1; i<=n; i++)
	{
		scanf("%d", &city[i].s);
		for(int j=1; j<=n; j++)
			map[i][j] = inf;
		ve[i].clear();
	}
	for(int i=1; i<=m; i++)
	{
		int u, v, c;
		scanf("%d %d %d", &u, &v, &c);
		u++, v++;
		map[u][v] = map[v][u] = min(map[v][u], c);
	}
}

void floyd()
{
	for(int k=1; k<=n; k++)
		for(int i=1; i<=n; i++)
			for(int j=1; j<=n; j++)
			{
				if(i != j && map[i][j] > map[i][k] + map[k][j])
					map[i][j] = map[i][k] + map[k][j];
			}
}

void dfs(int s, int t)
{
	for(int j=0; j<ve[s].size(); j++)
	{
		int i = ve[s][j];
		if(t >= city[i].c + map[s][i])
		{
			if(dp[s][t] + city[i].s > dp[i][t-city[i].c-map[s][i]])
			{
				dp[i][t-city[i].c-map[s][i]] = dp[s][t] + city[i].s;
				dfs(i, t-city[i].c-map[s][i]);
			}
		}
	}
	if(t >= map[s][e])
		dp[e][t-map[s][e]] = max(dp[s][t], dp[e][t-map[s][e]]);
}

void solve()
{
	for(int i=1; i<=n; i++)
	{
		for(int j=1; j<=n; j++)
			if(city[j].s > city[i].s)
				ve[i].push_back(j);
	}

	memset(dp, 0, sizeof(dp));
	dp[s][t-city[s].c] = city[s].s;
	dfs(s, t-city[s].c);
	for(int i=1; i<=n; i++)
		if(s != i && t >= map[s][i] + city[i].c)
		{
			dp[i][t-map[s][i]-city[i].c] = city[i].s;
			dfs(i, t-map[s][i]-city[i].c);
		}
	int ans = 0;
	for(int i=0; i<=t; i++)
		ans = max(ans, dp[e][i]);
	printf("%d\n", ans);
}

int main()
{
	int cas;
	scanf("%d", &cas);
	for(int T=1; T<=cas; T++)
	{
		input();
		floyd();
		printf("Case #%d:\n", T);
		solve();
	}
	return 0;
}