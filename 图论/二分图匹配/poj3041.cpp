/**
使用的编译器	G++
题目	3041
作者	heike520
 */
#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
using namespace std;

const int M = 504;
vector<int> ve[M];
int result[M];
bool state[M];
int n, m;

bool find(const int u)
{
	for(int i=0; i<ve[u].size(); i++)
	{
		int v = ve[u][i];
		if(!state[v])
		{
			state[v] = true;
			if(result[v] == 0 || find(result[v]))
			{
				result[v] = u;
				return true;
			}
		}
	}
	return false;
}

int solve()
{
	memset(result, 0, sizeof(result));
	int ans = 0;
	for(int i=1; i<=n; i++)
	{
		memset(state, 0, sizeof(state));
		if(find(i))
			ans ++;
	}
	return ans;
}

int main()
{
	while(scanf("%d %d", &n, &m) != EOF)
	{
		for(int i=1; i<=n; i++)
			ve[i].clear();
		for(int i=1; i<=m; i++)
		{
			int u, v;
			scanf("%d %d", &u, &v);
			ve[u].push_back(v);
		}
		printf("%d\n", solve());
	}
	return 0;
}
