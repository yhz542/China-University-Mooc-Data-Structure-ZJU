#include<stdio.h>
#include<stdlib.h>
#define MaxDigit 4 //最多判定4位数
#define Radix 10 //10进制
typedef struct Node *PtrToNode;
struct Node
{
        int key;
        PtrToNode next;
};
struct HeadNode
{
        PtrToNode head,tail;
};
typedef struct HeadNode Bucket[Radix];

int GetDigit(int X,int D);
void LSDRadixSort(int [],int);//基数排序 次位优先仅限正数
void MSDRadixSort(int [],int);//主位优先
void MSD(int [],int,int,int);

int *GetInput(int);
void Selection_Sort(int [],int);//选择排序
void Bubble_Sort(int [],int);//冒泡排序
void Insertion_Sort(int [],int);//插入排序

void Shell_Sort(int [],int);//原始希尔排序
void Shell_Sort_Hibbard(int [],int);//希尔排序Hibbard序列
void Shell_Sort_Sedgewick(int [],int);//希尔排序sedgewick序列
void Shell_Sort_Selection(int [],int);//希尔排序，选择排序实现
void Shell_Sort_Bubble_Sort(int [],int);//希尔排序，冒泡排序实现

void Heap_Sort(int [],int);//堆排序
void Swap(int *,int *);
void PercDown(int [],int,int);

void Merge(int  [],int [],int,int,int);
void Msort(int [],int [],int,int);
void Merge_Sort(int[],int);//归并排序（递归实现）
void Merge_pass(int [],int [],int,int);
void Merge_Sort_Iteration(int [],int);//归并排序（迭代实现）

void OffbeatSort(int [],int);
void Swap(int *,int *);

void Display(int [],int);
int main(void)
{
        int *Data;
        int Length;
        scanf("%d",&Length);
        Data=GetInput(Length);
        //Selection_Sort(Data,Length);
        //Bubble_Sort(Data,Length);
        //Insertion_Sort(Data,Length);
        //Shell_Sort(Data,Length);
        //Shell_Sort_Hibbard(Data,Length);
        Shell_Sort_Sedgewick(Data,Length);
        //Shell_Sort_Selection(Data,Length);
        //Shell_Sort_Bubble_Sort(Data,Length);
        //Heap_Sort(Data,Length);
        //Merge_Sort(Data,Length);
        //Merge_Sort_Iteration(Data,Length);
        //LSDRadixSort(Data,Length);
        //MSDRadixSort(Data,Length);
        Display(Data,Length);
        return 0;
}
int *GetInput(int Length)
{
        int *Data;
        Data=(int *)malloc(sizeof(int)*Length);
        for(int i=0;i<Length;i++)
                scanf("%d",&Data[i]);
        return Data;
}
void Selection_Sort(int Data[],int Length)
{
        for(int i=0,Min,Index;i<Length-1;i++)
        {
                Min=Data[i];
                Index=i;
                for(int j=i+1;j<Length;j++)
                        if(Data[j]<Min)
                        {
                                Min=Data[j];
                                Index=j;
                        }
                Data[Index]=Data[i];
                Data[i]=Min;
        }
}
void Bubble_Sort(int Data[],int Length)
{
        int flag;
        for(int P=Length-1;P>0;P--)
        {
                flag=0;
                for(int i=0;i<P;i++)
                {
                        if(Data[i]>Data[i+1])
                        {
                                flag=1;
                                Data[i]+=Data[i+1];
                                Data[i+1]=Data[i]-Data[i+1];
                                Data[i]-=Data[i+1];
                        }
                }
                if(!flag)
                        break;
        }
}
void Insertion_Sort(int Data[],int Length)
{
        int i,Tem;
        for(int P=1;P<Length;P++)
        {
                Tem=Data[P];
                for(i=P;i>0&&Data[i-1]>Tem;i--)
                        Data[i]=Data[i-1];
                Data[i]=Tem;
        }
}
void Shell_Sort(int Data[],int Length)
{
        for(int D=Length/2;D>0;D/=2)
        {
                for(int P=D,Tem,i;P<Length;P++)
                {
                        Tem=Data[P];
                        for(i=P;i>=D&&Data[i-D]>Tem;i-=D)
                                Data[i]=Data[i-D];
                        Data[i]=Tem;
                }
        }
}
void Shell_Sort_Hibbard(int Data[],int Length)
{
        int Hibbard=1,S,Tem;
        for(S=2;S-1<Length;S*=2);
        S/=2;
        for(Hibbard=S-1;Hibbard>0;S/=2,Hibbard=S-1)
                for(int P=Hibbard,i;P<Length;P++)
                {
                        Tem=Data[P];
                        for(i=P;i>=Hibbard&&Data[i-Hibbard]>Tem;i-=Hibbard)
                                Data[i]=Data[i-Hibbard];
                        Data[i]=Tem;
                }
}
void Shell_Sort_Sedgewick(int Data[],int Length)
{
        int Si,D,P,i;
        int Tem;
        int Sedgewick[]={146305,64769,36289,16001,8929,3905,2161,929,505,209,109,41,19,5,1,0};
        for(Si=0;Sedgewick[Si]>=Length;Si++);
        for(D=Sedgewick[Si];D>0;D=Sedgewick[++Si])
                for(P=D;P<Length;P++)
                {
                        Tem=Data[P];
                        for(i=P;i>=D&&Data[i-D]>Tem;i-=D)
                                Data[i]=Data[i-D];
                        Data[i]=Tem;
                }
}
void Shell_Sort_Selection(int Data[],int Length)
{
        int Si,D,P,i;
        int Min,Index;
        int Sedgewick[]={146305,64769,36289,16001,8929,3905,2161,929,505,209,109,41,19,5,1,0};
        for(Si=0;Sedgewick[Si]>=Length;Si++);
        for(D=Sedgewick[Si];D>0;D=Sedgewick[++Si])
                for(P=0;P<Length-D;P++)
                {
                        Min=Data[P];
                        Index=P;
                        for(i=P+D;i<Length;i+=D)
                                if(Data[i]<Min)
                                {
                                        Min=Data[i];
                                        Index=i;
                                }
                        Data[Index]=Data[P];
                        Data[P]=Min;
                }
}
void Shell_Sort_Bubble_Sort(int Data[],int Length)
{
        int Si,D,P,i;
        int Sedgewick[]={146305,64769,36289,16001,8929,3905,2161,929,505,209,109,41,19,5,1,0};
        for(Si=0;Sedgewick[Si]>=Length;Si++);
        for(D=Sedgewick[Si];D>0;D=Sedgewick[++Si])
        {
                int flag;
                for(i=0;i<D&&i<Length-D;i++)
                {
                        for(P=Length-D;P>0;P-=D)
                        {
                                flag=0;
                                for(int j=i;j<P;j+=D)
                                {
                                        if(Data[j]>Data[j+D])
                                        {
                                                flag=1;
                                                Data[j]+=Data[j+D];
                                                Data[j+D]=Data[j]-Data[j+D];
                                                Data[j]-=Data[j+D];
                                        }
                                }
                                if(!flag)
                                        break;
                        }

                }
        }
}

