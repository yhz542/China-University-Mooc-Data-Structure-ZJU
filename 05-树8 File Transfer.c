#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#define MAXSIZE 10000
typedef int ElementType;
typedef int SetName;
/* struct
{
        ElementType Data;
        int Parent;
}SetType;*/
typedef ElementType SetType[MAXSIZE];
SetName Find(SetType S,ElementType X);
bool Check(int,int,SetType);
void Link(int,int,SetType);
int main(void)
{
        int AmountComputer,Component=0;
        int NumberComputer1,NumberComputer2;
        SetType Group;
        char Switch;
        scanf("%d",&AmountComputer);
        for(int i=0;i<AmountComputer;i++)
                Group[i]=-1;
        while((Switch=getchar())=='\n');
        while(Switch!='S'&&Switch!='s')
        {
                scanf("%d %d",&NumberComputer1,&NumberComputer2);
                NumberComputer1--;
                NumberComputer2--;
                if(Switch=='C'||'c'==Switch)
                {
                        if(Check(NumberComputer1,NumberComputer2,Group))
                                puts("yes");
                        else
                                puts("no");
                }
                else if('I'==Switch||'i'==Switch)
                {
                        Link(NumberComputer1,NumberComputer2,Group);
                }
                while((Switch=getchar())=='\n');
        }
        for(int i=0;i<AmountComputer;i++)
        {
                if(Group[i]<0)
                        Component++;
        }
        if(Component==1)
                printf("The network is connected.");
        else
                printf("There are %d components.",Component);
        return 0;
}
bool Check(int Num1,int Num2,SetType G)
{
        if(Find(G,Num1)!=Find(G,Num2))
                return false;
        else
                return true;
}
void Union(SetType G,SetName Root1,SetName Root2)
{
        if(G[Root2]<G[Root1])
        {
                G[Root2]+=G[Root1];//为负数 比谁小 即绝对值大
                G[Root1]=Root2;
        }
        else
        {
                G[Root1]+=G[Root2];
                G[Root2]=Root1;
        }
        return;
}
SetName Find(SetType S,ElementType X)
{
        if(S[X]>=0)
                return S[X]=Find(S,S[X]);
        else
                return X;
}
void Link(int Num1,int Num2,SetType G)
{
        int Parent1,Parent2;
        Parent1=Find(G,Num1);
        Parent2=Find(G,Num2);
        if(Parent1!=Parent2)
        {
                Union(G,Parent1,Parent2);
        }
        return;
}
/*SetName Find(SetType S[],ElementType X)
{
        int i;
        for(i=0;i<MaxSize&&S[i].Data!=X;i++);
        if(i>=MaxSize)
                return -1;
        for(;S[i].Parent>=0;i=S[i].Parent);
        return i;
}*/
