#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
typedef int Vertex;
typedef struct ENode *PtrToENode;
struct ENode
{
        Vertex V1,V2;
};
typedef PtrToENode Edge;
typedef struct AdjVNode *PtrToAdjVNode;
struct AdjVNode
{
        Vertex Adj;
        PtrToAdjVNode Next;
};
typedef struct VNode
{
        //int Data;
        PtrToAdjVNode FirstEdge;
}*AdjList;
typedef struct GNode *PtrToGNode;
struct GNode
{
        int Nv;
        int Ne;
        AdjList G;
};
typedef PtrToGNode LGraph;
LGraph CreateGraph(int);
void InsertEdge(LGraph,Edge);
LGraph BuildGraph(void);

void GetInput(int **,int **,int);//读取哈希表中的数据
void Sort(int *,int *,int);//将元素大小进行表排序
int *CalculateIndegree(const int *,int,LGraph);//计算每个点的入度
void Output(LGraph Graph,int *Data,int *Indegree,int *Index,int N);
void Print(LGraph,int *,int);
int main(void)
{
        int N;
        LGraph Graph;
        int *Data,*Index,*Indegree;
        scanf("%d",&N);
        if(N>0)
        {
                Graph=CreateGraph(N);
                GetInput(&Data,&Index,N);
                Sort(Data,Index,N);
                Indegree=CalculateIndegree(Data,N,Graph);
                Output(Graph,Data,Indegree,Index,N);
        }
        return 0;
}
void GetInput(int **Data,int **Index,int N)
{
        *Data=(int *)malloc(sizeof(int)*N);
        *Index=(int *)malloc(sizeof(int)*N);
        for(int i=0;i<N;i++)
        {
                scanf("%d",(*Data)+i);
               (*Index)[i]=i;
        }
}
void Sort(int *Data,int *Index,int Length)
{
        int i,Tem;
        for(int P=1;P<Length;P++)
        {
                Tem=Index[P];
                for(i=P;i>0&&Data[Index[i-1]]>Data[Tem];i--)
                        Index[i]=Index[i-1];
                Index[i]=Tem;
        }
}
LGraph CreateGraph(int VertexNum)
{
        Vertex V;
        LGraph Graph;
        Graph=(LGraph)malloc(sizeof(struct GNode));
        Graph->Nv=VertexNum;
        Graph->Ne=0;
        Graph->G=(AdjList)malloc(sizeof(struct VNode)*Graph->Nv);
        for(V=0;V<VertexNum;V++)
                Graph->G[V].FirstEdge=NULL;
        return Graph;
}
void InsertEdge(LGraph Graph,Edge E)
{
        Graph->Ne++;
        PtrToAdjVNode NewNode;
        NewNode=(PtrToAdjVNode)malloc(sizeof(struct AdjVNode));
        NewNode->Adj=E->V2;
        NewNode->Next=Graph->G[E->V1].FirstEdge;
        Graph->G[E->V1].FirstEdge=NewNode;
}
int *CalculateIndegree(const int *Data,int N,LGraph Graph)
{
        int *Indegree;
        int Remainder;
        Edge E;
        E=(Edge)malloc(sizeof(struct ENode));
        Indegree=(int *)malloc(sizeof(int)*N);
        for(int i=0;i<N;i++)//初始化入度
                Indegree[i]=0;
        for(int i=0;i<N;i++)//计算入度，插入边
        {
                if(Data[i]>-1)//如果数据存在
                {
                        Remainder=Data[i]%N;
                        if(Remainder!=i)//如果表不在自己可以一次插入的位置上
                        {
                                for(int j=Remainder;j!=i;j=(j+1)%N)
                                {
                                        E->V1=j;
                                        E->V2=i;
                                        Indegree[i]++;
                                        InsertEdge(Graph,E);
                                }
                        }
                }
        }
        return Indegree;
}

void Output(LGraph Graph,int *Data,int *Indegree,int *Index,int N)
{
        int V;
        int Start;
        PtrToAdjVNode W;
        int Times;
        int Min=-1;
        for(Start=0;Start<N&&Data[Index[Start]]<0;Start++);
        for(int i=Start;i<N;i++)
        {
                if(Indegree[Index[i]]==0)
                {
                        Min=Index[i];
                        break;
                }
        }
        Times=N-Start-1;
        if(Min!=-1)
                printf("%d",Data[Min]);
        while(Times-->0)
        {
                V=Min;
                Indegree[V]=-1;
                for(W=Graph->G[V].FirstEdge;W;W=W->Next)
                {
                        --Indegree[W->Adj];
                }
                for(int i=Start;i<N;i++)
                        if(Indegree[Index[i]]==0&&Indegree[Index[i]]!=-1)
                        {
                                Min=Index[i];
                                Indegree[Index[i]]=-1;
                                break;
                        }
                printf(" %d",Data[Min]);
        }
}

void Print(LGraph Graph,int *Data,int N)
{
        PtrToAdjVNode W;
        for(int i=0;i<N;i++)
        {
                printf("%2d:",Data[i]);
                for(W=Graph->G[i].FirstEdge;W;W=W->Next)
                {
                        printf("%2d ",Data[W->Adj]);
                }
                putchar('\n');
        }
}
