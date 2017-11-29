#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
void GetInput(int **,int **,int);
bool IsInsertSort(int *,int *,int);
void InsertionSort(int *);
void MergeSort(int *,int);
int FindSublength(int *,int);
void Merge(int *,int *,int,int,int);
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
                printf("Merge Sort\n");
                MergeSort(Result,N);
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
void MergeSort(int *Data,int N)
{
        int SubLength,i;
        int TemData[N];
        SubLength=FindSublength(Data,N);
        for(i=0;i<N-2*SubLength;i+=2*SubLength)
        {
                Merge(Data,TemData,i,i+SubLength,i+2*SubLength-1);
        }
        if(i+SubLength<N)
                Merge(Data,TemData,i,i+SubLength,N-1);
        else
                while(i<N)
                {
                        TemData[i]=Data[i];
                        i++;
                }
        for(i=0;i<N;i++)
                Data[i]=TemData[i];
}
int FindSublength(int *Data,int N)
{
        int i,j,k,cnt=2,flag,time;
        for(i=1;i<N;i++)
        {
                if(Data[i]<Data[i-1])
                        break;
        }
        while(cnt<=i)
                cnt*=2;
        cnt/=2;
        if(!N%cnt)
                time=N/cnt;
        else
                time=N/cnt+1;
        for(;cnt>2;cnt/=2)
        {
                flag=0;
                for(j=0,k=0;j<time;j++)
                {
                        for(i=1,k++;i<cnt&&k<N;i++,k++)
                        {
                                if(Data[k]<Data[k-1])
                                {
                                        flag=1;
                                        break;
                                }
                        }
                        if(flag)
                                break;
                }
                if(!flag)
                        break;
        }
        return cnt;
}
void Merge(int *Data,int *TemData,int L,int C,int R)
{
        int l=L,r=C,Index=L;
        while(l<=C-1&&r<=R)
        {
                if(Data[l]<Data[r])
                {
                        TemData[Index]=Data[l];
                        l++;
                }
                else
                {
                        TemData[Index]=Data[r];
                        r++;
                }
                Index++;
        }
        while(l<=C-1)
                TemData[Index++]=Data[l++];
        while(r<=R)
                TemData[Index++]=Data[r++];
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
