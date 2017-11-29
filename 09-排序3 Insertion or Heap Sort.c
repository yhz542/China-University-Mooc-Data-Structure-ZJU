#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
void GetInput(int **,int **,int);
bool IsInsertSort(int *,int *,int);
void InsertionSort(int *);
void Heap_Sort(int [],int);
void Swap(int *,int *);
void PercDown(int [],int,int);
int GetLength(int *,int);
void Display(int *,int);
int Step;
int main(void)
{
        int N;
        int *Source,*Result;
        scanf("%d",&N);
        GetInput(&Source,&Result,N);
        if(IsInsertSort(Source,Result,N))
        {
                printf("Insertion Sort\n");
                InsertionSort(Result);
        }
        else
        {
                printf("Heap Sort\n");
                Heap_Sort(Result,N);
        }
        Display(Result,N);
        return 0;
}
void GetInput(int **Source,int **Result,int N)
{
        *Source=(int *)malloc(sizeof(int)*N);
        *Result=(int *)malloc(sizeof(int)*N);
        for(int i=0;i<N;i++)
                scanf("%d",&(*Source)[i]);
        for(int i=0;i<N;i++)
                scanf("%d",&(*Result)[i]);
}
bool IsInsertSort(int *Source,int *Result,int N)
{
        int Index,Tem;
        for(Index=1;Index<N;Index++)
        {
                if(Result[Index]<Result[Index-1])
                        break;
        }
        Tem=Index;
        for(;Index<N;Index++)
        {
                if(Result[Index]!=Source[Index])
                {
                        return false;
                }
        }
        Step=Tem;
        return true;
}
void InsertionSort(int *Data)
{
        for(int i=Step;i>0;i--)
        {
                if(Data[i]<Data[i-1])
                {
                        Data[i]+=Data[i-1];
                        Data[i-1]=Data[i]-Data[i-1];
                        Data[i]-=Data[i-1];
                }
        }
}
void Heap_Sort(int Data[],int Length)
{
        int i=GetLength(Data,Length);
        Swap(&Data[0],&Data[i]);
        PercDown(Data,0,i);
}
void Swap(int *a,int *b)
{
        int t=*a;
        *a=*b;
        *b=t;
}
void PercDown(int Data[],int p,int Length)
{
        int Parent,Child;
        int X;
        X=Data[p];
        for(Parent=p;(Parent*2+1)<Length;Parent=Child)
        {
                Child=Parent*2+1;
                if((Child!=Length-1)&&(Data[Child]<Data[Child+1]))
                        Child++;
                if(X>=Data[Child])
                        break;
                else
                        Data[Parent]=Data[Child];
        }
        Data[Parent]=X;
}
int GetLength(int *Data,int N)
{
        int Index;
        int Max=Data[0];
        for(int i=N-1;i>1;i--)
        {
                if(Max>Data[i])
                {
                        Index=i;
                        break;
                }
        }
        return Index;
}


void Display(int *Data,int N)
{
        if(N>1)
        {
                printf("%d",Data[0]);
                for(int i=1;i<N;i++)
                        printf(" %d",Data[i]);
        }
        else
                printf("%d",Data[0]);
}
