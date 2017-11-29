#include<stdio.h>
#include<stdlib.h>
typedef struct Node *PtrToNode;
struct Node
{
        int Address;
        int Data;
        int Next;
};
PtrToNode CreateSource(int);
void Sort(PtrToNode,int,int);
void Reverse(PtrToNode,int,int);
int EffectiveNum(PtrToNode);
void Output(PtrToNode,int);
int main(void)
{
        PtrToNode Source;
        int EffNum;
        int BeginAddress,TotalNum,ReLength;
        scanf("%d %d %d",&BeginAddress,&TotalNum,&ReLength);
        Source=CreateSource(TotalNum);
        Sort(Source,BeginAddress,TotalNum);
        EffNum=EffectiveNum(Source);
        Reverse(Source,EffNum,ReLength);
        Output(Source,EffNum);
        return 0;
}
PtrToNode CreateSource(int TotalNum)
{
        PtrToNode Source,New,Old;
        Source=(PtrToNode)malloc(sizeof(struct Node)*TotalNum);
        for(int i=0;i<TotalNum;i++)
        {
                scanf("%d %d %d",&Source[i].Address,&Source[i].Data,&Source[i].Next);
        }
        return Source;
}
void Sort(PtrToNode Source,int BeginAddress,int TotalNum)
{
        struct Node Tem;
        for(int i=0;i<TotalNum;i++)
                if(Source[i].Address==BeginAddress)
                {
                        Tem=Source[i];
                        Source[i]=Source[0];
                        Source[0]=Tem;
                        break;
                }
        for(int i=1;i<TotalNum-1;i++)
        {
                for(int j=i;j<TotalNum;j++)
                {
                        if(Source[j].Address==Source[i-1].Next)
                        {
                                Tem=Source[j];
                                Source[j]=Source[i];
                                Source[i]=Tem;
                                break;
                        }
                }
        }
        return;
}
void Output(PtrToNode Result,int TotalNum)
{
        for(int i=0;i<TotalNum;i++)
        {
                printf("%05d %d",Result[i].Address,Result[i].Data);
                if(Result[i].Next!=-1)
                        printf(" %05d",Result[i].Next);
                else
                        printf(" -1");
                putchar('\n');
        }
        return;
}
void Reverse(PtrToNode Source,int TotalNum,int ReLength)
{
        int times;
        struct Node Tem;
        times=TotalNum/ReLength;
        for(int i=0;i<times;i++)
        {
                for(int j=0;j<ReLength/2;j++)
                {
                        Tem=Source[(i+1)*ReLength-j-1];
                        Source[(i+1)*ReLength-j-1]=Source[i*ReLength+j];
                        Source[i*ReLength+j]=Tem;
                }
        }
        for(int i=0;i<TotalNum-1;i++)
        {
                Source[i].Next=Source[i+1].Address;
        }
        Source[TotalNum-1].Next=-1;
        return;
}
int EffectiveNum(PtrToNode Source)
{
        int i=0;
        while(Source[i].Next!=-1)
        {
                i++;
        }
        return i+1;
}
