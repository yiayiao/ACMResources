#include <iostream>
#include <cstring>
#include <algorithm>
#include <cstdio>
using namespace std;

const int maxn = 100010;
int n, m, num[maxn], ans[maxn], tree[maxn];
struct Node
{
	int l, r, op, id;
	bool operator<(const Node b) const 
	{
		if(r != b.r)
	   		return r < b.r; 
		return op < b.op;
	}
}node[maxn<<1];

int lowbit(int x)
{
	return x & (-x);
}

int query(int x)
{
	int cot = 0;
	while(x > 0)
	{
		cot += tree[x];
		x -= lowbit(x);
	}
	return cot;
}

void update(int x)
{
	while(x <= n)
	{
		tree[x] ++;
		x += lowbit(x);
	}
}

int main()
{
	int cas;
	scanf("%d", &cas);
	while(cas --)
	{
		scanf("%d %d", &n, &m);
		for(int i=1; i<=n; i++)
		{
			int n;
			scanf("%d", &n);
			num[n] = i;
		}
		for(int i=1; i<n; i++)
		{
			node[i].l = min(num[i], num[i+1]);
			node[i].r = max(num[i+1], num[i]);
			node[i].op = 1;
		}
		for(int i=n; i<m+n; i++)
		{
			int l, r;
			scanf("%d %d", &l, &r);
			node[i].l = l, node[i].r = r;
			node[i].op = 2;
			node[i].id = i-n;
		}

		sort(node+1, node+n+m);
		memset(tree, 0, sizeof(int)*(n+10));
		for(int i=1; i<m+n; i++)
		{
		//	cout<<node[i].l<<" "<<node[i].r<<" "<<node[i].op<<endl;
			if(node[i].op == 1)
				update(node[i].l);
			else
				ans[node[i].id] = node[i].r - node[i].l + 1 - (query(node[i].r) - query(node[i].l - 1));
		}
		for(int i=0; i<m; i++)
		{
			printf("%d\n", ans[i]);
		}
	}
	return 0;
}
