#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

const int maxn = 210;
int n, num[maxn];
double p[maxn], dp[maxn][22][2];
char op[maxn][3];


int main()
{
	int cas = 0;
	while(scanf("%d", &n) != EOF)
	{
		for(int i=0; i<=n; i++)
			scanf("%d", &num[i]);
		for(int i=1; i<=n; i++)
			scanf("%s", op[i]);
		for(int i=1; i<=n; i++)
			scanf("%lf", &p[i]);
		memset(dp, 0, sizeof(dp));
		double ans = 0;
		for(int k=0; k<=20; k++)
		{
			if(num[0] & (1<<k)) dp[0][k][1] = 1;
			else dp[0][k][0] = 1;
			for(int i=1; i<=n; i++)
			{
				dp[i][k][0] = dp[i-1][k][0] * p[i];
				dp[i][k][1] = dp[i-1][k][1] * p[i];
				if(num[i] & (1<<k)) // 1
				{
					if(op[i][0] == '|')
					{
						dp[i][k][1] += dp[i-1][k][0] * (1-p[i]);
						dp[i][k][1] += dp[i-1][k][1] * (1-p[i]);
					}
					else if(op[i][0] == '&')
					{
						dp[i][k][0] += dp[i-1][k][0] * (1-p[i]);
						dp[i][k][1] += dp[i-1][k][1] * (1-p[i]);
					}
					else if(op[i][0] == '^')
					{
						dp[i][k][1] += dp[i-1][k][0] * (1-p[i]);
						dp[i][k][0] += dp[i-1][k][1] * (1-p[i]);
					}
				}
				else // 0
				{
					if(op[i][0] == '|')
					{
						dp[i][k][1] += dp[i-1][k][1] * (1-p[i]);
						dp[i][k][0] += dp[i-1][k][0] * (1-p[i]);
					}
					else if(op[i][0] == '&')
					{
						dp[i][k][0] += dp[i-1][k][0] * (1-p[i]);
						dp[i][k][0] += dp[i-1][k][1] * (1-p[i]);
					}
					else if(op[i][0] == '^')
					{
						dp[i][k][1] += dp[i-1][k][1] * (1-p[i]);
						dp[i][k][0] += dp[i-1][k][0] * (1-p[i]);
					}
				}
			}
			ans += (1<<k) * dp[n][k][1];
		}
		printf("Case %d:\n%.6f\n",++cas ,ans);
	}
	return 0;
}
