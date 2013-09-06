#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <queue>			
using namespace std;

const int maxn = 210;
char gmap[maxn][maxn];
int n, m, key, gkey[maxn][maxn];
int dir[4][2] = {{0,1},{0,-1},{1,0},{-1,0}};
int sx, sy, ex, ey;

struct Node
{
	int x, y, num, k;
	Node(){}
	Node(int x, int y):x(x), y(y) { num = k = 0; }
}tmp, now;

queue<Node> que;
bool used[maxn][maxn][1<<7];
bool vis[maxn][maxn][1<<7][4];

int bfs()
{
	while(!que.empty()) que.pop();
	que.push(Node(sx, sy));
	memset(used, 0, sizeof(used));
	memset(vis, 0, sizeof(vis));
	used[sx][sy][0] = true;
	while(!que.empty())
	{
		tmp = que.front();
		que.pop();
		for(int i=0; i<4; i++)
		{
			int x = tmp.x, y = tmp.y, kk = tmp.k, mx = dir[i][0], my = dir[i][1];
			while(true)
			{
				int dd;
				if(gmap[x][y] == 'L')
					mx = 0, my = -1;
				else if(gmap[x][y] == 'U')
					mx = -1, my = 0;
				else if(gmap[x][y] == 'D')
					mx = 1, my = 0;
				else if(gmap[x][y] == 'R')
					mx = 0, my = 1;
				if(mx==-1&&my==0) dd=0;
                else if(mx==1&&my==0) dd=1;
                else if(mx==0&&my==1) dd=2;
                else if(mx==0&&my==-1) dd=3;
				if(vis[x][y][kk][dd])
					break;
				vis[x][y][kk][dd] = true;
				if(gmap[x][y] == 'K')
					kk |= gkey[x][y];
				if(x+mx >= 0 && x+mx < n && y+my >= 0 && y+my < m && gmap[x+mx][y+my] == '#')
				{
					if(used[x][y][kk]) 
						break;
					used[x][y][kk] = true;
					now.x = x, now.y = y;
					now.k = kk;
					now.num = tmp.num + 1;
					que.push(now);
					break;
				}
				x += mx;
				y += my;
				if(x < 0 || y < 0 || x >= n || y >= m)
					break;
				if(x == ex && y == ey && kk == (1<<key) - 1)
					return tmp.num + 1;
			}
		}
	}
	return -1;
}

int main()
{
	while(scanf("%d %d", &n, &m) != EOF)
	{
		key = 0;
		for(int i=0; i<n; i++)
		{
			scanf("%s", gmap[i]);
			for(int j=0; j<m; j++)
			{
				if(gmap[i][j] == 'S')
					sx = i, sy = j;
				else if(gmap[i][j] == 'E')
					ex = i, ey = j;
				else if(gmap[i][j] == 'K')
				{
					gkey[i][j] = (1 << key);
					key ++;
				}
			}
		}
		printf("%d\n", bfs());
	}
	return 0;
}
