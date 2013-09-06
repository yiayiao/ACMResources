#include <iostream>
#include <cstring>
#include <cstdio>
#include <algorithm>
#include <vector>
using namespace std;

const int maxn = 40010;
const int maxm = 10010;
int hen[maxn], su[maxn], fa[maxn], n, m;

void init(int n)
{
	for(int i=1; i<=n; i++)
	{
		hen[i] = su[i] = 0;
		fa[i] = i;
	}
}

int find(int x)
{
	if(x != fa[x])
	{
		int tmp = fa[x];
		fa[x] = find(tmp);
		hen[x] += hen[tmp];
		su[x] += su[tmp];
	}
	return fa[x];
}

void _union(int x, int y, int l, char d)
{
	int xx = find(x), yy = find(y);
	fa[xx] = yy;
	if(d == 'E')
	{
		hen[xx] = hen[y] - hen[x] + l;
		su[xx] = su[y] - su[x];
	}
	else if(d == 'W')
	{
		hen[xx] = hen[y] - hen[x] - l;
		su[xx] = su[y] - su[x];
	}
	else if(d == 'N')
	{
		hen[xx] = hen[y] - hen[x];
		su[xx] = su[y] - su[x] - l;
	}
	else
	{
		hen[xx] = hen[y] - hen[x];
		su[xx] = su[y] - su[x] + l;
	}
}

struct Node
{
	int s, e, l;
	char st[3];
}node[maxn];

struct Query
{
	int s, e, id;
	Query(int a, int b, int c): s(a), e(b), id(c){}
};
vector<Query> ve[maxn];
int ans[maxn];

int main()
{
	while(scanf("%d %d", &n, &m) != EOF)
	{
		for(int i=1; i<=m; i++)
		{
			scanf("%d %d %d %s", &node[i].s, &node[i].e, &node[i].l, node[i].st);
			ve[i].clear();
		}
		int q, s, e, id;
		scanf("%d", &q);
		for(int i=1; i<=q; i++)
		{
			scanf("%d %d %d", &s, &e, &id);
			ve[id].push_back(Query(s, e, i));
		}

		init(n);
		for(int i=1; i<=m; i++)
		{
			_union(node[i].s, node[i].e, node[i].l, node[i].st[0]);
			for(int j=0; j<ve[i].size(); j++)
			{
				int s = ve[i][j].s, e = ve[i][j].e;
				if(find(s) != find(e))
					ans[ve[i][j].id] = -1;
				else
				{
					cout<<find(s)<<" "<<hen[s]<<" "<<hen[e]<<" "<<su[s]<<" "<<su[e]<<endl;
					ans[ve[i][j].id] = abs(hen[s] - hen[e]) + abs(su[s] - su[e]);
				}
			}
		}

		for(int i=1; i<=q; i++)
		{
			printf("%d\n", ans[i]);
		}
	}
	return 0;
}
