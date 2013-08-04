#include <iostream>
#include <cstring>
#include <cstdio>
#include <algorithm>
using namespace std;

const int maxn = 201000;
int a[maxn], n, m, k1, k2;
struct Node 
{
	Node *ch[2], *fa;
	int size, val, add;
	bool rev;

	bool dir(){ return this == fa->ch[1]; }
	void set(Node *x, int p);
	void update();
	void pushdown();
	void REV();
	void ADD(int x);
}mem[maxn], *root, *nul, *cur = mem;

inline void Node::set(Node *x, int p)
{
	this->ch[p] = x;
	if(x != nul)
		x->fa = this;
}

inline void Node::pushdown()
{
	if(this == nul)
		return ;
	if(add)
	{
		ch[0]->ADD(add);
		ch[1]->ADD(add);
	}
	if(rev)
	{
		ch[0]->REV();
		ch[1]->REV();
	}
	add = rev = 0;
}

inline void Node::update()
{
	size = ch[0]->size + ch[1]->size + 1;
}

inline void Node::ADD(int x)
{
	if(this == nul)
		return ;
	val += x;
	add += x;
}  

inline void Node::REV()
{
	if(this == nul)
		return ;
	rev ^= 1;
	swap(ch[0], ch[1]);
}

void rot(Node *x)
{
    static Node* y;	y=x->fa;
    static bool d; d=x->dir();
    y->pushdown();
    x->pushdown();
    y->set(x->ch[!d], d);
    y->fa->set(x, y->dir());
    x->set(y, !d);
    y->update();
    if(y==root) root=x;
}

void splay(Node *x,Node *f=nul)
{
    x->pushdown();
    while(x->fa!=f)
    {
        if(x->fa->fa==f)rot(x);
        else
        {
            if(x->fa->dir()==x->dir())rot(x->fa);
            else rot(x);
            rot(x);
        }
    }
    x->update();
}

Node *newNode(int val)
{
    static Node*p;
    p=cur++;
    p->ch[0]=p->ch[1]=p->fa=nul;
    p->size=1;
    p->val=val;
    p->add=p->rev=0;
    return p;
}

Node* find(int k)
{
	static Node* now; now =  root;
	while(1)
	{
	//	printf("%d\n",now->ch[0]->size+1);
		now->pushdown();
        if(k == now->ch[0]->size+1)
			return now;
        if(k <= now->ch[0]->size)
			now = now->ch[0];
        else 
		{
			k -= now->ch[0]->size+1;
			now = now->ch[1];
		}
	}
}

void change(int s, int e, int cmd, bool d)
{
	s++, e++;
	splay(find(s-1));
	splay(find(e+1), root);
	if(d) 
		root->ch[1]->ch[0]->REV();
	else if(cmd)
		root->ch[1]->ch[0]->ADD(cmd);
	splay(root->ch[1]->ch[0]);
}

void insert(int k, Node *x)
{
	k ++;
	splay(find(k));
	splay(find(k+1), root);
	root->ch[1]->set(x, 0);
	splay(root->ch[1]->ch[0]);
}

Node* del(int s, int e)
{
	static Node *p;
	s ++, e ++;
	splay(find(s-1));
	splay(find(e+1), root);
	p = root->ch[1]->ch[0];
	root->ch[1]->set(nul, 0);
	splay(root->ch[1]);
	return p;
}

Node* maketree(int l, int r)
{
	if(l > r) return nul;
	int m = (l + r) >> 1;
	Node* p = newNode(a[m]);
	p->set(maketree(l, m-1), 0);
	p->set(maketree(m+1, r), 1);
	p->update();
	return p;
}

char cmd[30];
void print(Node * x)
{
	if(x == nul) 
		return ;
	x->pushdown();
	print(x->ch[0]);
	printf("%d", x->val);
	print(x->ch[1]);
}

int main()
{
	int i, x, y, z, cas = 0;
	Node *p;
	while(scanf("%d %d %d %d", &n, &m, &k1, &k2), n||m||k1||k2)
	{
		cas ++;
		printf("Case #%d:\n", cas);
		cur = mem;
		nul = newNode(0);
		nul->fa = nul->ch[0] = nul->ch[1] = nul;
		nul->size = 0;
		for(int i=1; i<=n; i++)
			scanf("%d", &a[i]);
		a[0] = a[n+1] = 0;
		root = maketree(0, n+1);
		//print(root);
		while(m --)
		{
			scanf("%s", cmd);
			if(cmd[0] == 'q')
			{
				printf("%d\n", find(2)->val);
			}
			else if(cmd[0] == 'a')
			{
				scanf("%d", &x);
				change(1, k2, x, false);
			}
			else if(cmd[0] == 'r')
			{
				change(1, k1, 0, true);
			}
			else if(cmd[0] == 'i')
			{
				scanf("%d", &x);
				ins(1, newNode(x));
				n++;
			}
			else if(cmd[0] == 'm')
			{
				scanf("%d", &x);
				if(x == 2)
				{
					p = del(1, 1);
					insert(n-1, p);
				}
				else
				{
					p = del(n, n);
					insert(0, p);
				}
			}
			else
			{
				del(1, 1);
				n--;
			}
		}
	}
	return 0;
}
