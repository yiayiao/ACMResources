/*
F - 无聊的矩阵

时间限制:	2000ms
内存限制:	65535KB
问题描述

 给定一个n*n的矩阵，从这个矩阵中选n个数，这n个数两两之间必须在不同行不同列，问这n个数中最大值与最小值之差的最小值是多少？
输入说明

 多组测试数据。每组测试数据格式如下：
 第一行是一个整数n（1<=n<=100）
 接下来n行，每行n个整数，表示给定的矩阵。 
输出说明

 输出n个数中最大值与最小值之差的最小值。
输入样例

4
1 1 1 1
2 2 2 2
3 3 3 3
4 4 4 4
输出样例

3
 
 */

#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
using namespace std;

const int M = 105;
int result[M], map[M][M], n;
bool state[M], data[M][M];

bool find(const int u)
{
	for(int v=1; v<=n; v++)
	{
		if(data[u][v] && !state[v])
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

bool solve()
{
	memset(result, 0, sizeof(result));
	int ans = 0;
	for(int i=1; i<=n; i++)
	{
		memset(state, 0, sizeof(state));
		if(!find(i))
			return false;
	}
	return true;
}

int main()
{
	while(scanf("%d", &n) != EOF)
	{
		for(int i=1; i<=n; i++)
			for(int j=1; j<=n; j++)
			{
				scanf("%d", &map[i][j]);
			}
		int low = 0, high = 200, down, up, ans;
		while(low <= high)
		{
			int mid = (low+high)>>1;
			for(down=0; down<=100; down++)
			{
				up = mid + down;
				for(int i=1; i<=n; i++)
					for(int j=1; j<=n; j++)
					{
						if(map[i][j] >= down && map[i][j] <= up)
							data[i][j] = 1;
						else
							data[i][j] = 0;
					}
				if(solve())
					break;
			}
			if(down <= 100)
				ans = mid, high = mid - 1;
			else 
				low = mid + 1;
		}
		printf("%d\n", ans);
	}
	return 0;
}
