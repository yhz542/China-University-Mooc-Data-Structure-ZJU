#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<string.h>
typedef struct Node *PNode;
struct Node
{
        long long QQNumber;
        char Command;
        int Order;
        char Key[17];
        int Status;
};
void GetInput(int,int*);
void Print(int);
int compare(const void *a,const void *b);
void Process(int [],int);
void Output(int);
PNode Data;
int main(void)
{
        int N;
        scanf("%d",&N);
        int Index[N];
        getchar();
        GetInput(N,Index);
        qsort(Index,N,sizeof(Index[0]),compare);
        Process(Index,N);
        Output(N);
        //Print(N);
        return 0;
}
void GetInput(int N,int Index[])
{
        Data=(PNode)malloc(sizeof(struct Node)*N);
        for(int i=0;i<N;i++)
        {
                scanf("%c %lld %s",&Data[i].Command,&Data[i].QQNumber,Data[i].Key);
                Data[i].Order=i;
                Index[i]=i;
                getchar();
        }
}
int compare(const void *a,const void *b)
{
        int a1=*(int *)a;
        int b1=*(int *)b;
        const struct Node *A=&Data[a1];
        const struct Node *B=&Data[b1];
        if(A->QQNumber!=B->QQNumber)
                return A->QQNumber-B->QQNumber;
        else
                return A->Order-B->Order;
}
void Process(int Index[],int N)
{
        long long former=-1;
        PNode current;
        char Key[17]="";
        for(int i=0;i<N;i++)
        {
                current=&Data[Index[i]];
                if(former!=current->QQNumber)
                {
                        Key[0]='\0';
                        if('L'==current->Command)
                                current->Status=0;//ERROR: Not Exist
                        else
                        {
                                current->Status=1;
                                strcpy(Key,current->Key);
                        }
                }
                else
                {
                        if('L'==current->Command)
                        {
                                if('\0'==Key[0])
                                        current->Status=0;
                                else if(strcmp(Key,current->Key)==0)
                                        current->Status=2;//Login: OK
                                else
                                        current->Status=3;//ERROR: Wrong PW
                        }
                        else
                        {
                                if('\0'==Key[0])
                                {
                                        current->Status=1;//New: OK
                                        strcpy(Key,current->Key);
                                }
                                else
                                        current->Status=4;//ERROR: Exist
                        }
                }
                former=current->QQNumber;
        }
}
void Output(int N)
{
        for(int i=0;i<N;i++)
        {
                switch(Data[i].Status)
                {
                        case 0:
                                puts("ERROR: Not Exist");
                                break;
                        case 1:
                                puts("New: OK");
                                break;
                        case 2:
                                puts("Login: OK");
                                break;
                        case 3:
                                puts("ERROR: Wrong PW");
                                break;
                        case 4:
                                puts("ERROR: Exist");
                }
        }
}
void Print(int N)
{
        printf("%-4s %-10s %s 密码\n","操作","次序","号码");
        for(int i=0;i<N;i++)
        {
                printf("%4c %10lld %3d  %s\n",Data[i].Command,Data[i].QQNumber,Data[i].Order,Data[i].Key);
        }
}
