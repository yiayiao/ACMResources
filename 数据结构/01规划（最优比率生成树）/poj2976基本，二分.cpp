#include <iostream>
#include <cstdio>
#include <algorithm>
using namespace std;
#define eps 1e-4
#define N 1005

double ce[N];
int a[N],b[N],n,k;

bool cmp(double a,double b)
{
	return a>b;
}
int main()
{
	while(scanf("%d%d",&n,&k),n+k)
	{
		for(int i=1;i<=n;i++)
			scanf("%d",&a[i]);
		for(int i=1;i<=n;i++)
			scanf("%d",&b[i]);
		double low = 0,high = 100,mid;
		while(high-low > eps)
		{
			mid = (high+low)/2.0;
			for(int i=1;i<=n;i++)
				ce[i] = a[i]*100.0 - b[i]*mid;
			sort(ce+1,ce+n+1,cmp);
			double sum = 0;
			for(int i=1;i<=n-k;i++)
				sum += ce[i];
			if(sum>0)
				low = mid;
			else
				high = mid;
		}
		printf("%d\n",(int)(low+0.5));
	}
	return 0;
}