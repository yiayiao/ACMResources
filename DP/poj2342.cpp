#include <iostream>
#include <cstring>
#include <cstdio>
#include <algorithm>
#include <vector>
using namespace std;

const int maxn = 6010;
int n, dp[maxn][2], num[maxn];
bool vis[maxn];
vector<int> ve[maxn];

void dfs(int rt)
{
	if(ve[rt].size() == 0)
		return;
	for(int i=0; i<ve[rt].size(); i++)
	{
		int u = ve[rt][i];
		dfs(u);
		dp[rt][1] += dp[u][0];
		dp[rt][0] += max(dp[u][0], dp[u][1]);
	}
}

int main()
{
	while(scanf("%d", &n) != EOF)
	{
		int l, k, rt;
		for(int i=1; i<=n; i++)
		{
			scanf("%d", &num[i]);
			dp[i][1] = num[i];
			vis[i] = dp[i][0] = 0;
			ve[i].clear();
		}
		while(scanf("%d %d", &l, &k) && (l + k))
		{
			ve[k].push_back(l);
			vis[l] = true;
		}
		for(int i=1; i<=n; i++)
			if(!vis[i])
			{
				rt = i;
				break;
			}
		dfs(rt);
		printf("%d\n", max(dp[rt][0], dp[rt][1]));
	}
	return 0;
}