void Heap_Sort(int Data[],int Length)
{
        int i;
        for(i=Length/2-1;i>=0;i--)
                PercDown(Data,i,Length);
        for(i=Length-1;i>0;i--)
        {
                Swap(&Data[0],&Data[i]);
                PercDown(Data,0,i);
        }
}
void Swap(int *a,int *b)
{
        int t=*a;
        *a=*b;
        *b=t;
}
void PercDown(int Data[],int p,int Length)
{
        int Parent,Child;
        int X;
        X=Data[p];
        for(Parent=p;(Parent*2+1)<Length;Parent=Child)
        {
                Child=Parent*2+1;
                if((Child!=Length-1)&&(Data[Child]<Data[Child+1]))
                        Child++;
                if(X>=Data[Child])
                        break;
                else
                        Data[Parent]=Data[Child];
        }
        Data[Parent]=X;
}
void Merge(int  Data[],int TemData[],int L,int R,int RightEnd)//L左边起始位置,R右边起始位置，RightEnd右边终止位置
{
        int LeftEnd,Num,Tem;
        int i;
        LeftEnd=R-1;
        Tem=L;
        Num=RightEnd-L+1;
        while(L<=LeftEnd&&R<=RightEnd)
        {
                if(Data[L]<=Data[R])
                        TemData[Tem++]=Data[L++];
                else
                        TemData[Tem++]=Data[R++];
        }
        while(L<=LeftEnd)
                TemData[Tem++]=Data[L++];
        while(R<=RightEnd)
                TemData[Tem++]=Data[R++];
        for(i=0;i<Num;i++,RightEnd--)
                Data[RightEnd]=TemData[RightEnd];
}
void Msort(int Data[],int TemData[],int L,int RightEnd)
{
        int Center;
        if(L<RightEnd)
        {
                Center=(L+RightEnd)/2;
                Msort(Data,TemData,L,Center);
                Msort(Data,TemData,Center+1,RightEnd);
                Merge(Data,TemData,L,Center+1,RightEnd);
        }
}
void Merge_Sort(int Data[],int Length)
{
        int *TemData;
        TemData=(int *)malloc(sizeof(int)*Length);
        if(TemData)
        {
                Msort(Data,TemData,0,Length-1);
                free(TemData);
        }
        else
                printf("空间不足");
}

