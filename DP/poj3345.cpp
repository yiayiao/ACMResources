#include <iostream>
#include <cstring>
#include <cstdio>
#include <algorithm>
#include <vector>
#include <map>
#include <sstream>
#include <string>
using namespace std;

const int maxn = 210, inf = 0x7ffffff;
int dp[maxn][maxn], cost[maxn], in[maxn], n, m;
vector<int> ve[maxn];
bool vis[maxn];

int dfs(int u)
{
	vis[u] = true;
	int num = 1;
	for(int i=0; i<ve[u].size(); i++)
	{
		int v = ve[u][i];
		if(vis[v]) continue;
		num += dfs(v);
	}
	for(int j=0; j<=n; j++)
		dp[u][j] = inf;
	dp[u][0] = 0;
	for(int i=0; i<ve[u].size(); i++)
	{
		int v = ve[u][i];
		for(int j=n; j>0; j--)
			for(int k=1; j-k>=0; k++)
				if(dp[u][j] > dp[u][j-k] + dp[v][k])
					dp[u][j] = dp[u][j-k] + dp[v][k];
	}
	if(dp[u][num] > cost[u])
		dp[u][num] = cost[u];
	return num;
}

int main()
{
	char str[1000];
	while(gets(str))
	{
		if(str[0] ==  '#')
			break;
		sscanf(str, "%d%d", &n, &m);
		for(int i=0; i<=n; i++)
			ve[i].clear();
		map<string, int> mymap;
		memset(vis, 0, sizeof(vis));
		memset(in, 0, sizeof(in));
		int id = 0;
		for(int i=1; i<=n; i++)
		{
			scanf("%s", str);
			if(mymap.find(str) == mymap.end()) 
				mymap[str] = ++id;
			int u = mymap[str];
			scanf("%d", &cost[u]);
			gets(str);
			stringstream ss(str);
			string name;
			while(ss >> name)
			{
				if(mymap.find(name) == mymap.end())
					mymap[name] = ++id;
				ve[u].push_back(mymap[name]);
				in[mymap[name]] ++;
			}
		}
		cost[0] = inf;
		for(int i=1; i<=n; i++)
		{
			if(in[i]) continue;
			ve[0].push_back(i);
		}
		dfs(0);
		int ans = inf;
		for(int i=m; i<=n; i++)
		{
			if(dp[0][i] != -1 && dp[0][i] < ans)
				ans = dp[0][i];
		}
		printf("%d\n", ans);
	}
	return 0;
}
