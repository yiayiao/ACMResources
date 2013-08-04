//经典题目，食物链。结题报告：http://blog.csdn.net/c0de4fun/article/details/7318642
#include <iostream>
using namespace std;

struct node{
     int pa;
     int re;  
}p[50005];

void init(int n)
{
     int i;
     for(i=1;i<=n;i++)
     {
          p[i].pa=i;
          p[i].re=0;            
     }
}

int find(int x)
{
    int temp;
    if(x==p[x].pa)
          return x;
    temp=p[x].pa;
    p[x].pa=find(temp);
    p[x].re=(p[temp].re+p[x].re)%3;
    return
          p[x].pa;        
}
void union_set(int x,int y,int rootx,int rooty,int d)
{
    p[rooty].pa=rootx;
    p[rooty].re=(3+(d-1)+p[x].re-p[y].re)%3; 
}
int main()
{
    int n,k,x,y,d,i,px,py,num=0;
    
    scanf("%d%d",&n,&k);
    init(n);
    
    while(k--)
    {
          scanf("%d%d%d",&d,&x,&y);
          if(x>n||y>n)
               num++;
          else if(d==2&&x==y)
               num++;
          else
          {
               px=find(x);
               py=find(y);
               if(px!=py)
                    union_set(x,y,px,py,d);
               else
               {
                    if(d==1 && p[x].re!=p[y].re)
                          num++;
                    else if(d==2 && (p[y].re-p[x].re+3)%3!=1)
                          num++;         
               }                   
          }           
    }
    printf("%d\n",num);
    //system("pause");
    return 0;
}