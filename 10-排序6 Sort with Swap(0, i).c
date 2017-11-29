#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
void GetInput(int *,int *,int);
int Sort(int *,int *,int);
bool IsOrder(int *,int);
void Swap(int *,int *);
void Display(int *,int);
int main(void)
{
        int Num;
        int *Data;
        int *Index;
        scanf("%d",&Num);
        Data=(int*)malloc(sizeof(int)*Num);
        Index=(int*)malloc(sizeof(int)*Num);
        GetInput(Data,Index,Num);
        Sort(Data,Index,Num);
        //printf("%d",Sort(Data,Num));
        return 0;
}
void GetInput(int Data[],int Index[],int Num)
{
        for(int i=0;i<Num;i++)
        {
                scanf("%d",&Data[i]);
                Index[Data[i]]=i;
        }
}
int Sort(int Data[],int Index[],int Length)
{
        int search=1;
        int i;
        int cnt=0;
        int tem;
        while(1)
        {
                if(0==Index[0])
                {
                        for(i=search;i<Length;i++)
                                if(Index[i]!=i)
                                {
                                        tem=Index[i];
                                        Index[i]=0;
                                        Index[0]=tem;
                                        cnt++;
                                        search=i;
                                        break;
                                }
                        if(i==Length)
                                break;
                }
                tem=Index[0];//存储0元素此时所在的位置
                Index[0]=Index[tem];
                Index[tem]=tem;
                cnt++;
        }
        printf("%d",cnt);
}
void Display(int *Data,int Length)
{
        for(int i=0;i<Length;i++)
                printf("%d ",Data[i]);
        putchar('\n');
}
