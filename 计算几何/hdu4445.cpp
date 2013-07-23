/*
使用的编译器	G++
运行使用时间	312 Ms
运行使用内存	312 Kb
有时过题真的是要看运气的，这个题枚举角度，0.0001超时，0.001wa，最后改用pi/1000AC
*/
#include <iostream>
#include <cstdio>
#include <cmath>
#include <cstring>
#include <algorithm>
using namespace std;

const double g = 9.8, pi = acos(-1.0)/2, ins = pi/1000;
const int M = 300;
double h, l1, l2, r1, r2;
double v[M];

inline double getTime(double vh)
{
	double tmp = sqrt(vh*vh + 2*g*h) - vh;
	return tmp/g;
}

inline double getDis(double vv, double a)
{
	double vx = vv*cos(a), vy = vv*sin(a);
	return vx * getTime(vy);
}

void solve(int n)
{
	int ans = 0;
	for(double a = -pi/2;a < pi/2; a +=ins)
	{
		int cot = 0;
		for(int i=0; i<n; i++)
		{
			double l = getDis(v[i], a); 
			if(l>=l2 && r2>=l)
			{
				cot = 0;
				break;
			}
			if(l>=l1 && r1>=l)
				cot ++;
		}
		ans = max(ans , cot);
	}
	printf("%d\n", ans);
}

int main()
{
	int n;
	while(scanf("%d", &n) && n)
	{
		scanf("%lf %lf %lf %lf %lf", &h, &l1, &r1, &l2, &r2);
		for(int i=0; i<n; i++)
			scanf("%lf", &v[i]);
		solve(n);
	}
	return 0;
}