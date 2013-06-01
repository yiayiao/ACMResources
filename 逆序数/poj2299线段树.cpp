#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
#define lson l, m, rt<<1
#define rson m+1, r, rt<<1|1
using namespace std;

const int M = 500002;

struct Node
{
	int x,y;
	friend bool operator<(Node a, Node b)
	{
		return a.y < b.y;
	}
}node[M];
int tmp[M], num[M];
int tree[M<<2];

void build(int l, int r, int rt)
{
	tree[rt] = 0;
	if(l == r)
		return ;
	int m = (l + r) >> 1;
	build(lson);
	build(rson);
}

void update(int q, int l, int r, int rt)
{
	if(l == r)
	{
		tree[rt] ++;
		return;
	}
	int m = (l + r) >> 1;
	if(q <= m)
		update(q, lson);
	else
		update(q, rson);
	tree[rt] = tree[rt<<1] + tree[rt<<1|1];
}

int query(int L, int R, int l, int r, int rt)
{
	if(L <= l && r <= R)
		return tree[rt];
	int m = (l + r) >>1;
	int ret = 0;
	if(L <= m)
		ret += query(L, R, lson);
	if(R > m)
		ret += query(L, R, rson);
	return ret;
}

int main()
{
	int n;
	while(scanf("%d",&n) && n)
	{	
		for(int i=1;i<=n;i++)
		{
			scanf("%d",&node[i].y);
			node[i].x = i;
		}
		sort(node+1,node+n+1);
		for(int i=1;i<=n;i++)
		{
			tmp[node[i].x ] = i;
		}

		build(1, n, 1);
		long long total = 0;
		for(int i=1;i<=n;i++)
		{
			total += query(tmp[i], n, 1, n, 1);
			update(tmp[i], 1, n, 1);
		}
		printf("%lld\n",total);

	}
	return 0;
}