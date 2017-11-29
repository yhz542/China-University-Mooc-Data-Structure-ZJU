#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<stdbool.h>
bool IsPrime(int);
int Redefine(int);
int *GetInput(int,int);
int Hash(int,int);
void Hashing(int,int);
int main(void)
{
        int MSize;//表的大小
        int N;//输入元素个数
        int *Data;
        scanf("%d %d",&MSize,&N);
        if(!IsPrime(MSize))
                MSize=Redefine(MSize);
        Hashing(MSize,N);
        return 0;
}
bool IsPrime(int MSize)
{
        if(MSize==1)
                return false;
        int Times;
        int i;
        Times=(int)sqrt(MSize);
        if(Times==1)
                return true;
        for(i=Times;i>2;i--)
        {
                if(MSize%i==0)
                        break;
        }
        if(MSize%2&&i==2)
                return true;
        else
                return false;
}
int Redefine(int MSize)
{
        int i;
        if(MSize==1)
        {
                MSize=2;
                return MSize;
        }
        MSize=(MSize%2?MSize+2:MSize+1);
        while(1)
        {
                for(i=(int)sqrt(MSize);i>2;i--)
                        if(!(MSize%i))
                                break;
                if(i==2)
                        break;
                MSize+=2;
        }
        return MSize;
}
void Hashing(int MSize,int N)
{
        int Data[MSize],InList[MSize];
        int Tem,Index;
        int offset;
        for(int i=0;i<MSize;i++)
        {
                Data[i]=-1;
                InList[i]=-1;
        }
        for(int i=0;i<N;i++)
        {
                scanf("%d",&Tem);
                Index=Hash(Tem,MSize);
                if(Data[Index]==-1)
                {
                        Data[Index]=Tem;
                        InList[i]=Index;
                }
                else
                {
                        for(int j=1;j<MSize;j++)
                        {
                                offset=(Index+j*j)%MSize;
                                if(Data[offset]==-1)
                                {
                                        Data[offset]=Tem;
                                        InList[i]=offset;
                                        break;
                                }
                        }
                }
        }
        for(int i=0,flag=0;i<N;i++)
        {
                if(!flag)
                {
                        printf("%d",InList[i]);
                        flag=1;
                }
                else
                {
                        if(InList[i]!=-1)
                                printf(" %d",InList[i]);
                        else
                                printf(" -");
                }
        }
}
int Hash(int Key,int P)
{
        return Key%P;
}
