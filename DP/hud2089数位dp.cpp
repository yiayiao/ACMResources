/*
使用的编译器	G++
运行使用时间	15 Ms
运行使用内存	204 Kb
 */ 
#include <cstdio>
#include <cstring>

const int N = 10;
int bit[N];
int dp[N][3];	//不吉利的数的个数
/*
dp[i][0]:前i位不含不吉利数。
dp[i][1]:前i位不含不吉利数且i+1位是6。
dp[i][2]:前i位含不吉利数。
 */
int dfs(int pos, int st, bool flag)
{
	if(pos == 0)
		return st == 2;
	if(flag && dp[pos][st] != -1)
		return dp[pos][st];
	int ans = 0;
	int u = flag ? 9 : bit[pos];
	for(int d = 0; d <= u; d++)
	{
		if(st == 2 || d == 4 || (st == 1 && d == 2))
			ans += dfs(pos - 1, 2, flag || d < u);
		else if(d == 6)
			ans += dfs(pos - 1, 1, flag || d < u);
		else 
			ans += dfs(pos - 1, 0, flag || d < u);
	}
	if(flag)
		dp[pos][st] = ans;
	return ans;
}

int solve(int n)
{
	int len = 0;
	while(n)
	{
		bit[++len] = n%10;
		n /= 10;
	}
	return dfs(len, 0, 0);
}

int main()
{
	int n, m;
	memset(dp, -1, sizeof(dp));
	while(scanf("%d %d", &n, &m) != EOF && (n+m))
	{
		printf("%d\n", m-n+1-(solve(m)-solve(n-1)));
	}
	return 0;
}
