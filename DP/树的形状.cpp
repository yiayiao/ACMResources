/*
对于一个给定高度K和节点数N的完全二叉树，给出他一共有多少种不同的形态。
TIPS：完全二叉树要么没有子树，要么一定左右子树都有。
有多组数据 
每组数据一行 两个数 N （1<=N<=200）,K（1<=K<=100）

使用的编译器	GPP
运行使用时间	64 Ms
运行使用内存	1724 Kb
*/
#include <iostream>
#include <cstring>
#include <cstdio>
#include <algorithm>
using namespace std;

const int mod = 9901;
const int M = 204, K = 104;
int dp[M][K];	//dp[i][j] 表示节点上为i，小于等于j层的不同形状的树的个数

void init()
{
	for(int i=1; i<K; i++)
		dp[1][i] = 1;
	for(int i=3; i<M; i++)
		for(int j=2; j<K; j++)
		{
			dp[i][j] = dp[i][j-1];
			for(int k=1; k<=i-2; k++)
			{
				dp[i][j] += (dp[k][j-1]-dp[k][j-2]+mod)%mod*dp[i-1-k][j-2]*2;
				dp[i][j] %= mod;
				dp[i][j] += (dp[k][j-1]-dp[k][j-2]+mod)%mod*(dp[i-1-k][j-1]-dp[i-1-k][j-2]+mod)%mod;	
				dp[i][j] %= mod;
			}
		}
}

int main()
{
	init();
	int n, k;
	while(scanf("%d %d", &n, &k)!=EOF)
		printf("%d\n", (dp[n][k] - dp[n][k-1] + mod)%mod);
	return 0;
}
