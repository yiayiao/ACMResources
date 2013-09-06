#include <iostream>
#include <cstring>
#include <cstdio>
#include <algorithm>
using namespace std;

const int maxn = 110000, maxm = 11000;
char str[maxn], rec[maxn];
pair<int, int> s_p[maxn];
int index[maxn], next[maxn], n;

void get_next(char* str, int len)
{
	memset(next, 0, sizeof(int) * len);
	for(int i=1; i<len; i++)
	{
		int j = next[i-1];
		while(j && str[i] != str[j])
			j = next[j-1];
		if(str[i] == str[j])
			j ++;
		next[i] = j;
	}
}

//用 str 去匹配 s, 查看 str 是否为 s 子串
bool match(char* s, int len)
{
	int k = 0;
	for(int i=0; i<n; i++)
	{
		while(k && str[k] != s[i])
			k = next[k-1];
		if(str[k] == s[i])
			k ++;
		if(k == len)
			return true;
	}
	return false;
}

int main()
{
	while(scanf("%s", str) != EOF)
	{
		n = strlen(str);
		for(int i=0; i<n; i++)
		{
			s_p[i].first = str[i];
			s_p[i].second = i;
		}
		stable_sort(s_p, s_p + n);
		for(int i=0; i<n; i++)
			index[i] = s_p[i].second;

		int now = index[0], q;
		n --;
		for(int i=0; i<n; i++)
		{
			rec[i] = s_p[now].first;
			now = index[now];
		}
		rec[n] = '\0';

		scanf("%d", &q);
		while(q --)
		{
			scanf("%s", str);
			int len = strlen(str);
			get_next(str, len);
			if(match(rec, len))
				printf("YES\n");
			else
				printf("NO\n");
		}
	}
	return 0;
}
