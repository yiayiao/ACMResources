#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

const int M = 1000000;
int st[M][9], goal[9], fact[9];
int path[M], pre[M];
bool vis[M];
const int dx[] = {0,-1,0,1};
const int dy[] = {-1,0,1,0};

void init()
{
	memset(vis, 0, sizeof(vis));
	fact[0] = 1;
	for(int i=1; i<9; i++)
		fact[i] = fact[i-1] * i;
}

int hash(int s)
{
	int code = 0;
	for(int i=0; i<9; i++)
	{
		int cnt = 0;
		for(int j=i+1; j<9; j++)
			if(st[s][j] < st[s][i])
				cnt ++;
		code += cnt * fact[8-i];
	}
	if(vis[code])
		return 0;
	return vis[code] = true;
}

int bfs()
{
	init();
	int head = 1, tail = 2;
	while(head < tail)
	{
		if(memcmp(goal, st[head], sizeof(goal)) == 0)
			return head;
		int z;
		for(z=0; z<9; z++)
			if(st[head][z] == 0)
				break;
		int x = z/3;
		int y = z%3;
		for(int d=0; d<4; d++)
		{
			int nx = x + dx[d];
			int ny = y + dy[d];
			int nz = nx*3 + ny;
			if(nx >= 0 && nx < 3 && ny >= 0 && ny < 3)
			{
				memcpy(st[tail], st[head], sizeof(st[head]));
				st[tail][nz] = st[head][z];
				st[tail][z] = st[head][nz];
				pre[tail] = head;
				path[tail] = d;
				if(hash(tail))
					tail ++;
			}
		}
		head ++;
	}
	return 0;
}

void print(int a)
{
	if(a == 1)
		return;
	print(pre[a]);
	char pp[4] = {'l','u','r','d'};
	printf("%c",pp[path[a]]);
}

int main()
{
	for(int i=0;i<9;i++)
	{
		char tt;
		cin>>tt;
		if(tt == 'x')
			st[1][i] = 0;
		else 
			st[1][i] = tt-'0';
		goal[i] = i+1;
	}
	goal[8] = 0;

	int ans = bfs();
	if(ans>0)
		print(ans);
	else
		printf("-1");
	printf("\n");
	return 0;
}