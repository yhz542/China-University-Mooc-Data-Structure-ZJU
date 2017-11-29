#include<stdio.h>
#include<stdlib.h>
struct Polynomial;
typedef struct Polynomial *Equation;
struct Polynomial
{
        int Coefficient;
        int Index;
        Equation Next;
} ;
Equation CreateNode(void);
Equation GetInput(int);
Equation Multiplication(Equation,Equation);
Equation Add(Equation,Equation);
void Display(Equation);
int main(void)
{
        int NumNonZero;
        Equation First,Second,Sum,Product;
        scanf("%d",&NumNonZero);
        First=GetInput(NumNonZero);
        scanf("%d",&NumNonZero);
        Second=GetInput(NumNonZero);
        Sum=Add(First->Next,Second->Next);
        Product=Multiplication(First->Next,Second->Next);
        Display(Product);
        putchar('\n');
        Display(Sum);
        return 0;
}
Equation CreateNode(void)
{
        Equation New;
        New=(Equation)malloc(sizeof(struct Polynomial));
        New->Coefficient=0;
        New->Index=0;
        New->Next=NULL;
        return New;
}
Equation GetInput(int Num)
{
        Equation Head,Former,Later;
        Head=CreateNode();
        Former=Head;
        for(int i=0;i<Num;i++)
        {
                Later=CreateNode();
                scanf("%d %d",&Later->Coefficient,&Later->Index);
                if(Later->Coefficient==0)
                {
                        free(Later);
                        continue;
                }
                Former->Next=Later;
                Former=Later;
        }
        return Head;
}
Equation Multiplication(Equation First,Equation Second)
{
        Equation Head_one,Head_two,New,Old,E1,E2,Tem;
        E1=First;
        E2=Second;
        Head_one=CreateNode();
        if(!First||!Second)
                return Head_one;
        Head_two=CreateNode();
        Old=Head_one;
        while(E2)
        {
                New=CreateNode();
                New->Coefficient=E1->Coefficient*E2->Coefficient;
                New->Index=E1->Index+E2->Index;
                E2=E2->Next;
                Old->Next=New;
                Old=New;
        }
        E1=E1->Next;
        E2=Second;
        Old=Head_two;
        if(!E1)
               return Head_one;
        while(E2)
        {
                New=CreateNode();
                New->Coefficient=E1->Coefficient*E2->Coefficient;
                New->Index=E1->Index+E2->Index;
                E2=E2->Next;
                Old->Next=New;
                Old=New;
        }
        Tem=Head_one;
        Head_one=Add(Head_one->Next,Head_two->Next);
        while(Tem)
        {
                New=Tem;
                Tem=Tem->Next;
                free(New);
        }
        E1=E1->Next;
        while(E1)
        {
                E2=Second;
                New=Head_two->Next;
                while(E2)
                {
                        New->Coefficient=E1->Coefficient*E2->Coefficient;
                        New->Index=E1->Index+E2->Index;
                        E2=E2->Next;
                        New=New->Next;
                }
                Tem=Head_one;
                Head_one=Add(Head_one->Next,Head_two->Next);
                while(Tem)
                {
                        New=Tem;
                        Tem=Tem->Next;
                        free(New);
                }
                E1=E1->Next;
        }
        while(Second)
        {
                New=Second;
                Second=Second->Next;
                free(New);
        }
        return Head_one;
}
Equation Add(Equation First,Equation Second)
{
        Equation Head,New,Old;
        Head=CreateNode();
        Old=Head;
        while(First&&Second)
        {
                if(First->Index>Second->Index)
                {
                        New=CreateNode();
                        New->Coefficient=First->Coefficient;
                        New->Index=First->Index;
                        First=First->Next;
                }
                else if(First->Index<Second->Index)
                {
                        New=CreateNode();
                        New->Coefficient=Second->Coefficient;
                        New->Index=Second->Index;
                        Second=Second->Next;
                }
                else
                {
                        New=CreateNode();
                        New->Coefficient=Second->Coefficient+First->Coefficient;
                        New->Index=Second->Index;
                        First=First->Next;
                        Second=Second->Next;
                        if(New->Coefficient==0)
                        {
                                free(New);
                                continue;
                        }
                }
                Old->Next=New;
                Old=New;
        }
        while(First)
        {
                New=CreateNode();
                New->Coefficient=First->Coefficient;
                New->Index=First->Index;
                First=First->Next;
                Old->Next=New;
                Old=New;
        }
        while(Second)
        {
                New=CreateNode();
                New->Coefficient=Second->Coefficient;
                New->Index=Second->Index;
                Second=Second->Next;
                Old->Next=New;
                Old=New;
        }
        return Head;
}
void Display(Equation One)
{
        One=One->Next;
        if(!One)
                printf("0 0");
        else
        {
                printf("%d %d",One->Coefficient,One->Index);
                One=One->Next;
                while(One)
                {
                        printf(" %d %d",One->Coefficient,One->Index);
                        One=One->Next;
                }
        }
        return;
}
