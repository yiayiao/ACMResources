//自己还是比较缺乏大胆猜测的能力，其实很多题目并不高深，基础的知识解决大问题
#include <iostream>
#include <cstring>
#include <cstdio>
using namespace std;

const int mod = 10007, maxn = 10100;
char str[10100];
int dp[maxn];

void init()
{
	dp[0] = 1, dp[1] = 1;
	for(int i=2; i<maxn; i++)
		dp[i] = (dp[i-1] + dp[i-2]) % mod;	//时时刻刻想着要模除
}

int main()
{
	int t;
	init();
	scanf("%d", &t);
	for(int cas = 1; cas <= t; cas ++)
	{
		scanf("%s", str);
		int he = 0, len = strlen(str), ans = 1;
		if(len == 0) ans = 0;
		for(int i=0; i<len-1; i++)
		{
			while(i < len-1 && str[i] == 'h' && str[i+1] == 'e')
			{
				i += 2;
				he ++;
			}
			ans = (ans * dp[he]) % mod;
			he = 0;
		}
		printf("Case %d: %d\n", cas, ans);
	}
	return 0;
}
