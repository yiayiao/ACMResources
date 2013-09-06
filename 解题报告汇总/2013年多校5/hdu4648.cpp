#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
using namespace std;

const int maxn = 100010, maxm = 11020;
int a[maxn], num[maxn], record[maxm*3][3], n, m;

int main()
{
	while(scanf("%d %d", &n, &m) != EOF)
	{
		num[0] = 0;
		for(int i=1; i<=n; i++)
		{
			scanf("%d", &num[i]);
			num[i] = (num[i] + num[i-1]) % m;
		}
		memset(record, -1, sizeof(record));
		for(int i=0; i<=n; i++)
		{
			if(record[(num[i]+m)%m][0] == -1)
				record[(num[i]+m)%m][0] = record[(num[i]+m)%m][1] = i;
			else
				record[(num[i]+m)%m][1] = i;
		}
		int ans = 0;
		for(int i=0; i<m; i++)
		{
			if(record[i][1] - record[i][0] > ans)
				ans = record[i][1] - record[i][0];
		}
		printf("%d\n", ans);
	}
	return 0;
}
