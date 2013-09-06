#include <cstdio>

bool flag;

bool dfs(int b, int s, int n)
{
	for(int i=n; i>1; i--)
	{
		if(s%i == 0 && dfs(b, s/i, i-1))
			return true;
		if(b%i == 0 && dfs(b/i, s, i-1))
			return true;
	}
	
	if(s == 1) 
		flag = true;
	else if(!flag) 
		return true;
	
	if(b == 1 && s == 1)
		return true;
	return false;
}

int main()
{
	int b, s;
	while(scanf("%d %d", &b, &s) != EOF)
	{
		if(b < s) 
		{
			int t = b;
			b = s;
			s = t;
		}
		flag = false;
		if(dfs(b, s, 100))
			printf("%d\n", b);
		else
			printf("%d\n", s);
	}
	return 0;
}
