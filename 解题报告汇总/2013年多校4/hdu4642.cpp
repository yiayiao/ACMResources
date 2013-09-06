#include <cstdio>
using namespace std;

const int maxn = 110;
int gmap[maxn][maxn];

int main()
{
	int cas;
	scanf("%d", &cas);
	while(cas --)
	{
		int n, m;
		scanf("%d %d", &n, &m);
		for(int i=0; i<n; i++)
			for(int j=0; j<m; j++)
				scanf("%d", &gmap[i][j]);
		if(gmap[n-1][m-1] == 1)
			printf("Alice\n");
		else
			printf("Bob\n");
	}
	return 0;
}
