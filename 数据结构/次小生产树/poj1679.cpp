/** 首先求出原图最小生成树，记录权值之和为MinST。枚举添加每条不在最小生成树上的边(u,v)，加上以后一定会形成一个环。找到环上权值第二大的边(即除了(u,v)以外的权值最大的边)，把它删掉，计算当前生成树的权值之和。取所有枚举修改的生成树权值之和的最小值，就是次小生成树。
  	具体实现时，更简单的方法是从每个节点i遍历整个最小生成树，定义mdis[j]为从i到j的路径上最大边的权值。遍历图(dfs)求出mdis[j]的值，然后对于添加每条不在最小生成树中的边(i,j)，新的生成树权值之和就是MinST + w(i,j) – mdis[j]，记录其最小值，则为次小生成树。
	该算法的时间复杂度为O(N^2 + M)。算法的瓶颈不在求最小生成树，而在O(N^2+M)的枚举加边修改。但是还是使用kruskal，因为Kruskal每次是加边，prim每次是加点，所以Kruskal更方便处理树中每条边的邻接表ve。
	下面的解答为poj1679， 如果最小生成树唯一，则输出它的值，否则输出 not unique!
 * */
#include <iostream>
#include <cstring>
#include <algorithm>
#include <cstdio>
#include <vector>
#define inf 0x7ffffff
using namespace std;

const int M = 105;
vector<int> ve[M];			//最小生成树中边的邻接表
int mdis[M], dis[M][M];		//树中从根到该节点的最大边 ， 距离
int sum , minc , msum;
int n,m;

struct Node
{
	int u,v,len;
	Node(){}
	Node(int a,int b,int c)
		:u(a),v(b),len(c){}
	bool operator<(const Node b) const 
	{
		return len < b.len;
	}
}edge[M*M];

//最小生出树算法
int root[M];
void init(int n)
{
	for(int i=1;i<=n;i++)
		root[i] = i;
}
int findroot(int x)
{
	if(root[x] != x)
		root[x] = findroot(root[x]);
	return root[x];
}
void _union(int x,int y)
{
	int xx = findroot(x);
	int yy = findroot(y);
	if( xx != yy)
		root[xx] = yy;
}
bool kruskal()
{
	for(int i=1;i<=n;i++)
		ve[i].clear();
	sum = 0;
	sort(edge+1,edge+n+1);
	init(n);
	int i=1, j=1, k=1;
	for(k=1;k<=n-1;k++,i++)
	{
		while(i<=m && findroot(edge[i].u)==findroot(edge[i].v))
			i++;
		if(i == m+1) break;
		ve[edge[i].u].push_back(edge[i].v);
		ve[edge[i].v].push_back(edge[i].u);
		_union(edge[i].u , edge[i].v);
		sum += edge[i].len;
	}
	if(k == n) 
		return true;
	return false;
}

void dfs(int x,int y)
{
	mdis[y] = max(dis[x][y], mdis[x]);
	for(int i=0;i<ve[y].size();i++)
	{
		if(ve[y][i] != x)
			dfs(y,ve[y][i]);
	}
}

int main()
{
	int cas;
	scanf("%d", &cas);
	while(cas --)
	{
		scanf("%d%d",&n,&m);
		memset(dis,0x7f,sizeof(dis));

		for(int i=1;i<=m;i++)
		{
			int u,v,w;
			scanf("%d%d%d", &u,&v,&w);
			dis[u][v] = min(dis[u][v], w);
			dis[v][u] = dis[u][v];
			edge[i] = Node(u,v,w);
		}
		kruskal();
		//cout<<sum<<endl;
		minc = inf;
		bool flag[M];
		for(int i=1;i<=n;i++)
		{
			memset(mdis,0,sizeof(mdis));
			memset(flag,0,sizeof(flag));
			flag[i] = true;
			for(int j=0;j<ve[i].size();j++)
			{
				flag[ve[i][j]] = true;
				dfs(i,ve[i][j]);
			}
			for(int j=1;j<=n;j++)
				if(!flag[j] && dis[i][j]-mdis[j]<minc)
				{
					msum = sum + dis[i][j] - mdis[j];	
					minc = dis[i][j] - mdis[j];
				}
			if(minc == 0)
				break;
		}
		if(minc != 0)
			printf("%d %d\n", sum, msum);
		else
			printf("Not Unique!\n");
	}
	return 0;
}

