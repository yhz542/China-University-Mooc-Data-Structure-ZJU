#include<stdio.h>
#include<stdlib.h>
int MaxSeq(int [],int);
int main(void)
{
        int Amount;
        int MaxSubSeqSum;
        int *SubSequence;
        scanf("%d",&Amount);
        if(Amount<=0)
                return 0;
        SubSequence=(int *)malloc(sizeof(int)*Amount);
        for(int i=0;i<Amount;i++)
                scanf("%d",&SubSequence[i]);
        MaxSubSeqSum=MaxSeq(SubSequence,Amount);
        printf("%d",MaxSubSeqSum);
        return 0;
}
int MaxSeq(int Seq[],int Amount)
{
        int MaxSubSeqSum=Seq[0];
        int TemSubSeqSum=0;
        for(int i=0;i<Amount;i++)
        {
                TemSubSeqSum+=Seq[i];
                if(MaxSubSeqSum<TemSubSeqSum)
                        MaxSubSeqSum=TemSubSeqSum;
                if(TemSubSeqSum<0)
                        TemSubSeqSum=0;
        }
        return MaxSubSeqSum;
}
