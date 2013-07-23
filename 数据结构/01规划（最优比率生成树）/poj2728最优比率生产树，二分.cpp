/*
roblem: 2728		User: heike520
Memory: 8064K		Time: 2875MS
Language: C++		Result: Accepted

*/
#include <iostream>
#include <cstring>
#include <algorithm>
#include <cstdio>
#include <cmath>
#define eps 0.0001
using namespace std;

const int M = 1001;
double graph[M][M];
struct Node
{
	double x,y,h;
}dot[M];

double getdis(double x1,double y1,double x2,double y2)
{
	return sqrt((y2-y1)*(y2-y1) + (x2-x1)*(x2-x1));
}

void creat(int n,double p)
{
	for(int i=1;i<=n;i++)
		for(int j=1;j<=n;j++)
			graph[i][j] = fabs(dot[i].h-dot[j].h) 
				- p*getdis(dot[i].x,dot[i].y,dot[j].x,dot[j].y);
}

bool vis[M];
double dis[M];
double prime(double graph[][M], int n)
{
	memset(vis,false,sizeof(vis));
	double ans = 0;
	int mark;
	vis[1] = true;
	for(int i=1;i<=n;i++)
		dis[i] = graph[1][i];
	for(int i=1;i<n;i++)
	{
		double mmin = 2e+23;
		for(int j=1;j<=n;j++)
		{
			if(!vis[j] && dis[j]<=mmin)
			{
				mmin = dis[j];
			   	mark = j;
			}
		}
		vis[mark] = true;
		ans += dis[mark];
		for(int j=1;j<=n;j++)
		{
			if(!vis[j] && graph[mark][j] < dis[j])
				dis[j] = graph[mark][j];
		}
	}
	//cout<<ans<<endl;
	return ans;
}

int main()
{
	int n;
	while(scanf("%d",&n) && n)
	{
		for(int i=1;i<=n;i++)
		{
			scanf("%lf%lf%lf",&dot[i].x,&dot[i].y,&dot[i].h);
		}
		double mmin=0, mmax=1000, mid;
		while(mmin < mmax)
		{
			mid = (mmin + mmax)/2;
			creat(n, mid);
			double pre = prime(graph, n);
			if(fabs(pre) <= eps)
				break;
			else if(pre > eps)
				mmin = mid;
			else
				mmax = mid;
		}
		printf("%.3lf\n", mid);
	}
	return 0;
}