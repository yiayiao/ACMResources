/*
Problem: 2976		User: heike520
Memory: 208K		Time: 63MS
Language: C++		Result: Accepted
*/
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cmath>
using namespace std;
#define N 1005
#define eps 1e-6
struct Node
{
	double a,b,v;
	bool operator<(const Node c) const
	{
		return v>c.v;
	}
}node[N];

int main()
{
	int n,m;
	while(scanf("%d%d",&n,&m) && (n+m))
	{
		m = n-m;
		for(int i=0;i<n;i++)
			scanf("%lf",&node[i].a);
		for(int i=0;i<n;i++)
			scanf("%lf",&node[i].b);
		double ans = 0,temp;
		while(true)
		{
			for(int i=0;i<n;i++)
				node[i].v = node[i].a - node[i].b*ans;
			sort(node,node+n);
			double suma = 0,sumb = 0;
			for(int i=0;i<m;i++)
			{
				suma += node[i].a;
				sumb += node[i].b;
			}
			temp = suma/sumb;
			if(fabs(temp-ans)<eps)
				break;
			ans = temp;
		}
		printf("%d\n",(int)(100 *(ans+0.005)));	
	}
	return 0;
}