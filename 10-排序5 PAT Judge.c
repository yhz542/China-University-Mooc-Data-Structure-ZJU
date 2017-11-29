#include<stdio.h>
#include<stdlib.h>
void Initialize(int x,int y,int [][y]);
void GetInput(int,int NumOfProblems,int [][NumOfProblems]);
int *Heap_Sort(int,int y,int [][y]);
void Swap(int *,int *);
void PercDown(int [],int,int,int y,int [][y]);
void Print(int **,int,int);
int *displayed;
int main(void)
{
        int NumOfUsers;
        int NumOfProblems;
        int *Sort;
        int Length;
        int former,now;
        scanf("%d",&NumOfUsers);
        scanf("%d",&NumOfProblems);
        displayed=(int *)malloc(sizeof(int)*NumOfUsers);//判断是否有题通过编译决定是否显示
        for(int i=0;i<NumOfUsers;i++)
                displayed[i]=0;
        if(NumOfUsers>0&&NumOfProblems>0)
        {
                int cnt=0;
                NumOfProblems+=2;
                int Info[NumOfUsers][NumOfProblems];//Info[][0]为总分 Info[][NumOfProblems-1]为满分数量
                Initialize(NumOfUsers,NumOfProblems,Info);
                GetInput(NumOfUsers,NumOfProblems,Info);//读取输入
                Sort=Heap_Sort(NumOfUsers,NumOfProblems,Info);
                former=Info[Sort[0]-1][0];
                for(int i=0,rank=1;i<Sort[NumOfUsers];i++)
                {
                        if(Info[Sort[i]-1][0]==former)
                                cnt++;
                        else
                        {
                                rank+=cnt;
                                former=Info[Sort[i]-1][0];
                                cnt=1;
                        }
                        printf("%d %05d",rank,Sort[i]);
                        for(int j=0;j<NumOfProblems-1;j++)
                        {
                                if(Info[Sort[i]-1][j]>-1)
                                        printf(" %d",Info[Sort[i]-1][j]);
                                else if(Info[Sort[i]-1][j]==-1)
                                        printf(" 0");
                                else
                                        printf(" %c",'-');
                        }
                        putchar('\n');
                }
                //Print((int **)Info,NumOfUsers,NumOfProblems);
        }
        return 0;
}
void Initialize(int x,int y,int (*Data)[y])
{
        for(int i=0;i<x;i++)
                for(int j=1;j<y-1;j++)
                        Data[i][j]=-2;
        for(int i=0;i<x;i++)
        {
                Data[i][0]=Data[i][y-1]=0;
        }
}
void GetInput(int NumOfUsers,int NumOfProblems,int Info[][NumOfProblems])
{
        int NumofSubmission;
        int UserID,ProblemID,Score;
        int FullMark[--NumOfProblems];
        scanf("%d",&NumofSubmission);
        for(int i=1;i<NumOfProblems;i++)
                scanf("%d",&FullMark[i]);
        for(int i=0;i<NumofSubmission;i++)
        {
                scanf("%d %d %d",&UserID,&ProblemID,&Score);
                if(Score>Info[--UserID][ProblemID])
                {

                        Info[UserID][ProblemID]=Score;
                        if(Score==FullMark[ProblemID])
                                Info[UserID][NumOfProblems]++;
                        if(Score>=0)
                                displayed[UserID]=1;//至少一道题通过编译 可以显示出来
                }
        }
        for(int i=0;i<NumOfUsers;i++)
                if(displayed[i])
                        for(int j=1;j<NumOfProblems;j++)
                                if(Info[i][j]>-1)
                                        Info[i][0]+=Info[i][j];
}
int *Heap_Sort(int x,int y,int Data[][y])
{
        int cnt=0;
        int *Tem=(int *)malloc(sizeof(int)*(x+1));
        for(int i=0,j=0;i<x;i++)
                if(displayed[i])
                {
                        Tem[j]=i+1;
                        j++;
                        cnt++;
                }
        for(int i=cnt/2-1;i>=0;i--)
        {
                PercDown(Tem,i,cnt,y,Data);
        }
        for(int i=cnt-1;i>0;i--)
        {
                Swap(&Tem[0],&Tem[i]);
                PercDown(Tem,0,i,y,Data);
        }
        Tem[x]=cnt;
        return Tem;
}
void Swap(int *a,int *b)
{
        int t=*a;
        *a=*b;
        *b=t;
}
void PercDown(int Tem[],int p,int Length,int y,int Data[][y])
{
        int Parent,Child;
        int ID1,ID2;
        int Pointone,Pointtwo;
        int NumFull1,NumFull2;
        int X;
        X=Tem[p];
        for(Parent=p;(Parent*2+1)<Length;Parent=Child)
        {
                Child=Parent*2+1;
                if(Child!=Length-1)
                {
                        ID1=Tem[Child]-1;
                        ID2=Tem[Child+1]-1;
                        Pointone=Data[ID1][0];
                        Pointtwo=Data[ID2][0];
                        NumFull1=Data[ID1][y-1];
                        NumFull2=Data[ID2][y-1];
                        if(Pointone>=Pointtwo)
                        {
                                if(Pointone>Pointtwo)
                                        Child++;
                                else if(NumFull1>NumFull2)
                                        Child++;
                                else if(NumFull1==NumFull2&&ID1<ID2)
                                        Child++;
                        }
                }

                Pointone=Data[X-1][0];
                Pointtwo=Data[Tem[Child]-1][0];
                NumFull1=Data[X-1][y-1];
                NumFull2=Data[Tem[Child]-1][y-1];
                if(Pointone<=Pointtwo)
                {
                        if(Pointone<Pointtwo||NumFull1<NumFull2)
                                break;
                        else if(NumFull1==NumFull2&&X>Tem[Child])
                                break;
                }
                        Tem[Parent]=Tem[Child];
        }
        Tem[Parent]=X;
}


void Print(int **Data,int x,int y)
{
        printf("%5s 总分","序号");
        for(int i=0;i<y-2;i++)
                printf(" 题%d",i+1);
        printf(" 满分 显示\n");
        for(int i=0;i<x;i++)
        {
                printf("%05d",i+1);
                for(int j=0;j<y;j++)
                        printf(" %3d",*((int *)Data+i*y+j));
                printf("\t%s",!displayed[i]?"No":"Yes");
                putchar('\n');
        }
}
