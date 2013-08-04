
#include <iostream>
#include <stdio.h>
#include <memory.h>
#define NUM 100000
using namespace std;

int set[NUM+2],rank[NUM+2];
bool flag[NUM+2];
void init()
{
    for(int i=1;i<=NUM;i++)
    {
        set[i]=i;
        rank[i]=0;
    }
}
int find(int i)
{
    if(set[i]!=i)
        set[i]=find(set[i]);
    return set[i];
}
void Union_set(int i,int j)
{
    i=find(i);
    j=find(j);
    if(i==j)
        return;
    if(rank[i]>rank[j])
    {
        set[j]=i;
    }
    else
    {
        if(rank[i]==rank[j])
             rank[j]++;
        set[i]=j;
    }
}
int main()
{
    int a,b,n=0,count=0,cas=0;
    bool tt=true;
    init();
    memset(flag,0,sizeof(flag));
    while(scanf("%d%d",&a,&b) && ((a+1)&&(b+1)))
    {
        if(!(a&&b))
        {
            cas++;
            if(tt && (count==n-1||count==0))
                printf("Case %d is a tree.\n",cas);
            else
                printf("Case %d is not a tree.\n",cas);
            init();
            memset(flag,0,sizeof(flag));
            n=0;
            count=0;
            tt=true;
            continue;
        }
        if(!flag[a])
        {
            flag[a]=true;
            n++;
        }
        if(!flag[b])
        {
            flag[b]=true;
            n++;
        }
        if(find(a)==find(b))
        {
        //    cout<<a<<" "<<b<<endl;
            tt=false;
        }
        else
        {
            Union_set(a,b);
            count++;
        }
    }
    return 0;
}