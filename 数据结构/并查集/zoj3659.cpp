
#include <iostream>
#include <cstring>
#include <cstdio>
#include <algorithm>
using namespace std;

const int M = 200010;

struct Node
{
	int u,v;
	long long cost;
	friend bool operator<(Node a,Node b)
	{
		return a.cost > b.cost ;
	}
}node[M];

int n;	//
int root[M<<2], son[M<<2];
long long dp[M<<2];

int find(int a)
{
	if(root[a] == -1)
		return a;
	int tt = find(root[a]);
	dp[a] += dp[root[a]];
	root[a] = tt;
	return tt;
}

int pre;	//初始为n
void _union(int a,int b,long long cost)
{
	a = find(a);
	b = find(b);
	if(a == b)
		return ;
	dp[a] += cost*son[b];
	dp[b] += cost*son[a];
	son[pre] = son[a] + son[b];		//有多少个分支
	root[a] = root[b] = pre;
	pre ++;
}

void init()
{
	memset(root,-1,sizeof(root));
	memset(dp,0,sizeof(dp));
	fill(son,son+n+10,1);
	pre = n+2;
}

int main()
{
	while(scanf("%d",&n) != EOF)
	{
		for(int i=1;i<n;i++)
			scanf("%d%d%lld", &node[i].u,&node[i].v,&node[i].cost);
		sort(node+1,node+n);
		init();
		for(int i=1;i<n;i++)
			_union(node[i].u, node[i].v, node[i].cost);
		
		long long ans = 0;
		for(int i=1;i<=n;i++)
		{
			find(i);
			ans = max(ans, dp[i]);
		}
		printf("%lld\n", ans);
	}
	return 0;
}