#include <iostream>
#include <cstdio>
#include <algorithm>
using namespace std;

const int maxn = 200001, maxd = 3000000;
struct Node
{
	int l, r, lc, rc, s;
	Node(){};
	Node(int l, int r, int lc, int rc, int s)
		:l(l), r(r), lc(lc), rc(rc), s(s){}
}tree[maxd];
int n, m, tot;
int org[maxn], b[maxn], root[maxn];

int build(int l, int r)
{
	if(l > r) return 0;
	int rt = ++tot;
	tree[rt] = Node(l, r, 0, 0, 0);
	if(l == r) return rt;
	int m = (l + r) >> 1;
	tree[rt].lc = build(l, m);
	tree[rt].rc = build(m+1, r);
	return rt;
}

int change(int rt, int p, int w)
{
	int k = ++tot;
	tree[k] = Node(tree[rt].l, tree[rt].r, tree[rt].lc, tree[rt].rc, tree[rt].s+w); 
	if(tree[rt].l == p && p == tree[rt].r)
		return k;
	int m = (tree[rt].l + tree[rt].r) >> 1;
	if(p <= m)
		tree[k].lc = change(tree[rt].lc, p, w);
	else
		tree[k].rc = change(tree[rt].rc, p, w);
	return k;
}

int query(int rt1, int rt2, int k)
{
	if(tree[rt1].l == tree[rt2].r)
		return tree[rt1].l;
	int t = tree[tree[rt1].lc].s - tree[tree[rt2].lc].s;
	if(k <= t)
		return query(tree[rt1].lc, tree[rt2].lc, k);
	return query(tree[rt1].rc, tree[rt2].rc, k-t);
}

int main()
{
	while(scanf("%d %d", &n, &m) != EOF)
	{
		for(int i=1; i<=n; i++)
		{
			scanf("%d", &org[i]);
			b[i] = org[i];	
		}
		sort(b+1, b+n+1);
		int q = unique(b+1, b+n+1) - b - 1;
		tot = 1;
		root[0] = build(1, q);
		for(int i=1; i<=n; i++)
			root[i] = change(root[i-1], lower_bound(b+1, b+n+1, org[i])-b, 1);

		while(m --)
		{
			int x, y, k;
			scanf("%d %d %d", &x, &y, &k);
			printf("%d\n", b[query(root[y], root[x-1], k)]);
		}
	}
	return 0;
}

