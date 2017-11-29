/*
#include<stdio.h>
#include<stdlib.h>
typedef struct Node *PtrToNode;
typedef int ElementType;
struct Node
{
    ElementType Data; // 存储结点数据 
    PtrToNode   Next; // 指向下一个结点的指针 
};
typedef PtrToNode List;// 定义单链表类型 
List Read(void); // 细节在此不表 

void Print( List L ); // 细节在此不表；空链表将输出NULL 
List Merge( List L1, List L2 );
int main()
{
    List L1, L2, L;
    L1 = Read();
    L2 = Read();
    L = Merge(L1, L2);
    Print(L);
    Print(L1);
    Print(L2);
    return 0;
}
List Read(void)
{
        List Head,Tem,Old;
        int Num;
        Head=(PtrToNode)malloc(sizeof(struct Node));
        Head->Next=NULL;
        Old=Head;
        scanf("%d",&Num);
        for(int i=0;i<Num;i++)

        {
                Tem=(PtrToNode)malloc(sizeof(struct Node));
                Tem->Next=NULL;
                scanf("%d",&Tem->Data);
                Old->Next=Tem;
                Old=Old->Next;
        }
        return Head;
}
void Print( List L )
{
        L=L->Next;
        if(!L)
                printf("NULL");
        while(L)
        {
                printf("%d ",L->Data);
                L=L->Next;
        }
        putchar('\n');
        return;
}*/
List Merge( List L1, List L2 )
{
        List Head,Tem,l1,l2;
        Head=(PtrToNode)malloc(sizeof(struct Node));
        Head->Next=NULL;
        Tem=Head;
        l1=L1->Next;
        l2=L2->Next;
        while(l1&&l2)
        {
                if(l1->Data<l2->Data)
                {
                        Tem->Next=l1;
                        l1=l1->Next;
                }
                else
                {
                        Tem->Next=l2;
                        l2=l2->Next;
                }
                Tem=Tem->Next;
        }
        while(l1)
        {
                Tem->Next=l1;
                l1=l1->Next;
                Tem=Tem->Next;
        }
        while(l2)
        {
                Tem->Next=l2;
                l2=l2->Next;
                Tem=Tem->Next;
        }
        L1->Next=NULL;
        L2->Next=NULL;
        return Head;
}
