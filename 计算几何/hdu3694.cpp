#include <iostream>
#include <cstdio>
#include <cmath>
#define eps 1e-8
using namespace std;

struct Point 
{
	double x, y;
}p[4];

double getdis(Point p1,Point p2) 
{ 
	return sqrt((p1.x-p2.x)*(p1.x-p2.x)+(p1.y-p2.y)*(p1.y-p2.y)); 
} 

double getdis_all(Point p0)
{
	double res = 0.0;
	for(int i=0; i<4; i++)
		res += getdis(p0, p[i]);
	return res;
}

Point intersection(Point p1,Point p2,Point p3,Point p4) 
{ 
	Point ret=p1; 
	double t=((p1.x-p3.x)*(p3.y-p4.y)-(p1.y-p3.y)*(p3.x-p4.x)) 
		/((p1.x-p2.x)*(p3.y-p4.y)-(p1.y-p2.y)*(p3.x-p4.x)); 
	ret.x+=(p2.x-p1.x)*t; 
	ret.y+=(p2.y-p1.y)*t; 
	return ret; 
} 

double xmult(Point p1,Point p2,Point p0)
{
	return (p1.x-p0.x)*(p2.y-p0.y) - (p1.y-p0.y)*(p2.x-p0.x);
}

int main()
{
	while(true)
	{
		for(int i=0; i<4; i++)
			scanf("%lf %lf", &p[i].x, &p[i].y);
		if(p[0].x + 1 < 1e-8)
			break;

		double ans = 1e20, res = 0;
		for(int i=0; i<4; i++)
		{
			res = getdis_all(p[i]);
			ans = min(ans, res);
		}

		if(xmult(p[0],p[1],p[3])*xmult(p[2],p[1],p[3])<0) 
		{ 
			Point tmp=intersection(p[0],p[2],p[1],p[3]); 
			res=getdis_all(tmp); 
			ans=min(ans,res); 

		} 
		if(xmult(p[1],p[2],p[3])*xmult(p[0],p[2],p[3])<0)
		{ 
			Point tmp=intersection(p[1],p[0],p[2],p[3]); 
			res=getdis_all(tmp); 
			ans=min(ans,res); 
		} 
		if(xmult(p[2],p[0],p[3])*xmult(p[1],p[0],p[3])<0) 
		{ 
			Point tmp=intersection(p[2],p[1],p[0],p[3]); 
			res=getdis_all(tmp); 
			ans=min(ans,res); 
		} 
		printf("%.4lf\n", ans);
	}
	return 0;
}