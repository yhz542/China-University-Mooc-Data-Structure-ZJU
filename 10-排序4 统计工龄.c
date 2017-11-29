#include<stdio.h>
#include<stdlib.h>
void GetInput(int [],int);
void Print(int []);
int main(void)
{
        int Num;
        int Data[51]={0};
        scanf("%d",&Num);
        GetInput(Data,Num);
        Print(Data);
        return 0;
}
void GetInput(int Data[],int Num)
{
        int Tem;
        for(int i=0;i<Num;i++)
        {
                scanf("%d",&Tem);
                Data[Tem]++;
        }
}
void Print(int Data[])
{
        for(int i=0;i<51;i++)
        {
                if(Data[i])
                        printf("%d:%d\n",i,Data[i]);
        }
}
