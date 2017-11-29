#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<stdbool.h>
#define MaxSize 65
typedef struct HNode *Heap;
struct HNode{
        int *Data;
        int Size;
        int Capacity;
};
typedef Heap MinHeap;
typedef struct CNode *Ccode;
struct CNode
{
        char c;//存储的字母
        int n;//字母出现的次数
        char code[MaxSize];
};
typedef struct TNode *Tree;
struct TNode
{
        int Data;
        Tree Left;
        Tree Right;
};
Ccode GetTimes(int,MinHeap);
void GetCode(Ccode,int);
void Insert(MinHeap,int);
int DeleteMin(MinHeap);
MinHeap CreateMinHeap(int);
int CalculateWPL(MinHeap);
int CountStudentWPL(Ccode,int);
bool Check(Ccode,int);
Tree CreateTree(void);
int main(void)
{
        int NumOfChar,NumOfStudent,MinLength,WPLOfSt;
        MinHeap H;
        Ccode character;
        scanf("%d",&NumOfChar);
        H=CreateMinHeap(NumOfChar);//创建最小堆
        character=GetTimes(NumOfChar,H);//读取字符以及频率
        MinLength=CalculateWPL(H);//计算WPL最小编码长度
        scanf("%d",&NumOfStudent);//获取待测试学生数量
        int answer[NumOfStudent];
        for(int i=0;i<NumOfStudent;i++)
        {
                GetCode(character,NumOfChar);//获取每个学生的编码
                if(CountStudentWPL(character,NumOfChar)!=MinLength)//计算WPL是否相等
                {
                        printf("No\n");
                        continue;
                }
                if(Check(character,NumOfChar))//检查前缀码
                        printf("Yes\n");
                else
                        printf("No\n");
        }
        return 0;
}
Ccode GetTimes(int NumOfChar,MinHeap H)
{
        int times;
        char c;
        Ccode character;
        character=(Ccode)malloc(sizeof(struct CNode)*NumOfChar);
        for(int i=0;i<NumOfChar;i++)
        {
                getchar();
                scanf("%c",&c);
                scanf("%d",&times);
                Insert(H,times);
                character[i].c=c;
                character[i].n=times;
        }
        return character;
}
void GetCode(Ccode character,int NumOfChar)
{
        char c;
        for(int i=0;i<NumOfChar;i++)
        {
                getchar();//吸收空格回车
                scanf("%c",&c);
                for(int j=0;j<NumOfChar;j++)
                {
                        if(character[j].c==c)
                        {
                                scanf(" %s",character[j].code);
                                break;
                        }
                }
        }
}
MinHeap CreateMinHeap(int NumOfChar)
{
        MinHeap H;
        H=(MinHeap)malloc(sizeof(struct HNode));
        H->Size=0;
        H->Capacity=NumOfChar;
        H->Data=(int *)malloc(sizeof(int)*(NumOfChar+1));
        H->Data[0]=-1000;
        return H;
}
void Insert(MinHeap H,int X)
{
        int i;
        i=++H->Size;
        for(;H->Data[i/2]>X;i/=2)
        {
                H->Data[i]=H->Data[i/2];
        }
        H->Data[i]=X;
        return;
}
int DeleteMin(MinHeap H)
{
        int Parent,Child;
        int Minitem,X;
        Minitem=H->Data[1];
        X=H->Data[H->Size--];
        for(Parent=1;Parent*2<=H->Size;Parent=Child)
        {
                Child=Parent*2;
                if((Child!=H->Size)&&(H->Data[Child]>H->Data[Child+1]))
                        Child++;
                if(X<=H->Data[Child])
                        break;
                else
                        H->Data[Parent]=H->Data[Child];
        }
        H->Data[Parent]=X;
        return Minitem;
}
int CalculateWPL(MinHeap H)
{

        int left,right,sum=0;
        for(int i=1;i<H->Size;)
        {
                left=DeleteMin(H);
                right=DeleteMin(H);
                sum+=right+left;
                Insert(H,right+left);
        }
        return sum;
}
int CountStudentWPL(Ccode character,int NumOfChar)
{
        int WPL=0,Tem;
        for(int i=0;i<NumOfChar;i++)
        {
                Tem=strlen((character+i)->code);
                if(Tem>NumOfChar-1)
                        return -1;
                Tem*=character[i].n;
                WPL+=Tem;
        }
        return WPL;
}
bool Check(Ccode character,int NumOfChar)
{
        char c;
        Tree Head=CreateTree();
        Tree tem;
        for(int i=0;i<NumOfChar;i++)
        {
                tem=Head;
                int j=strlen(character[i].code);
                for(int k=0;k<j-1;k++)
                {
                        c=character[i].code[k];
                        if(c=='0')
                        {
                                if(!tem->Left)
                                {
                                        tem->Left=CreateTree();
                                }
                                else if(tem->Left->Data>0)
                                        return false;
                                tem=tem->Left;
                        }
                        else if(c=='1')
                        {
                                if(!tem->Right)
                                {
                                        tem->Right=CreateTree();
                                }
                                else if(tem->Right->Data>0)
                                        return false;
                                tem=tem->Right;
                        }
                }
                c=character[i].code[j-1];
                if(c=='0')
                {
                        if(!tem->Left)
                        {
                                tem->Left=CreateTree();
                                tem->Left->Data=1;
                        }
                        else
                                return false;
                }
                else
                {
                        if(!tem->Right)
                        {
                                tem->Right=CreateTree();
                                tem->Right->Data=1;
                        }
                        else
                                return false;
                }
        }
        return true;
}
Tree CreateTree(void)
{
        Tree New;
        New=(Tree)malloc(sizeof(struct TNode));
        New->Data=-1;
        New->Left=New->Right=NULL;
        return New;
}
