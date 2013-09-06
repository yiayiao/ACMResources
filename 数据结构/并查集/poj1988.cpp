#include <iostream>
#include <cstring>
#include <algorithm>
#include <cstdio>
using namespace std;

const int M = 30005;
int fa[M], sum[M], up[M];

void init(int n)
{
	for(int i=1;i<=n;i++)
	{
		fa[i] = i;
		sum[i] = 1;
		up[i] = 0;
	}
}

int find(int a)
{
	if(fa[a] != a)
	{
		int father = fa[a];
		fa[a] = find(father);
		up[a] += up[father];
	}
	return fa[a];
}

void _union(int a, int b)
{
	a = find(a);
	b = find(b);
	if(a == b)
		return ;
	fa[b] = a;
	up[b] += sum[a];
	sum[a] += sum[b];
}

int main()
{
	int p, x, y;
	char op[2];
	init(M);
	scanf("%d", &p);
	while(p --)
	{
		scanf("%s", op);
		if(op[0] == 'M')
		{
			scanf("%d %d", &x, &y);
			_union(x, y);
		}
		else
		{
			scanf("%d", &x);
			int ans = sum[find(x)] - up[x] - 1;
			printf("%d\n", ans);
		}
	}
	return 0;
}