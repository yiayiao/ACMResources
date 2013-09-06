/*用树状数组求解区间更新（区间数均加上num）与区间查询（求和）题目
 *1.更新(s到t的区间同时加上d)：
 *	add[s] = add[s] + d, 表示将num[s..n]同时加上d;
 *	这样t+1到n的区间就多加了d，所以有 add[t+1] = add[t+1] - d，表示将num[t+1..n]同时减去d;
 *2.查询(query(s,t) 查询s到t的区间和)
 * 	转化为求前缀和 num[s] + .. + num[t] = sum[t] - sum[s-1]
 *	前缀和sum[x]由两部分组，一是数组的原始和，二是该区间内的累计增量和.
 *		数组的原始和为org[x]，预处理
 *		数组的累积增量和与add[]有关，add[i]对sum[x]的贡献为add[i]*(x+1-i)
 *	sum[x] = org[1]+..+org[x] + add[1]*x+add[2]*(x-1)+..+add[x]*1
 *		   = segma(org[i]) + segma(add[i]*(x+1-i))		1<=i<=x
 *		   = segma(org[i]) + (x+1)*segma(add[i]) - segma(add[i]*i) 	1<=i<=x
 *		sum[x]实际是就是org[i], add[i], add[i]*i的前缀和
 */
#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

typedef long long LL;
const int maxn = 100010;
LL add[2][maxn], org[maxn];
int n, q;

int lowbit(int x)
{
	return x & (-x);
}

void update(int id, int x, int ins)
{
	while(x <= n)
	{
		add[id][x] += ins;
		x += lowbit(x);
	}
}

LL query(int id, int x)
{
	LL ret = 0;
	while(x > 0)
	{
		ret += add[id][x];
		x -= lowbit(x);
	}
	return ret;
}

int main()
{
	while(scanf("%d %d", &n, &q) != EOF)
	{
		memset(add, 0, sizeof(add));
		for(int i=1; i<=n; i++)
		{
			scanf("%lld", &org[i]);
			org[i] += org[i-1];
		}
		while(q --)
		{
			char op[2];
			int s, t, ins;
			scanf("%s %d %d", op, &s, &t);
			if(op[0] == 'Q')
			{
				LL ans = org[t] - org[s-1];
				ans += (t+1)*query(0, t) - s*query(0, s-1);
				ans -= query(1, t) - query(1, s-1);
				printf("%lld\n", ans);
			}
			else
			{
				scanf("%d", &ins);
				update(0, s, ins), update(0, t+1, -ins);
				update(1, s, ins*s), update(1, t+1, -ins*(t+1));
			}
		}
	}
	return 0;
}
