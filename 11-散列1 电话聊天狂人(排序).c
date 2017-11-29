#include<stdio.h>
#include<stdlib.h>
#include<string.h>
char **GetInput(int);
void Print(char **,int);
int compare(const void *a,const void *b)
{
        return strcmp(*(char**)a,*(char**)b);
}

int main(void)
{
        int Num;
        int Max=1,cnt=1;
        char **Call;
        char CallKing[12];
        char tem[12];
        scanf("%d",&Num);
        Call=GetInput(Num);
        qsort(Call,Num*2,sizeof(char*),compare);
        //Print(Call,Num);
        strcpy(CallKing,Call[0]);
        strcpy(tem,Call[0]);
        for(int i=1;i<2*Num;i++)
        {
                if(strcmp(tem,Call[i])==0)
                        cnt++;
                else
                {
                        if(Max<cnt)
                        {
                                Max=cnt;
                                strcpy(CallKing,tem);
                        }
                        strcpy(tem,Call[i]);
                        cnt=1;
                }
        }
        printf("%s %d",CallKing,Max);
        return 0;
}
char **GetInput(int Num)
{
        char **New;
        New=(char**)malloc(sizeof(char *)*(2*Num));
        for(int i=0;i<2*Num;i++)
                New[i]=(char *)malloc(sizeof(char)*12);
        for(int i=0;i<2*Num;i++)
                scanf("%s",New[i]);
        return New;
}
void Print(char **Call,int Num)
{
        for(int i=0;i<Num;i++)
                printf("%s %s\n",Call[2*i],Call[2*i+1]);
}
