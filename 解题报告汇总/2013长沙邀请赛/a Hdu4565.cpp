/*解题报告：http://www.klogk.com/posts/hdu4565/
 *好久没有写过矩阵快速幂，这道题照着人家的解题报告，也a得好艰难
 *首先是将递推公式转化为矩阵形式：
 *C[n+1] = 2*a*C[n] - (a^a - b)*C[n-1] 
 *=>|C[n+1]| = |2*a  (b-a^a)|*|C[n]	 |
 *	|C[n]  |   |1	  0		| |C[n-1]|
 *=>|C[n+1]| = |2*a  (b-a^a)|^n|C[1]|
 *	|C[n]  |   |1	  0		|  |C[0]|
 *一开始忽略了几个问题：1.矩阵乘法不满足交换率，2.注意模除n = (n%mod + mod)%mod,这是最保险的
 */
#include <iostream>
#include <cstring>
#include <cstdio>
#include <algorithm>
using namespace std;

typedef long long LL;

struct Matrix
{
    LL m[3][3];
}e, d;
LL a, b, n, mod;

void init()
{
    for(int i=1; i<=2; i++)
        for(int j=1; j<=2; j++)
            e.m[i][j] = (i == j);
    d.m[1][1] = 2*a;
    d.m[1][2] = b - a*a;
    d.m[2][1] = 1;
    d.m[2][2] = 0;
}

Matrix mul(Matrix m1, Matrix m2)
{
    Matrix c;
    for(int i=1; i<=2; i++)
        for(int j=1; j<=2; j++)
        {
            c.m[i][j] = 0;
            for(int k=1; k<=2; k++)
			{
                c.m[i][j] += ((m1.m[i][k]%mod)*(m2.m[k][j]%mod))%mod;
				c.m[i][j] = (c.m[i][j]%mod + mod)%mod;
			}
        }
    return c;
}

Matrix pow(Matrix m, LL n)
{
    Matrix ans = e;
    while(n)
    {
        if(n & 1)
            ans = mul(ans, m);
        n >>= 1;
        m = mul(m, m);
    }
    return ans;
}

int main()
{
    while(scanf("%I64d %I64d %I64d %I64d", &a, &b, &n, &mod)!= EOF)
    {
        init();
        Matrix p = pow(d, n), t;
        t.m[1][1] = 2*a, t.m[2][1] = 2, t.m[1][2] = t.m[2][2] = 0;
        p = mul(p, t);
        printf("%I64d\n", (p.m[2][1]%mod + mod)%mod);    
    }
    return 0;
}
