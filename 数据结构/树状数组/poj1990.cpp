#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>
using namespace std;

const int maxn = 20010;
struct Node
{
	int x, v;
	bool operator< (Node b) const
	{
		if(v == b.v) return x < b.x;
		return v < b.v;
	}
}cow[maxn];

int lowbit(int x)
{
	return x&(-x);
}

void modify(int array[], int pos, int num, int n)
{
	while(pos <= n)
	{
		array[pos] += num;
		pos += lowbit(pos);
	}
}

int quary(int array[], int pos)
{
	int sum = 0;
	while(pos> 0)
	{
		sum += array[pos];
		pos -= lowbit(pos);
	}
	return sum;
}

int xcot[maxn], xtot[maxn];

int main()
{
	int n, xmax;
	while(scanf("%d", &n) != EOF)
	{
		xmax = 0;
		for(int i=0; i<n; i++)
		{
			scanf("%d%d", &cow[i].v, &cow[i].x);
			if(cow[i].x > xmax)
				xmax = cow[i].x;
		}
		sort(cow, cow + n);
		memset(xcot, 0, sizeof(xcot));
		memset(xtot, 0, sizeof(xtot));

		modify(xcot, cow[0].x, 1, xmax);
		modify(xtot, cow[0].x, cow[0].x, xmax);
		long long ans = 0, tmp = 0, all = cow[0].x;
		for(int i=1; i<n; i++)
		{
			long long count = quary(xcot, cow[i].x);
			long long stotal = quary(xtot, cow[i].x), btotal = all - stotal;
			tmp = (count*cow[i].x - stotal) + (btotal - (i - count)*cow[i].x);
			ans += tmp*cow[i].v;
			all += cow[i].x;
			modify(xcot, cow[i].x, 1, xmax);
			modify(xtot, cow[i].x, cow[i].x, xmax);
		}
		printf("%lld\n", ans); 
	}
	return 0;
}
