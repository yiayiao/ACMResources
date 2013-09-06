#include <iostream>
#include <cstring>
#include <cstdio>
#include <algorithm>
#include <vector>
using namespace std;

const int maxn = 50010;
typedef long long LL;
int n, I, R;
LL dp[maxn], num[maxn];
vector<int> ve[maxn];
bool vis[maxn];

void dfs1(int u)
{
	vis[u] = true;
	num[u] = 1, dp[u] = 0;
	for(int i=0; i<ve[u].size(); i++)
	{
		int v = ve[u][i];
		if(!vis[v])
		{
			dfs1(v);
			num[u] += num[v];
			dp[u] += dp[v] + num[v];
		}
	}
}

void dfs2(int u)
{
	vis[u] = true;
	for(int i=0; i<ve[u].size(); i++)
	{
		int v = ve[u][i];
		if(!vis[v])
		{
			dp[v] = dp[u] - 2*num[v] + num[1];
			dfs2(v);
		}
	}
}


int main()
{
	int T;
	scanf("%d", &T);
	while(T --)
	{
		scanf("%d %d %d", &n, &I, &R);
		for(int i=0; i<=n; i++)
			ve[i].clear();
		for(int i=1; i<n; i++)
		{
			int u, v;
			scanf("%d %d", &u, &v);
			ve[u].push_back(v);
			ve[v].push_back(u);
		}
		memset(vis, false, sizeof(vis));
		dfs1(1);
		memset(vis, false, sizeof(vis));
		dfs2(1);
		LL mmax = (1ll)<<62;
		vector<int> ans;
		for(int i=1; i<=n; i++)
		{
			if(dp[i] < mmax)
			{
				ans.clear();
				mmax = dp[i];
				ans.push_back(i);
			}
			else if(dp[i] == mmax)
				ans.push_back(i);
		}
		printf("%lld\n", mmax*I*I*R);
		for(int i=0; i<ans.size(); i++)
			printf("%d%c", ans[i], i != ans.size()-1 ? ' ': '\n');
		printf("\n");
	}
	return 0;
}