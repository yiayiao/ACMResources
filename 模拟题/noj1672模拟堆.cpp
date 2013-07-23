#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

const int M = 400010;
int n, m, cot;
int tree[M];

int shiftUp(int n)
{
	if(n == 1)
		return 1;
	if(tree[n>>1] > tree[n])
	{
		swap(tree[n>>1] , tree[n]);
		return shiftUp(n>>1);
	}
	return n;
}

void shiftDown(int n)
{
	if((n<<1|1) <= cot && tree[n<<1|1] < tree[n<<1] && tree[n<<1|1] < tree[n])
	{
		swap(tree[n<<1|1], tree[n]);
		shiftDown(n<<1|1);
	}
	else if((n<<1) <= cot && tree[n<<1] < tree[n])
	{
		swap(tree[n<<1], tree[n]);
		shiftDown(n<<1);
	}
}

void print()
{
	//cout<<"cot:"<<cot<<endl;
	int rank = 1, tcot = cot, j = 1;
	while(tcot > 0)
	{
		for(int i=0; i<min(rank, tcot)-1; i++)
			printf("%d ", tree[j++]);
		printf("%d\n", tree[j++]);
		tcot -= rank;
		rank <<= 1;
	}
	printf("\n");
}

int main()
{
	while(scanf("%d %d", &n, &m) != EOF)
	{
		memset(tree, 0,sizeof(tree));
		cot = 0;
		for(int i=1; i<=n; i++)
		{
			scanf("%d", &tree[++cot]);
			shiftUp(cot);
		}
		
		char op[20];
	   	int num;
		while(m -- )
		{
			scanf("%s %d", op, &num);
			if(op[0] == 'a')
			{
				cot ++;
				tree[cot] = num;
				shiftUp(cot);
			}
			else{
				for(int i=1; i<=cot; i++)
				{
					if(tree[i] == num)
					{
						swap(tree[i], tree[cot]);
						tree[cot] = 0;
						cot --;
						int t = shiftUp(i);
						shiftDown(t);
						break;
					}
				}
			}
			print();
		}
	}
	return 0;
}
