#include <cstdio>
#define M 30004
int set[M],rank[M];
void init(int n)
{
	for(int i=0;i<=n;i++)
	{
		set[i] = i;
		rank[i] = 0;
	}
}
int find(int i)
{
	if(set[i] != i)
		set[i] = find(set[i]);
	return set[i];
}
void same(int i,int j)
{
	i = find(i);
	j = find(j);
	if(i == j)
		return;
	if(rank[i]>rank[j])
		set[j] = i;
	else
	{
		if(rank[i] == rank[j])
			rank[j] ++;
		set[i] = j;
	}
}

int main()
{
	int n,m,num;
	while(scanf("%d%d",&n,&m) && (m+n))
	{
		init(n);
		for(int i=0;i<m;i++)
		{
			int a,b;
			scanf("%d",&num);
			scanf("%d",&a);
			for(int k=1;k<num;k++)
			{
				scanf("%d",&b);
				same(a,b);
			}
		}
		int ans = 0;
		for(int i=0;i<n;i++)
		{
			if(find(i) == find(0))
				ans++;
		}
		printf("%d\n",ans);
	}
	return 0;
}