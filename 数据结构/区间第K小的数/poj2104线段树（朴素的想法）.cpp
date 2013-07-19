//poj 2104 区间内第k小的数
#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

const int ex = 20, maxn = 100104;
// 对于当前的num, rankL表示lower_bound(a+l, a+r,  num), rankR表示upper_bound(a+l, a+r, num);
// 若对于查询的num, 在[l,r]中的rankL = rankR = k, 则num为第k大数
int n, m, rankL, rankR;
int rank[ex][maxn], b[maxn];

//对rank的每一层进行赋值与排序
void mergesort(int l, int r, int dep)
{
	if(l >= r)
		return;
	int m = (l + r) >> 1;
	mergesort(l, m, dep+1);
	mergesort(m+1, r, dep+1);
	int lm = l, rm = m+1, id = l;
	while(lm <=m && rm <=r)
	{
		if(rank[dep+1][lm] <= rank[dep+1][rm])
			rank[dep][id++] = rank[dep+1][lm++];
		else
			rank[dep][id++] = rank[dep+1][rm++];
	}
	while(lm <= m)
	{
		rank[dep][id++] = rank[dep+1][lm++];
	}
	while(rm <= r)
	{
		rank[dep][id++] = rank[dep+1][rm++];
	}
}

void process()
{
	for(int i=0; i<ex; i++)
		memcpy(rank[i], b, sizeof(int)*n);
	mergesort(0, n-1, 0);
}

// if (judge == 0), 那么就返回大于等于某数的最小位置(和rankL相关)
// if (judge == 1), 那么就返回大于某数的最小位置(和rankR相关)
int binsearch(int x, int y, int num, int dep, int judge) 
{
	y++;
	int ll = x;
	while (y > x) 
	{
		int mid = (x+y) / 2;
		if (rank[dep][mid] - num >= judge) 
			y = mid;
		else 
			x = mid+1;
	}
	return x-ll;
}

void query(int ll, int rr, int l, int r, int num, int dep)
{
	if(ll == l && rr == r)
	{//rank[dep][ll...rr]有序,而我们需要查找num在b[l(=ll)...r(=rr)]的位置, 所以就可以直接二分查找求位置了.
		rankL += binsearch(ll, rr, num, dep, 0);
		rankR += binsearch(ll, rr, num, dep, 1);
		return ;
	}
	if(r < ll || l > rr) return ;
	int mid = (ll + rr) >> 1;
	query(ll, mid, l, min(mid, r), num, dep+1);
	query(mid+1, rr, max(l, mid+1), r, num, dep+1);
}

void solve(int lef, int rig, int k) 
{
	int x = 0;
	int y = n-1;
	int mid = (x+y) / 2;
	while (true) 
	{
		mid = (x+y) / 2;
		rankL=0, rankR=0;
		query(0, n-1, lef, rig, rank[0][mid], 0); // 求数a[0][mid]的位置[rankL, rankR)
		if (rankL<=k && k<rankR) break; // 数a[0][mid]就是所求的数
		if (k >= rankR) 
			x = mid+1; // a[0][mid]较小, 也就是mid的位置较低, 于是取[x...y]区间的右边, 继续迭代
		else 
			y = mid; // a[0][mid]较大, 也就是mid的位置较高, 于是取[x...y]区间的左边, 继续迭代
	}
	printf("%d\n", rank[0][mid]);
}

int main()
{
	while(scanf("%d %d", &n, &m) != EOF)
	{
		for(int i=0; i<n; i++)
		{
			scanf("%d", &b[i]);
		}
		process();
		while(m --)
		{
			int left, right, k;
			scanf("%d %d %d", &left, &right, &k);
			solve(left-1, right-1, k-1);
		}
	}
	return 0;
}
