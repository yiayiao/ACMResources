#include <iostream>
#include <cstring>
#include <algorithm>
#include <cstdio>
#include <vector>
using namespace std;

const int maxn = 110000;
double dot[maxn], w;
int n, m, u, v;

int main()
{
	while(scanf("%d %d", &n, &m) != EOF)
	{
		for(int i=1; i<=n; i++)
			scanf("%lf", &dot[i]);
		for(int i=1; i<=m; i++)
		{
			scanf("%d %d %lf", &u, &v, &w);
			dot[u] += w/2.0;
			dot[v] += w/2.0;
		}
		sort(dot+1, dot+n+1);
		double ans = 0.0;
		for(int i=1; i<n; i+=2)
			ans += dot[i+1] - dot[i];
		printf("%.0lf\n", ans);
	}
	return 0;
}

