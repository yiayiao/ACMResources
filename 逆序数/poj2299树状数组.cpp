#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
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
int a[M],c[M];

int lowbit(int x)
{
	return x&(-x);
}
void update(int x,int val)
{
	while(x<=M)
	{
		c[x]+= val;
		x+= lowbit(x);
	}
}
int query(int x)
{
	long long ans = 0;
	while(x>0)
	{
		ans += c[x];
		x -= lowbit(x);
	}
	return ans;
}

int main()
{
	int n;
	while(scanf("%d",&n) && n)
	{	
		memset(c,0,sizeof(c));
		for(int i=1;i<=n;i++)
		{
			scanf("%d",&node[i].y);
			node[i].x = i;
		}
		sort(node+1,node+n+1);
		for(int i=1;i<=n;i++)
		{
			a[node[i].x ] = i;
		}

		//for(int i=1;i<=n;i++)
		//	cout<<a[i]<<" ";
		//cout<<endl;

		long long total = 0;
		for(int i=1;i<=n;i++)
		{
			update(a[i],1);
			//cout<<query(a[i])<<" ";
			total += i-query(a[i]);	// i位之前应该有i个比它小的数，实际有query(a[i])个
		}
		printf("%lld\n",total);

	}
	return 0;
}

