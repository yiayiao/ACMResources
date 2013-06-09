#include <iostream>
#include <cstring>
#include <algorithm>
#include <cstdio>
#define eps 1e-10
using namespace std;

const int M = 10005;
double a[M], b[M], c[M];
int n;

double cacul(double x)
{
	double ret = -0x7fffffff;
	for(int i=0; i<n; i++)
	{
		double tmp = a[i]*x*x + b[i]*x + c[i];
		ret = max(tmp, ret);
	}
	return ret;
}

double search(double left, double right)
{
	while(right - left > 1e-10)
	{
		double d = (right - left) / 3.0;
		double mid1 = left + d;
		double mid2 = left + 2*d;
		if(cacul(mid1) >= cacul(mid2))
			left = mid1;
		else
			right = mid2;
	}
	return right;
}

int main()
{
	int cas;
	scanf("%d", &cas);
	while(cas --)
	{
		scanf("%d", &n);
		for(int i=0; i<n; i++)
		{
			scanf("%lf %lf %lf", &a[i], &b[i], &c[i]);
		};
		double ans = search(0.0, 1000.0);
		printf("%.4lf\n", cacul(ans));
	}
	return 0;
}
