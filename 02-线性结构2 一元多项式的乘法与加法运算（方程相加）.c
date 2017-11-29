//another kind of Way to achieve 方程相加
#include<stdio.h>
#include<stdlib.h>
typedef struct Node* List;
struct Node
{
        int coefficient;
        int exponent;
        List next;
};
List enter(void);
List add(List,List);
List multiply(List,List);
void display(List);
int main(void)
{
        List first;
        List second;
        List sum;
        List product;
        first=enter();
        second=enter();
        sum=add(first,second);
        product=multiply(first,second);
        display(product);
        putchar('\n');
        display(sum);
        return 0;
}
List enter(void)
{
        List head;
        List New;
        List rear;
        head=(List)malloc(sizeof(struct Node));
        head->next=NULL;
        rear=head;
        int amount;
        scanf("%d",&amount);
        while(amount--)
        {
                New=(List)malloc(sizeof(struct Node));
                scanf("%d %d",&New->coefficient,&New->exponent);
                if(0==New->coefficient)
                {
                        free(New);
                        continue;
                }
                rear->next=New;
                New->next=NULL;
                rear=New;
        }
        New=head;
        head=head->next;
        free(New);
        return head;
}
List add(List first,List second)
{
        List result;
        List tem;
        List rear;
        result=(List)malloc(sizeof(struct Node));
        result->next=NULL;
        rear=result;
        while(first&&second)
        {
                tem=(List)malloc(sizeof(struct Node));
                if(first->exponent>second->exponent)
                {
                        tem->exponent=first->exponent;
                        tem->coefficient=first->coefficient;
                        first=first->next;
                }
                else if(first->exponent<second->exponent)
                {
                        tem->exponent=second->exponent;
                        tem->coefficient=second->coefficient;
                        second=second->next;
                }
                else
                {
                        tem->exponent=first->exponent;
                        tem->coefficient=first->coefficient+second->coefficient;
                        first=first->next;
                        second=second->next;
                        if(0==tem->coefficient)
                        {
                               free(tem);
                               continue;
                        }
                }
                tem->next=NULL;
                rear->next=tem;
                rear=tem;
        }
        while(first)
        {
                tem=(List)malloc(sizeof(struct Node));
                tem->exponent=first->exponent;
                tem->coefficient=first->coefficient;
                first=first->next;
                tem->next=NULL;
                rear->next=tem;
                rear=tem;
        }
        while(second)
        {
                tem=(List)malloc(sizeof(struct Node));
                tem->exponent=second->exponent;
                tem->coefficient=second->coefficient;
                second=second->next;
                tem->next=NULL;
                rear->next=tem;
                rear=tem;
        }
        tem=result;
        result=result->next;
        free(tem);
        return result;
}
List multiply(List first,List second)
{
        if(!first||!second)
                return NULL;
        List product,tem,rear,sec;
        product=(List)malloc(sizeof(struct Node));
        rear=product;
        rear->next=NULL;
        sec=second;
        while(sec)
        {
                tem=(List)malloc(sizeof(struct Node));
                tem->coefficient=first->coefficient*sec->coefficient;
                tem->exponent=first->exponent+sec->exponent;
                rear->next=tem;
                rear=tem;
                sec=sec->next;
        }
        rear->next=NULL;
        first=first->next;
        while(first)
        {
                rear=product->next;
                sec=second;
                while(sec)
                {
                        tem=(List)malloc(sizeof(struct Node));
                        tem->coefficient=first->coefficient*sec->coefficient;
                        tem->exponent=first->exponent+sec->exponent;
                        tem->next=NULL;
                        while(rear->next&&tem->exponent<rear->next->exponent)
                                rear=rear->next;
                        if(!(rear->next))
                        {
                                rear->next=tem;
                                rear=tem;
                        }
                        else//等于大于的情况
                        {
                                if(tem->exponent==rear->next->exponent)
                                {
                                        rear->next->coefficient+=tem->coefficient;
                                        if(0==rear->next->coefficient)
                                        {
                                                rear->next=rear->next->next;
                                                free(rear->next);
                                        }
                                        free(tem);
                                }
                                else//大于
                                {
                                        tem->next=rear->next;
                                        rear->next=tem;
                                        rear=tem;
                                }
                        }
                        sec=sec->next;
                }
                first=first->next;
        }
        rear->next=NULL;
        tem=product;
        product=product->next;
        free(tem);
        return product;
}
void display(List L)
{
        int first=0;
        if(!L)
        {
                printf("0 0");
        }
        while(L)
        {
                if(!first)
                {
                        first=1;
                        printf("%d %d",(*L).coefficient,L->exponent);

                }
                else
                        printf(" %d %d",(*L).coefficient,L->exponent);
                L=(*L).next;
        }
        return;
}
