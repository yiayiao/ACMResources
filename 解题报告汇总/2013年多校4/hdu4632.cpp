#include <cstdio>
#include <cstring>

const int maxn = 1010, mod = 10007;
char str[maxn];
int dp[maxn][maxn];

int main()
{
	int cas;
	scanf("%d", &cas);
	for(int t = 1; t <= cas; t++)
	{
		scanf("%s", str);
		int len = strlen(str);
		memset(dp, 0, sizeof(dp));
		for(int i=0; i<len; i++)
			dp[i][i] = 1;
		for(int i=1; i<len; i++)
		{
			for(int j=i-1; j>=0; j--)
			{
				dp[j][i] = (dp[j+1][i] + dp[j][i-1] - dp[j+1][i-1] + mod) % mod;
				if(str[i] == str[j])
					dp[j][i] = (dp[j][i] + dp[j+1][i-1] + 1 + mod) % mod;
			}
		}
		printf("Case %d: %d\n", t, dp[0][len-1]);
	}
	return 0;
}
