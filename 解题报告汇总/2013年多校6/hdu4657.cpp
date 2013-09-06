/*
 * 又学了一招
 * 题目的意思：构造两个数字a[1..n], c[1..n] 使得 (a[i]+b[i])%n == c[i], b[i]已经给出
 * 采用构造的方式，初始化a[i] = c[i] = i，同时维护好ａ元素所在位置的数组。
 * 对于枚举到 i 位置保持1 到 i-1 中(a[i]+b[i]) % n = c[i]成立。
 * 对于i号位置，根据b[i]和c[i]计算出所需要的a[j]，通过 a 数组的索引数组快速找到所需元素的下标 j。
 * 	如果 j 大于等于枚举的位置，交换过来，继续往后枚举 i；
 * 	否则注定要破坏之前已经维护好的关系，因此需要交换一些元素，将c[i+1]与c[j]交换，处理j号位置。
 */
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>
using namespace std;

const int maxn = 100010;
int n, a[maxn], index[maxn], b[maxn], c[maxn];

int main()
{
	int cas;
	scanf("%d", &cas);
	while(cas --)
	{
		scanf("%d", &n);
		for(int i=0; i<n; i++)
		{
			scanf("%d", &b[i]);
			a[i] = c[i] = i;
			index[a[i]] = i;
		}
		for(int i=0; i<n; i++)
		{
			int cur = i;
			while((a[cur] + b[cur])%n != c[cur])
			{
				int next = index[(c[cur] - b[cur] + n)%n];
				swap(a[cur], a[next]);
				swap(index[a[cur]], index[a[next]]);
				if(next > i) break;
				swap(c[i+1], c[next]);
				cur = next;
			}
		}
		for(int i=0; i<n; i++)
			printf(i==0 ? "%d" : " %d", a[i]);
		puts("");
		for(int i=0; i<n; i++)
			printf(i==0 ? "%d" : " %d", c[i]);
		puts("");
	}
	return 0;
}
