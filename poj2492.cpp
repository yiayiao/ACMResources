/*
Problem: 2492		User: heike520
Memory: 704K		Time: 844MS
Language: G++		Result: Accepted
Source Code
*/
#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

const int M = 2010;
int relative[M], fa[M];

void init(int n)
{
	for(int i=1;i<=n;i++)
	{
		fa[i] = i;
		relative[i] = 0;
	}
}

int find(int x)
{
	if(x != fa[x])
	{
		int temp = fa[x];
		fa[x] = find(fa[x]);
		if(relative[temp] != 0)
			relative[x] = 1 - relative[x];
	}
	return fa[x];
}

int _union(int x, int y)
{
	int fx = find(x);
	int fy = find(y);
	fa[fy] = fx;
	if(relative[x] != relative[y])
		relative[fy] = 0;
	else
		relative[fy] = 1;
}

int main()
{
	int T, cas, n, m, x, y;
	scanf("%d", &T);
	for(cas = 1; cas <= T; cas ++)
	{
		scanf("%d %d", &n, &m);
		init(n);
		bool flag = false;
		while(m --)
		{
			scanf("%d %d" , &x, &y);
			int fx = find(x);
			int fy = find(y);
			if(fx == fy && relative[x] == relative[y])
				flag = true;
			else
				_union(x, y);
		}
		printf("Scenario #%d:\n", cas);
		if(flag)
			printf("Suspicious bugs found!\n\n");
		else
			printf("No suspicious bugs found!\n\n");
		
	}
	return 0;
}
