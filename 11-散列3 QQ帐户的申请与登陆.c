#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define NotExist -655350000
typedef struct HNode *HashTable;
struct HNode
{
        char QQNumber[11];
        char Key[17];
};
int GetTableSize(int);
HashTable CreateTable(int);
int Hash(char [],int);
int Find(HashTable,char [],int);
void Login(HashTable,char [],char [],int);
void SetUp(HashTable,char [],char [],int);
void Insert(HashTable,char [],char [],int);
void Print(HashTable,int);
int main(void)
{
        int N;
        int TableSize;
        HashTable H;
        scanf("%d",&N);
        getchar();
        if(0==N)
                return 0;
        TableSize=GetTableSize(N);
        H=CreateTable(TableSize);

        char Command;
        char Key[17];
        char QQNumber[11];
        for(int i=0;i<N;i++)
        {
                scanf("%c %s %s",&Command,QQNumber,Key);
                if('L'==Command)
                        Login(H,QQNumber,Key,TableSize);
                else
                        SetUp(H,QQNumber,Key,TableSize);
                getchar();
        }
        //Print(H,TableSize);
        return 0;
}
int GetTableSize(int N)
{
        N*=2;
        N++;
        while((N%4)!=3)
                N+=2;
        return N;
}
HashTable CreateTable(int TableSize)
{
        HashTable New;
        New=(HashTable)malloc(sizeof(struct HNode)*TableSize);
        for(int i=0;i<TableSize;i++)
        {
                New[i].Key[0]='\0';
                New[i].QQNumber[0]='n';
        }
        return New;
}
int Find(HashTable H,char QQNumber[],int TableSize)
{
        int i;
        int Position;
        int Offset;
        int TemPosition;
        Position=Hash(QQNumber,TableSize);
        if(H[Position].QQNumber[0]=='n')
                return Position=-Position;
        else if(strcmp(H[Position].QQNumber,QQNumber)==0)
                return Position;
        for(i=1;i<TableSize;i++)
        {
                Offset=i*i;
                TemPosition=(Position+Offset)%TableSize;
                if(strcmp(H[TemPosition].QQNumber,QQNumber)==0)
                        return TemPosition;
                else if(H[TemPosition].QQNumber[0]=='n')
                        return TemPosition=-TemPosition;
                else
                {
                        TemPosition=Position-(Offset%TableSize);
                        if(TemPosition<0)
                                TemPosition+=TableSize;
                        if(strcmp(H[TemPosition].QQNumber,QQNumber)==0)
                                return TemPosition;
                        else if(H[TemPosition].QQNumber[0]=='n')
                                return TemPosition=-TemPosition;
                }
        }
        if(i==TableSize)
                return NotExist;//表中放满了，且没有该元素
}
int Hash(char Key[],int P)
{
        int i;
        char Tem[8];
        int Num;
        for(i=0;i<7&&Key[i]!='\0';i++)
                Tem[i]=Key[i];
        Tem[i]='\0';
        Num=(atoi(Tem));
        return Num%P;
}
void Login(HashTable H,char QQNumber[],char Key[],int TableSize)
{
        int Position;
        Position=Find(H,QQNumber,TableSize);
        if(Position>=0)
        {
                if(strcmp(Key,H[Position].Key)==0)
                        puts("Login: OK");
                else
                        puts("ERROR: Wrong PW");
        }
        else
                puts("ERROR: Not Exist");
}
void SetUp(HashTable H,char QQNumber[],char Key[],int TableSize)
{
        int Position;
        Position=Find(H,QQNumber,TableSize);
        if(Position<0)
        {
                Insert(H,QQNumber,Key,Position);
                puts("New: OK");
        }
        else if(Position>=0)
        {
                if(H[Position].QQNumber[0]=='n')
                {
                        Insert(H,QQNumber,Key,Position);
                        puts("New: OK");
                        return;
                }
                else
                        puts("ERROR: Exist");
        }
}
void Insert(HashTable H,char QQNumber[],char Key[],int Position)
{
        Position=-Position;
        if(H[Position].QQNumber[0]=='n')
        {
                strcpy(H[Position].QQNumber,QQNumber);
                strcpy(H[Position].Key,Key);
        }
        else
                puts("Insert Error!");
}


void Print(HashTable H,int TableSize)
{
        printf("%d\n",TableSize);
        for(int i=0;i<TableSize;i++)
                printf("i=%d %s %s\n",i,H[i].QQNumber,H[i].Key);
}
