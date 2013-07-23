/*
自己的dp还是很弱啊，dp[l]表示从l开始往后扩展
*/
#include <iostream>
#include <cstring>
#include <cstdio>
#include <algorithm>
using namespace std;

typedef long long LL;
LL dp[70], num[70];
int n;

LL dfs(int l)
{
	if(l == n)
		return 0;
	if(~dp[l])
		return dp[l];
	dp[l] = (1ll<<62) - 1;
	for(int i=l+1; i<=min(l+20, n); i++)
	{
		dp[l] = min(dp[l], dfs(i) + (1<<i-l)*num[l]);
	}
	return dp[l];	
}

int main()
{
	int cas;
	scanf("%d", &cas);
	while(cas --)
	{
		scanf("%d", &n);
		for(int i=0; i<n; i++)
		{
			scanf("%I64d", &num[i]);
		}
		memset(dp, -1, sizeof(dp));
		printf("%I64d\n", dfs(0));
	}
	return 0;
}
