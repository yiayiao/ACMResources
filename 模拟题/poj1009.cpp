/*
使用的编译器	G++
运行使用时间	16 Ms
运行使用内存	756 Kb
*/
#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

const int size = 1000;
int width, total = 0;

struct Pix
{
	int pos, code;
	Pix(){}
	Pix(int a, int b):pos(a), code(b){}
	bool operator< (Pix b) const
	{
		return pos < b.pos;
	}
};
int inMapPair[size][2];		//第一维存值，第二维存length
Pix outMap[size*8];

int GetValue(int pos)
{
	int i = 0, p = 0;
	while(p < pos)
		p += inMapPair[i++][1];
	return inMapPair[i-1][0];
}

int GetCode(int pos)
{
	int code = GetValue(pos);
	int maxabs = 0;
	int row = (pos - 1) / width;
	int col = (pos - 1) % width;
	for(int i=row-1; i<=row + 1; i++)
	{
		for(int j=col-1; j<=col + 1; j++)
		{
			int tpos = i*width + j;
			if(i<0 || j<0 || j >= width || tpos>=total || tpos == pos -1)
				continue;
			int tcode = GetValue(tpos + 1);
			if(maxabs < abs(tcode - code))
				maxabs = abs(tcode - code);
		}
	}
	return maxabs;
}

int main()
{
	while(scanf("%d", &width) && width)
	{
		int pairv, pairt;
		int k = total = 0;
		while(scanf("%d %d", &pairv, &pairt) && pairt)
		{
			inMapPair[k][0] = pairv;
			inMapPair[k++][1] = pairt;
			total += pairt;
		}
		int pairNum = k;
		printf("%d\n", width);

		int pos = 1;
		k = 0;
		for(int p=0; p<=pairNum; p++)
		{
			int row = (pos - 1)/width;
			int col = (pos - 1)%width;
			for(int i=row-1; i<=row+1; i++)
				for(int j=col-1; j<=col+1; j++)
				{
					int tpos = i*width + j;
					if(i<0 || j<0 || j>=width || tpos>=total)
						continue;
					outMap[k].pos = tpos + 1;
					outMap[k++].code = GetCode(tpos + 1);
				}
			pos += inMapPair[p][1];
		}
		sort(outMap, outMap + k);

		Pix temp = outMap[0];
		for(int i=0; i<k; i++)
		{
			if(temp.code == outMap[i].code)
				continue;
			printf("%d %d\n", temp.code, outMap[i].pos - temp.pos);
			temp = outMap[i];
		}
		printf("%d %d\n", temp.code, total - temp.pos + 1);
		printf("0 0\n");
	}
	printf("0\n");
	return 0;
}
