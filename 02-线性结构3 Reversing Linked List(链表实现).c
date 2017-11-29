#include<stdio.h>
#include<stdlib.h>
typedef struct Node *List;
struct Node
{
        int Data;
        int Address;
        int NextAddress;
        List Next;
};
List GetInput(int);
List Sort(List,int,int);
List Reverse(List,int);
void Test(List L);
int main(void)
{
        List Source,Head,Tem;
        int BeginAddress,TotalNum,ReLength,ReTime;
        scanf("%d %d %d",&BeginAddress,&TotalNum,&ReLength);
        ReTime=TotalNum/ReLength;
        Source=GetInput(TotalNum);
        Source=Sort(Source,BeginAddress,TotalNum);
        Head=(List)malloc(sizeof(struct Node));
        Head->Next=Source;
        Tem=Head;
        for(int i=0;i<ReTime;i++)
        {
                Tem->Next=Reverse(Tem,ReLength);
                Tem->NextAddress=Tem->Next->Address;
                for(int j=0;j<ReLength;j++)
                {
                        Tem=Tem->Next;
                }
        }
        while(Tem->Next)
        {

                Tem=Tem->Next;
        }
        Tem->NextAddress=-1;
        Test(Head);
        return 0;
}
List GetInput(int TotalNum)
{
        List Source;
        Source=(List)malloc(sizeof(struct Node)*TotalNum);
        for(int i=0;i<TotalNum;i++)
        {
                scanf("%d %d %d",&Source[i].Address,&Source[i].Data,&Source[i].NextAddress);
                Source[i].Next=NULL;
        }
        return Source;
}
List Sort(List Source,int BeginAddress,int TotalNum)
{
        List Head=Source,Tem;
        int i;
        for(i=0;i<TotalNum;i++)
        {
                if(Source[i].Address==BeginAddress)
                {
                        Head=&Source[i];
                        break;
                }
        }
        Tem=Head;
        for(i=1;i<TotalNum-1;i++)
                for(int j=0;j<TotalNum;j++)
                {
                        if(Tem->NextAddress==Source[j].Address)
                        {
                                Tem->Next=Source+j;
                                Tem=Tem->Next;
                        }
                }
        return Head;
}
void Test(List L)
{
        L=L->Next;
        while(L->Next)
        {
                printf("%05d %d %05d\n",L->Address,L->Data,L->NextAddress);
                L=L->Next;
        }
        printf("%05d %d %d\n",L->Address,L->Data,L->NextAddress);
}
List Reverse(List Source,int ReLength)
{
        List New=Source->Next,Old,Tmp;
        Old=New->Next;
        for(int j=1;j<ReLength;j++)
        {
                Tmp=Old->Next;
                Old->Next=New;
                Old->NextAddress=New->Address;
                New=Old;
                Old=Tmp;
        }
        Source->Next->Next=Old;
        return New;
}

//remain to achieve
