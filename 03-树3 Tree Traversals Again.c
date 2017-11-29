#include<stdio.h>
#include<stdlib.h>
struct SNode
{
        int Top;
        int Capacity;
        int *Store;
};
typedef struct SNode *Stack;
Stack CreateStack(int);
int Pop(Stack);
void Push(Stack, int);
void GetInput(int *, int *,int,Stack);
void MakePost(int *,int *,int *,int);
void Display(int *,int);
int main(void)
{
        int TotalNum;
        int *PreOrder, *InOrder, *PostOrder;
        Stack New;
        scanf("%d", &TotalNum);
        if(TotalNum==0)
                return 0;
        New = CreateStack(TotalNum);
        PreOrder = (int *)malloc(sizeof(int) * TotalNum);
        InOrder = (int *)malloc(sizeof(int) * TotalNum);
        PostOrder = (int *)malloc(sizeof(int) * TotalNum);
        GetInput(PreOrder,InOrder,TotalNum,New);
        MakePost(PreOrder,InOrder,PostOrder,TotalNum);
        Display(PostOrder,TotalNum);
        return 0;
}
Stack CreateStack(int TotalNum)
{
        Stack New;
        New = (Stack)malloc(sizeof(struct SNode));
        New->Capacity = TotalNum;
        New->Top = -1;
        New->Store = (int *)malloc(sizeof(int) * TotalNum);
        return New;
}
void Push(Stack New, int Num)
{
        New->Store[++(New->Top)] = Num;
}
int Pop(Stack New)
{
        return New->Store[New->Top--];
}
void GetInput(int *PreOrder, int *InOrder,int TotalNum,Stack New)
{
        getchar();
        char Manipulation[5];
        int Tem;
        int PreCount=0;
        int InCount=0;
        for(int i=0;i<2*TotalNum;i++)
        {
                scanf("%s",Manipulation);
                if(Manipulation[1]=='u')
                {
                        scanf("%d",&Tem);
                        PreOrder[PreCount++]=Tem;
                        Push(New,Tem);
                }
                else
                {
                        InOrder[InCount++]=Pop(New);
                }
        }
}
void MakePost(int *PreOrder,int *InOrder,int *PostOrder,int TotalNum)
{
        int pre=0,post;
        int i=0;
        PostOrder[TotalNum-1]=PreOrder[0];
        while(InOrder[i++]!=PreOrder[0]);
        i--;
        if(i>0)
                MakePost(PreOrder+1,InOrder,PostOrder,i);
        if(TotalNum-i-1>0)
                MakePost(PreOrder+i+1,InOrder+i+1,PostOrder+i,TotalNum-i-1);
}
void Display(int *PostOrder,int TotalNum)
{
        printf("%d",PostOrder[0]);
        for(int i=1;i<TotalNum;i++)
                printf(" %d",PostOrder[i]);
}
