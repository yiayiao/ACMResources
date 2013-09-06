/*
对于序列：a1,a2,a3,a4,a5，总的颜色组合有s=a1*a2*a3*a4*a5 
    如果不计颜色连续，有s*5片 
    其中重复的有p=min(a1,a2)*s/(a1*a2)+min(a2,a3)*s/(a2*a3)+...  
    要让s*5-p最大，p要尽可能小，所以将序列排序，然后排成一小一大一小。。顺序 
    如a1<a3<a5<a4<a2 
注意min(a1,a2)*s/(a1*a2)不能直接算，需要使用逆元，不想用逆元，就得考虑其他法子
 */
#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

typedef long long LL;
const int maxn = 1000010;
const LL mod = 1000000007;
LL a[maxn], b[maxn], c[maxn], bef[maxn], hin[maxn];
int n;

int main()
{
	int T;
	scanf("%d", &T);
	while(T --)
	{
		scanf("%d", &n);
		for(int i=1; i<=n; i++)
		{
			scanf("%I64d", &b[i]);
		}
		if(n == 1)
		{
			cout<<b[1]<<endl;
			continue;
		}
		sort(b+1, b+n+1);
		for(int i=1; i<=n; i++)
			a[i] = b[n-i+1];
		int ct=1, ct1=1, ct2=1;
		for(int i=1; i<=n; i++)
		{
			if(i % 2)
				c[i] = b[ct1++];
			else
				c[i] = a[ct2++];
			//cout<<c[i]<<" ";
		}

		bef[0] = 1, hin[n] = c[n], hin[n+1] = 1;
		for(int i=1; i<=n; i++)
		{
			bef[i] = (bef[i-1] * c[i])%mod;
			hin[n-i] = (hin[n-i+1] * c[n-i])%mod;
		}

		LL ans = 0;
		for(int i=2; i<=n; i++)
		{
			ans = ((min(c[i], c[i-1])*bef[i-2]%mod)*hin[i+1]%mod + ans)%mod;
		}
		cout<<((n*bef[n]%mod-ans)%mod+mod)%mod<<endl;
	}
	return 0;
}
