#include<stdio.h>
#include<stdlib.h>
#define min -10000
int *create(int,int *);
void Insert(int,int *,int *);
void print(int *);
int main(void)
{
        int *heap,size;
        int length;
        int times;
        int tem;
        scanf("%d %d",&length,&times);
        heap=create(length,&size);
        for(int i=0;i<length;i++)
        {
                scanf("%d",&tem);
                Insert(tem,heap,&size);
        }
        for(int i=0;i<times;i++)
                print(heap);
        return 0;
}
int *create(int length,int *size)
{
        int *heap=(int *)malloc(sizeof(int)*(length+1));
        heap[0]=min;
        *size=0;
        return heap;
}
void Insert(int number,int *heap,int *size)
{
        int i;
        for(i=++(*size);heap[i/2]>number;i/=2)
        {
                heap[i]=heap[i/2];
        }
        heap[i]=number;
}
void print(int *heap)
{
        int index;
        scanf("%d",&index);
        printf("%d",heap[index]);
        while(index>1)
        {
                index/=2;
                printf(" %d",heap[index]);
        }
        printf("\n");
}
