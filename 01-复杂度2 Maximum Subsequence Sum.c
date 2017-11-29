#include<stdio.h>
#include<stdlib.h>
void MaxSeq(int [],int);
int main(void)
{
        int Amount;
        int *SubSequence;
        scanf("%d",&Amount);
        if(Amount<=0)
                return 0;
        SubSequence=(int *)malloc(sizeof(int)*Amount);
        for(int i=0;i<Amount;i++)
                scanf("%d",&SubSequence[i]);
        MaxSeq(SubSequence,Amount);
        return 0;
}
void MaxSeq(int Seq[],int Amount)
{
        int MaxSubSeqSum=Seq[0];
        int TemSubSeqSum=0;
        int First,Last;
        int Tem=Seq[0];
        First=Last=Seq[0];
        for(int i=0;i<Amount;i++)
        {
                TemSubSeqSum+=Seq[i];
                if(MaxSubSeqSum<TemSubSeqSum)
                {
                        MaxSubSeqSum=TemSubSeqSum;
                        Last=Seq[i];
                        First=Tem;
                }
                if(TemSubSeqSum<0)
                {
                        TemSubSeqSum=0;
                        Tem=Seq[i+1];
                }
        }
        if(MaxSubSeqSum<0)
        {
                MaxSubSeqSum=0;
                First=Seq[0];
                Last=Seq[Amount-1];
        }
        printf("%d %d %d",MaxSubSeqSum,First,Last);
        return;
}
