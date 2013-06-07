/*
使用的编译器 G++
运行使用时间 110 Ms
运行使用内存 1076 Kb
*/ 
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <vector>
#include <cmath>
#define zero(x) (abs(x)<eps)
using namespace std;

const int M = 500002;
const double eps = 1e-8;
struct Point
{
	int x, y;
}p[M];
int n;
vector<Point> s;

int dist(Point p1, Point p2)
{
	return (p1.x-p2.x)*(p1.x-p2.x) + (p1.y-p2.y)*(p1.y-p2.y);
}
int xmult(Point p0, Point p1, Point p2)
{
	return (p1.x-p0.x)*(p2.y-p0.y) - (p1.y-p0.y)*(p2.x-p0.x);
}
//Graham
bool cmp(Point p1, Point p2)
{
	if(xmult(p[0], p1, p2) > eps)
		return true;
	if(zero(xmult(p[0], p1, p2)) && dist(p[0], p1) < dist(p[0], p2))
		return true;
	return false;
}
void Graham()
{
	for(int i=1; i<n; i++)
		if(p[i].y < p[0].y || (p[i].y == p[0].y && p[i].x < p[0].x))
			swap(p[i], p[0]);
	sort(p+1, p+n ,cmp);
	s.clear();
	s.push_back(p[0]);
	s.push_back(p[1]);
	for(int i=2; i<n; i++)
	{
		while(s.size()>=2 && xmult(s[s.size()-2], s[s.size()-1], p[i])<eps)
			s.pop_back();
		s.push_back(p[i]);
	}
}
//Rotating 选择卡壳求凸包直径
void Rotating()
{
	int ans = 0, len = s.size();
	int j = 1;
	s.push_back(s[0]);
	for(int i=0; i<len; i++)
	{
		while(abs(xmult(s[i], s[i+1], s[j+1]) > abs(xmult(s[i], s[i+1], s[j]))))
			j = (j+1) % len;
		ans = max(ans, max(dist(s[i+1], s[j]), dist(s[i], s[j])));
	}
	printf("%d\n", ans);
}

int main()
{
	while(scanf("%d", &n) != EOF)
	{
		for(int i=0;i<n;i++)
			scanf("%d %d", &p[i].x, &p[i].y);
		Graham();
		Rotating();
	}
	return 0;
}
