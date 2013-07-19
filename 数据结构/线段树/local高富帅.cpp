/*
问题描述

高富帅的三个特征 --高 ，富 ， 帅。如果一个人发现有人比自己高，比自己富，比自己帅。那么他就认为自己是屌丝。。

现在总共有N个人，让你统计总共有多少只屌丝。

输入说明

第一行一个整数N （N <= 500000）

接下来N行。每行三个整数。a,b,c。分别表示高，富，帅的程度。（0 <= a,b,c <= 10^9，a值越大表示越高。b,c同理）

输出说明

输入样例

9
48 9 5
89 69 84
85 95 22
52 96 90
50 15 45
85 80 21
36 1 44
100 90 10
86 44 43
输出样例

4

*/

#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#define lson l, m, rt<<1
#define rson m+1, r, rt<<1|1
using namespace std;

const int N = 500010;
struct Node
{
	int g, f, s;
}node[N];
int n;

int tree[N<<2];
int query(int L, int R, int l, int r, int rt)
{
	if(L <= l && R <= r)
		return tree[rt];
	int m = (l + r) >> 1;
	if(R <= m)
		return query(L, R, lson);
	else if(L > m)
		return query(L, R, rson);
	else
	{
		int ret = query(L, m, lson);
		ret = max(ret, query(m+1, R, rson));
		return ret;
	}
}

void update(int id, int num, int l, int r, int rt)
{
	if(l == r)
	{
		tree[rt] = max(tree[rt], num);
		return ;
	}
	int m = (l + r) >> 1;
	if(id <= m)
		update(id, num, lson);
	else
		update(id, num, rson);
	tree[rt] = max(tree[rt<<1], tree[rt<<1|1]);
}

bool cmpg(Node a, Node b)
{
	return a.g < b.g;
}

bool cmpf(Node a, Node b)
{
	return a.f > b.f;
}

int main()
{
	while(scanf("%d", &n) != EOF)
	{
		memset(tree, 0, sizeof(tree));
		for(int i=0; i<n; i++)
		{
			scanf("%d %d %d", &node[i].g, &node[i].f, &node[i].s);
		}
		sort(node, node + n, cmpg);
		int pre = node[0].g, high = 1;
		node[0].g = high;
		for(int i=1; i<n; i++)
		{
			int tmp = node[i].g;
			if(node[i].g == pre)
				node[i].g = high;
			else
				node[i].g = ++high;
			pre = tmp;
		}
		high ++;

		int ans = 0;
		sort(node, node + n, cmpf);
		for(int i=0; i<n;)
		{
			int k = i;
			while(k < n && node[i].f == node[k].f)
			{
				if(query(node[k].g+1, high, 1, high, 1) > node[k].s)
					ans ++;
				k ++;
			}
			while(i < k)
			{
				update(node[i].g, node[i].s, 1, high, 1);
				i ++;
			}
		}
		printf("%d\n", ans);
	}
	return 0;
}
