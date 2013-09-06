#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
using namespace std;

const int maxn = 1510;
int dp[maxn][2], n;
bool vis[maxn];
vector<int> ve[maxn];

void dfs(int rt)
{
	if(ve[rt].size() == 0)
	{
		dp[rt][0] = 0;
		dp[rt][1] = 1;
		return;
	}
	int s = 0, t = 0;
	for(int i=0; i<ve[rt].size(); i++)
	{
		int v = ve[rt][i];
		dfs(v);
		s += dp[v][1];
		t += min(dp[v][1], dp[v][0]);
	}
	dp[rt][0] = s;
	dp[rt][1] = t + 1;
}

int main()
{
	while(scanf("%d", &n) != EOF)
	{
		memset(vis, false, sizeof(vis));
		memset(dp, 0, sizeof(dp));
		for(int i=0; i<n; i++)
		{
			int u, d, v;
			scanf("%d:(%d)", &u, &d);
			ve[u].clear();
			while(d --)
			{
				scanf("%d", &v);
				ve[u].push_back(v);
				vis[v] = true;
			}
		}
		int root;
		for(int i=0; i<n; i++)
		{
			if(!vis[i]) 
			{
				root = i;
			   	break;
			}
		}
		dfs(root);
		printf("%d\n", min(dp[root][0], dp[root][1]));
	}
	return 0;
}
