#include <iostream>
#include <cmath>
#include <algorithm>
#include <cstdio>
#include <vector>
#define zero(x) (fabs(x)<eps)
using namespace std;

const int M = 10010;
const double eps = 1e-8;

struct Point
{
	double x, y;
	Point(){}
	Point(double a,double b):x(a), y(b){}
}pa[M], pb[M], pos;
int an, bn;
vector<Point> sa, sb;

double dist(Point p1, Point p2)
{
	return sqrt((p1.x - p2.x)*(p1.x - p2.x) + (p1.y - p2.y)*(p1.y - p2.y));
}

double xmult(Point p0, Point p1, Point p2)
{
	return (p1.x - p0.x)*(p2.y - p0.y) - (p1.y - p0.y)*(p2.x - p0.x);
}

//graham
bool cmp(Point p1, Point p2)
{
	if(xmult(pos, p1, p2) > eps)
		return true;
	if(zero(xmult(pos, p1, p2)) && dist(pos, p1) < dist(pos, p2))
		return true;
	return false;
}
void graham(vector<Point> &s, Point p[], int n)
{
	for(int i=1; i<n; i++)
		if(p[i].y < p[0].y || (zero(p[i].y-p[0].y) && p[i].x < p[0].x))
			swap(p[i], p[0]);
	pos = p[0];
	sort(p+1, p+n, cmp);
	s.clear();
	s.push_back(p[0]);
	s.push_back(p[1]);
	s.push_back(p[2]);
	for(int i=3; i<n; i++)
	{
		while(s.size() >= 2 && xmult(s[s.size()-2],s[s.size()-1],p[i])<eps)
			s.pop_back();
		s.push_back(p[i]);
	}
}

//判断向量a1b1 和 向量a2b2的关系
double get_angle(Point a1, Point b1, Point a2, Point b2)
{
	Point s1(b1.x-a1.x, b1.y-a1.y);
	Point s2(b2.x-a2.x, b2.y-a2.y);
	return s2.x*s1.y - s1.x*s2.y;
}
double dist_point_seg(Point p, Point a, Point b)
{
	Point t = p;
	t.x += a.y - b.y;
	t.y += b.x - a.x;
	if(xmult(a, t, p)*xmult(b, t, p) > eps)
		return dist(p,a) + eps<dist(p,b) ? dist(p,a) : dist(p,b);
	else
		return fabs(xmult(p, a, b))/dist(a, b);
}

double min_dis(vector<Point>s1,vector<Point>s2)
{ 
	int na=s1.size(),nb=s2.size(); 
	int lp=0,lq=0; 
	for(int i=1;i<na;i++) 
		if(s1[i].y<s1[lp].y||(zero(s1[i].y-s1[lp].y)&&s1[i].x<s1[lp].x)) 
			lp=i; 
	for(int i=1;i<nb;i++) 
		if(s2[i].y>s2[lq].y||(zero(s2[i].y-s2[lq].y)&&s2[i].x>s2[lq].x)) 
			lq=i; 
	s1.push_back(s1[0]);s2.push_back(s2[0]); 
	double ans=dist(s1[lp],s2[lq]); 
	int tp=lp,tq=lq; 
	do{ 
		double angle=get_angle(s1[tp],s1[tp+1],s2[tq],s2[tq+1]); 
		//和两个凸包的边都重合 
		if(zero(angle)){ 
			ans=min(ans,dist_point_seg(s1[tp],s2[tq],s2[tq+1])); 
			ans=min(ans,dist_point_seg(s1[tp+1],s2[tq],s2[tq+1])); 
			ans=min(ans,dist_point_seg(s2[tq],s1[tp],s1[tp+1])); 
			ans=min(ans,dist_point_seg(s2[tq+1],s1[tp],s1[tp+1])); 
			tp=(tp+1)%na;tq=(tq+1)%nb; 
		} 
		//和第二个凸包的边重合 
		else if(angle<-eps){ 
			ans=min(ans,dist_point_seg(s1[tp],s2[tq],s2[tq+1])); 
			tq=(tq+1)%nb; 
		} 
		//和第一个凸包的边重合 
		else{ 
			ans=min(ans,dist_point_seg(s2[tq],s1[tp],s1[tp+1])); 
			tp=(tp+1)%na; 
		} 
	}while(!(lp==tp&&lq==tq)); 
	return ans; 
}

int main()
{
	while(scanf("%d %d", &an, &bn) != EOF && (an + bn))
	{
		for(int i=0; i<an; i++)
			scanf("%lf %lf", &pa[i].x, &pa[i].y);
		graham(sa, pa, an);
		for(int i=0; i<bn; i++)
			scanf("%lf %lf", &pb[i].x, &pb[i].y);
		graham(sb, pb, bn);

		double ans = min_dis(sa, sb);
		printf("%.5lf\n", ans);
	}
	return 0;
}
