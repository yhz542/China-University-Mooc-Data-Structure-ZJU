#include<stdio.h>//链表实现 哈希表排序
#include<stdlib.h>
#include<math.h>
typedef struct Node *List;
struct Node
{
        int Data;
        int Address;
        int NextAddress;
        List Next;
};
int GetTableLength(int);
int NextPrime(int);
int Hash(int,int);
void Insert(List *,List,int);
int Find(List *,int,int);
List GetInput(int,List *,int);
List Sort(List,int,int *,List *,int);
List Reverse(List,int);
void Test(List L);
int main(void)
{
        List Source,Head,Tem,TemHead;
        List *HashTable;
        int BeginAddress,TotalNum,ReLength,ReTime,TableLength;
        scanf("%d %d %d",&BeginAddress,&TotalNum,&ReLength);
        TableLength=GetTableLength(TotalNum);
        HashTable=(List *)malloc(sizeof(List)*TableLength);
        for(int i=0;i<TableLength;i++)
                HashTable[i]=NULL;
        Source=GetInput(TotalNum,HashTable,TableLength);
        Head=(List)malloc(sizeof(struct Node));
        Head->Next=Sort(Source,BeginAddress,&TotalNum,HashTable,TableLength);
        ReTime=TotalNum/ReLength;
        Tem=Head;
        for(int i=0;i<ReTime;i++)
        {
                TemHead=Tem->Next;
                Tem->Next=Reverse(Tem,ReLength);
                Tem->NextAddress=Tem->Next->Address;
                Tem=TemHead;
        }
        if(Tem->Next)
                Tem->NextAddress=Tem->Next->Address;
        else
                Tem->NextAddress=-1;
        Test(Head);
        free(HashTable);
        free(Source);
        return 0;
}
int GetTableLength(int N)
{
        int Prime;
        N*=2;
        N++;
        while((N%4)!=3)
                N+=2;
        Prime=NextPrime(N);
        if(Prime<3)
                Prime=3;
        return Prime;
}
int NextPrime(int N)
{
        int i,p=N;
        while(1)
        {
                for(i=(int)sqrt(p);i>2;i--)
                        if(!(p%i))
                                break;
                if(i==2)
                                break;
                else
                                p+=4;
        }
        return p;
}
int Hash(int Key,int P)
{
        return Key%P;
}
void Insert(List *HashTable,List L,int TableLength)
{
        int Index;
        Index=Find(HashTable,L->Address,TableLength);
        if(HashTable[Index]==NULL)
        {
                HashTable[Index]=L;
        }
}
int Find(List *HashTable,int Address,int TableLength)
{
        int NewPosition,CurPosition;
        int CNum=0;
        NewPosition=CurPosition=Hash(Address,TableLength);
        while(HashTable[NewPosition]!=NULL&&HashTable[NewPosition]->Address!=Address)
        {
                if(++CNum%2)
                {
                        NewPosition=CurPosition+(CNum+1)*(CNum+1)/4;
                        if(NewPosition>=TableLength)
                                NewPosition=NewPosition%TableLength;
                }
                else
                {
                        NewPosition=CurPosition-CNum*CNum/4;
                        while(NewPosition<0)
                                NewPosition+=TableLength;
                }
        }
        return NewPosition;
}
List GetInput(int TotalNum,List *HashTable,int TableLength)
{
        List Source;
        Source=(List)malloc(sizeof(struct Node)*TotalNum);
        for(int i=0;i<TotalNum;i++)
        {
                scanf("%d %d %d",&Source[i].Address,&Source[i].Data,&Source[i].NextAddress);
                Source[i].Next=NULL;
                Insert(HashTable,Source+i,TableLength);
        }
        return Source;
}
List Sort(List Source,int BeginAddress,int *TotalNum,List *HashTable,int TableLength)
{
        if(*TotalNum<1)
                return NULL;
        List Head,Tem;
        int cnt=1;
        int Position;
        int i;
        Position=Find(HashTable,BeginAddress,TableLength);
        Head=HashTable[Position];
        Tem=Head;
        for(i=1;i<*TotalNum;i++)
        {
                Position=Find(HashTable,Tem->NextAddress,TableLength);
                cnt++;
                Tem->Next=HashTable[Position];
                Tem=Tem->Next;
                if(-1==Tem->NextAddress)
                        break;
        }
        *TotalNum=cnt;
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
