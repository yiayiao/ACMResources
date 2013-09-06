/*
我们现在定义Insert(p, d)表示把区间[1..p]都加d，Query(p)表示查询区间[1..p]之和。
考虑调用一次Insert(p, d)对以后的某次查询Query(q)的影响：
(1) 如果p<=q，总的结果会加上p*d 
(2) 如果p>q，总的结果会加上q*d
也就是说，Query(q)的结果来源可分为两部分：一部分是Insert(p1,d) (p1<=q)，一部分是Insert(p2,d) (p2 > q)。
我们用两个数组B[], C[]分别维护这两部分信息：B[i]表示区间右端点恰好是i的所有区间的影响之和，C[i]表示区间右端点大于i的所有区间的影响之和。每当遇到 Insert时，考虑当前的Insert会对以后的Query产生什么影响，更新B和C数组；当遇到Query时，把两部分的结果累加起来。
具体来说，当我们遇到Insert(p, d)时，把B[p]增加p*d，把C[1], C[2], …, C[p-1]都增加d。当遇到Query(p)时，查询B[1]+B[2]+…+B[p]+C[p]*p即可。可以发现对B数组是修改单个元素，查询区间和；而对C数组是修改区间，查询单个元素，正好对应了上面的两种数组操作模式。
 */
#include <iostream>
#include <cstring>
#include <algorithm>
#include <cstdio>
#include <vector>
using namespace std;

const int maxn = 100010;
long long B[maxn], C[maxn], org[maxn];

int lowbit(int x)
{
	return x & (-x);
}

void bit_update(long long *a, int p, int d)
{
	while(p < maxn)
	{
		a[p] += d;
		p += lowbit(p);
	}
}

void bit_update2(long long *a, int p, int d)
{
	while(p > 0)
	{
		a[p] += d;
		p -= lowbit(p);
	}
}

long long bit_query(long long *a, int p)
{
	long long s = 0;
	while(p > 0)
	{
		s += a[p];
		p -= lowbit(p);
	}
	return s;
}

long long bit_query2(long long *a, int p)
{
	long long s = 0;
	while(p < maxn)
	{
		s += a[p];
		p += lowbit(p);
	}
	return s;
}

void insert(int p, int d)
{
	bit_update(B, p, p*d);
	bit_update2(C, p-1, d);
}

long long query(int p)
{
	return bit_query(B, p) + bit_query2(C, p)*p;
}

void insert_seg(int a, int b, int d)
{
	insert(a-1, -d);
	insert(b, d);
}

long long query_seg(int a, int b)
{
	return org[b] - org[a-1] + query(b) - query(a-1);
}

int main()
{
	int n, m;
	scanf("%d %d", &n, &m);
	for(int i=2; i<=n+1; i++)
	{
		scanf("%lld", &org[i]);
		org[i] += org[i-1];
	}
	while(m --)
	{
		char op[3];
		int l, r, d;
		scanf("%s %d %d", op, &l, &r);
		l ++, r ++;
		if(op[0] == 'C')
		{
			scanf("%d", &d);
			insert_seg(l, r, d);
		}
		else
			printf("%lld\n", query_seg(l, r));
	}
	return 0;
}
