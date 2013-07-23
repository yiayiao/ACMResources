#include<iostream>
#include<algorithm>
#include<cmath>
#include <cstdio>
using namespace std;
#define MAXN 1005
#define INF 1000000000
int n;
double prerate=0;
struct point 
{
	double b,c;
}dis[MAXN][MAXN];
double xx[MAXN],yy[MAXN],zz[MAXN];
double lowcost[MAXN];     //与点i边相连的最小权值
int aa[MAXN],bb[MAXN];
bool closeset[MAXN];      //表示点是否被加入树中
double prim()
{
	int i,j,k;
	double min,sumb=0,sumc=0;
	for(i=2;i<=n;i++) //初始化，先将标号为0的点加入树中，其余的全标记为1；
	{
		lowcost[i]=dis[i][1].b-prerate*dis[i][1].c;
		aa[i]=i;
		bb[i]=1;
		closeset[i]=1; 
	}
	closeset[1]=0;
	lowcost[1]=-1;
	for(i=2;i<=n;i++)
	{
		min=2e+23;
		k=1;
		for(j=2;j<=n;j++) //查找权值最小的边所连的点，记为k。
			if(lowcost[j]<min&&closeset[j])
			{
				min=lowcost[j];
				k=j; 
			}
		closeset[k]=0;
		sumb+=dis[aa[k]][bb[k]].b;
		sumc+=dis[aa[k]][bb[k]].c;
		for(j=2;j<=n;j++) //更新加入一个节点后，lowcost的值。
			if(lowcost[j]>dis[j][k].b-prerate*dis[j][k].c&&closeset[j])
			{
				lowcost[j]=dis[j][k].b-prerate*dis[j][k].c;
				aa[j]=j;
				bb[j]=k;
			}
	}
	return sumb/sumc;
}

int main()
{
	int i,j;
	double rate;
	while (scanf("%d",&n)!=EOF)
	{
		if (n==0)
			break;
		for (i=1;i<=n;i++)
			scanf("%lf%lf%lf",&xx[i],&yy[i],&zz[i]);
		for (i=1;i<=n;i++)
			for (j=1;j<=n;j++)
			{
				dis[i][j].c=sqrt((xx[i]-xx[j])*(xx[i]-xx[j])+(yy[i]-yy[j])*(yy[i]-yy[j]));
				dis[i][j].b=fabs(zz[i]-zz[j]);
			}
		while (1)
		{
			rate=prim();
			if (fabs(prerate-rate)<0.00001)
				break;
			prerate=rate;
		}
		printf("%.3lf\n",prerate);
	}
	return 0;
}