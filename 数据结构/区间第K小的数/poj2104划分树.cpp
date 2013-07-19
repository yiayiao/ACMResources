#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
using namespace std;

const int M = 100010;
int tree[22][M],toleft[22][M];
int sorted[M];

void build(int left,int right,int deep)
{
	if(left == right) return;
	int mid = (left+right)>>1;
	int ls = left, rs = mid+1;
	for(int i=left; i<=right; i++)
	{
		if(tree[deep][i] <= sorted[mid])
		{
			toleft[deep][i] = toleft[deep][i-1]+1;
			tree[deep+1][ls++] = tree[deep][i];
		}
		else
		{
			toleft[deep][i] = toleft[deep][i-1];
			tree[deep+1][rs++] = tree[deep][i];
		}
      
	}
	build(left,mid,deep+1);
	build(mid+1,right,deep+1);
}

int query(int left,int right,int k,int L,int R,int deep)
{
	if(left == right)
		return tree[deep][left];
	int mid = (L+R)>>1;
	int x = toleft[deep][left-1] - toleft[deep][L-1];
	int y = toleft[deep][right] - toleft[deep][L-1];
	int ry = right-L-y, rx = left-L-x;
	int cnt = y-x;
	if(cnt >= k)
		return query(L+x, L+y-1, k, L, mid, deep+1);
	else
		return query(mid+rx+1, mid+ry+1, k-cnt, mid+1, R, deep+1);
}

int main()
{
	int n,m;
	while(scanf("%d%d",&n,&m) == 2)
	{
		for(int i=1;i<=n;i++)
		{
			scanf("%d",&sorted[i]);
			tree[0][i] = sorted[i];
		}
		sort(sorted+1, sorted+n+1);
		build(1,n,0);
		while(m--)
		{	
			int left,right,k;
			scanf("%d%d%d",&left,&right,&k);
			printf("%d\n",query(left,right,k,1,n,0));
		}
	}
	return 0;
}