void Merge_pass(int Data[],int TemData[],int Length,int SubLength)
{
        int i,j;
        for(i=0;i<=Length-2*SubLength;i+=2*SubLength)
                Merge(Data,TemData,i,i+SubLength,i+2*SubLength-1);
        if(i+SubLength<Length)
                Merge(Data,TemData,i,i+SubLength,Length-1);
        else
                for(j=i;j<Length;j++)
                        TemData[j]=Data[j];
}
void Merge_Sort_Iteration(int Data[],int Length)
{
        int SubLength;
        int *TemData;
        SubLength=1;
        TemData=(int *)malloc(sizeof(int)*Length);
        if(TemData)
        {
                while(SubLength<Length)
                {
                        Merge_pass(Data,TemData,Length,SubLength);
                        SubLength*=2;
                        Merge_pass(TemData,Data,Length,SubLength);
                        SubLength*=2;
                }
                free(TemData);
        }
        else
                printf("空间不足");
}

int GetDigit(int X,int D)
{
        int d,i;
        for(i=1;i<=D;i++)
        {
                d=X%Radix;
                X/=Radix;
        }
        return d;
}
void LSDRadixSort(int Data[],int Length)
{
        int D,Di,i;
        Bucket B;
        PtrToNode tem,p,List=NULL;
        for(i=0;i<Radix;i++)
                B[i].head=B[i].tail=NULL;
        for(i=0;i<Length;i++)//将数组元素逆序插入链表
        {
                tem=(PtrToNode)malloc(sizeof(struct Node));
                tem->key=Data[i];
                tem->next=List;
                List=tem;
        }
        for(D=1;D<=MaxDigit;D++)
        {
                p=List;
                while(p)//对第D位进行插入 D=1 85插在5中 D=2插在8中
                {
                        Di=GetDigit(p->key,D);
                        tem=p;
                        p=p->next;
                        tem->next=NULL;
                        if(!B[Di].head)
                                B[Di].head=B[Di].tail=tem;
                        else
                        {
                                B[Di].tail->next=tem;//链表尾部进行插入
                                B[Di].tail=tem;
                        }
                }
                List=NULL;
                for(Di=Radix-1;Di>=0;Di--)
                {
                        if(B[Di].head)//将桶中元素按顺序插回链表中 再次进行位数排序 9 89 789
                        {
                                B[Di].tail->next=List;
                                List=B[Di].head;
                                B[Di].head=B[Di].tail=NULL;
                        }
                }
        }
        for(i=0;i<Length;i++)//将排好序的链表元素依次放回数组中
        {
                tem=List;
                List=List->next;
                Data[i]=tem->key;
                free(tem);
        }
}

void MSDRadixSort(int Data[],int Length)
{
        MSD(Data,0,Length-1,MaxDigit);
}
void MSD(int Data[],int L,int R,int D)
{
        int Di,i,j;
        Bucket B;
        PtrToNode tem,p,List=NULL;
        if(D==0)//递归的基准情形
                return;
        for(i=0;i<Radix;i++)//将桶初始化
                B[i].head=B[i].tail=NULL;
        for(i=L;i<=R;i++)//将数组中的元素倒序放入链表中
        {
                tem=(PtrToNode)malloc(sizeof(struct Node));
                tem->key=Data[i];
                tem->next=List;
                List=tem;
        }
        p=List;//指向链表表头
        while(p)
        {
                Di=GetDigit(p->key,D);
                tem=p;
                p=p->next;
                tem->next=NULL;
                if(!B[Di].head)
                        B[Di].tail=tem;
                tem->next=B[Di].head;
                B[Di].head=tem;
        }
        i=j=L;
        for(Di=0;Di<Radix;Di++)
        {
                if(B[Di].head)
                {
                        p=B[Di].head;
                        while(p)
                        {
                                tem=p;
                                p=p->next;
                                Data[j++]=tem->key;
                                free(tem);
                        }
                        MSD(Data,i,j-1,D-1);
                        i=j;
                }
        }
}
void OffbeatSort(int Data[],int N)
{
        int i, j, mini, maxi;
        for (i=1;i<=N/2;i++)
        {
                mini=maxi=i;
                for(j=i+1;j<N-i+2;++j)
                {
                        if(Data[j]<Data[mini])
                                mini=j;
                        else if(Data[j]>Data[maxi])
                                maxi=j;
                }
                if(mini!=i)
                        Swap(&Data[mini],&Data[i]);
                if(maxi!=N-i+1 )
                {
                        if(maxi==i)
                                Swap(&Data[mini], &Data[N-i+1]);
                        else
                                Swap(&Data[maxi], &Data[N-i+1]);
                }
        }
}
void Swap(int *a,int *b)
{
        int c=*a;
        *a=*b;
        *b=c;
}

void Display(int Data[],int N)
{
        if(N>1)
        {
                printf("%d",Data[0]);
                for(int i=1;i<N;i++)
                        printf(" %d",Data[i]);
        }
        else
                printf("%d",Data[0]);
}
/*int flag=0;
        for(int i=0;i<N;i++)
        {
                if(flag)
                        printf(" %d",Data[i]);
                else
                {
                        printf("%d",Data[i]);
                        flag=1;
                }
        }*/
