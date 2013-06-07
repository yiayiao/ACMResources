#include <iostream>
#include <cstring>
#include <cstdio>
#include <algorithm>
using namespace std;

long long num = 0;
const int M = 500005;
int data[M], tmp[M];

void merge(int begin, int mid, int end)
{
	int begA = begin, endA = mid, begB = mid+1, endB = end;
	int j = 0;
	while(begA <= endA && begB <= endB)
	{
		if(data[begA] <= data[begB])
			tmp[j++] = data[begA++];
		else
		{
			num += (endA - begA + 1);
			tmp[j++] = data[begB++];
		}
	}
	while(begA <= endA)
		tmp[j++] = data[begA++];
	while(begB <= endB)
		tmp[j++] = data[begB++];
	for(int i=0; i<j; i++)
		data[begin+i] = tmp[i];
}

void mergeSort(int first, int last)
{
	if(first < last)
	{
		int mid = (first + last)/2;
		mergeSort(first, mid);
		mergeSort(mid+1, last);
		merge(first, mid, last);
	}
}

int main()
{
	int i, n;
	while(scanf("%d", &n) && n)
	{
		num = 0;
		for(int i=0;i<n;i++)
			scanf("%d", &data[i]);
		mergeSort(0, n-1);
		printf("%lld\n", num);
	}
	return 0;
}
