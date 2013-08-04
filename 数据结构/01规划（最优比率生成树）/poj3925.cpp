/*
使用的编译器 G++
运行使用时间 16 Ms
运行使用内存 692 Kb
*/
#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

const int maxn = 17, inf = 0x7ffffff;
int n, m;
int dis[maxn][maxn], num[maxn], ans[maxn];
int f_ans[maxn], p1, p2;

int prim()
{
	bool vis[maxn];
	int dd[maxn], ret = 0;
	memset(vis, 0, sizeof(vis));
	vis[ans[0]] = true;
	dd[ans[0]] = 0;
	for(int i=1; i<m; i++)
		dd[ans[i]] = dis[ans[0]][ans[i]];
	for(int i=1; i<m; i++)
	{
		int tmp = inf, p = -1;
		for(int i=0; i<m; i++)
			if(!vis[ans[i]] && dd[ans[i]] < tmp)
			{
				tmp = dd[ans[i]];
				p = ans[i];
			}
		vis[p] = true;
		ret += dd[p];
		for(int i=0; i<m; i++)
			if(!vis[ans[i]] && dd[ans[i]] > dis[p][ans[i]])
				dd[ans[i]] = dis[p][ans[i]];
	}
	return ret;
}

void dfs(int id, int r_m)
{
	if(r_m == m)
	{
		int bian = prim(), cot = 0;
		for(int i=0; i<m; i++)
			cot += num[ans[i]];
		//cout<<"-->"<<bian<<" "<<cot<<endl;
		if(p1*cot > p2*bian)
		{
			memcpy(f_ans, ans, sizeof(int)*m);
			p1 = bian, p2 = cot;
		}
		return;
	}
	if((m - r_m) + id - 1> n)
		return ;
	ans[r_m] = id;
	dfs(id+1, r_m+1);
	dfs(id+1, r_m);
}

int main()
{
	while(scanf("%d %d", &n, &m) && (m+n))
	{
		for(int i=1; i<=n; i++)
		{
			scanf("%d", &num[i]);
		}
		for(int i=1; i<=n; i++)
			for(int j=1; j<=n; j++)
			{
				scanf("%d", &dis[i][j]);
			}
		p1 = 100000, p2 = 0;
		dfs(1, 0);
		for(int i=0; i<m-1; i++)
			printf("%d ", f_ans[i]);
		printf("%d\n", f_ans[m-1]);
	}
	return 0;
}
