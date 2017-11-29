#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#define MaxVertexNum 105
#define INFINITY 65535
typedef int Vertex;
typedef int WeightType;
typedef struct ENode *PtrToENode;
struct ENode
{
        Vertex V1,V2;
        WeightType Weight;
};
typedef PtrToENode Edge;
typedef struct AdjVNode *PtrToAdjVNode;
struct AdjVNode
{
        Vertex Adj;
        WeightType Weight;
        PtrToAdjVNode Next;
};
typedef struct VNode
{
        PtrToAdjVNode FirstEdge;
}*AdjList;
typedef struct GNode *PtrToGNode;
struct GNode
{
        int Nv;
        int Ne;
        AdjList G;
        AdjList W;
};
typedef PtrToGNode LGraph;
LGraph CreateGraph(int);
void InsertEdge(LGraph,Edge);
LGraph BuildGraph(void);
bool TopSort(LGraph,Vertex [],int []);
void ReverseTopSort(LGraph,Vertex[],int [],int[],int);
typedef struct QNode
{
        int Capacity;
        int Front,Rear;
        int *Data;
}*Queue;
Queue CreateQueue(int);
bool AddQ(Queue,int);
int DeleteQ(Queue);
bool IsEmpty(Queue Q);
void Display(int);
void Print(LGraph);
int D[MaxVertexNum][MaxVertexNum];
int main(void)
{
        int Last;
        LGraph Graph;
        Graph=BuildGraph();
        for(int i=0;i<Graph->Nv;i++)
                for(int j=0;j<Graph->Nv;j++)
                        D[i][j]=INFINITY;
        int *earlytime,*latelytime;
        earlytime=(int *)malloc(sizeof(int)*Graph->Nv);
        latelytime=(int *)malloc(sizeof(int)*Graph->Nv);
        Vertex TopOrder[MaxVertexNum];
        Vertex ReTopOrder[MaxVertexNum];
        if(TopSort(Graph,TopOrder,earlytime))
        {
                int Max=earlytime[0];
                for(int i=1;i<Graph->Nv;i++)
                {
                        if(Max<earlytime[i])
                        {
                                Max=earlytime[i];
                                Last=i;
                        }
                }
                printf("%d\n",Max);
        }
        else
        {
                printf("0");
                return 0;
        }
        ReverseTopSort(Graph,ReTopOrder,latelytime,earlytime,Last);
        Display(Graph->Nv);
        return 0;
}
LGraph CreateGraph(int VertexNum)
{
        Vertex V;
        LGraph Graph;
        Graph=(LGraph)malloc(sizeof(struct GNode));
        Graph->Nv=VertexNum;
        Graph->Ne=0;
        Graph->G=(AdjList)malloc(sizeof(struct VNode)*Graph->Nv);
        Graph->W=(AdjList)malloc(sizeof(struct VNode)*Graph->Nv);
        for(V=0;V<VertexNum;V++)
        {
                Graph->G[V].FirstEdge=NULL;
                Graph->W[V].FirstEdge=NULL;
        }
        return Graph;
}
void InsertEdge(LGraph Graph,Edge E)
{
        PtrToAdjVNode NewNode;
        NewNode=(PtrToAdjVNode)malloc(sizeof(struct AdjVNode));
        NewNode->Adj=--E->V2;
        NewNode->Weight=E->Weight;
        NewNode->Next=Graph->G[--E->V1].FirstEdge;
        Graph->G[E->V1].FirstEdge=NewNode;
        NewNode=(PtrToAdjVNode)malloc(sizeof(struct AdjVNode));
        NewNode->Adj=E->V1;
        NewNode->Weight=E->Weight;
        NewNode->Next=Graph->W[E->V2].FirstEdge;
        Graph->W[E->V2].FirstEdge=NewNode;
}
LGraph BuildGraph(void)
{
        LGraph Graph;
        Edge E;
        Vertex V;
        int Nv,i;
        scanf("%d",&Nv);
        Graph=CreateGraph(Nv);
        scanf("%d",&(Graph->Ne));
        if(Graph->Ne)
        {
                E=(Edge)malloc(sizeof(struct ENode));
                for(i=0;i<Graph->Ne;i++)
                {
                        scanf("%d %d %d",&E->V1,&E->V2,&E->Weight);
                        InsertEdge(Graph,E);
                }
        }
        return Graph;
}
Queue CreateQueue(int Nv)
{
        Queue New;
        New=(Queue)malloc(sizeof(struct QNode));
        New->Capacity=Nv;
        New->Front=New->Rear=0;
        New->Data=(int *)malloc(sizeof(int)*(Nv+1));
        return New;
}
bool AddQ(Queue Q,int X)
{
        Q->Rear=(Q->Rear+1)%Q->Capacity;
        Q->Data[Q->Rear]=X;
        return true;
}
int DeleteQ(Queue Q)
{
        Q->Front=(Q->Front+1)%Q->Capacity;
        return Q->Data[Q->Front];
}
bool IsEmpty(Queue Q)
{
        return (Q->Front==Q->Rear);
}
bool TopSort(LGraph Graph,Vertex TopOrder[],int time[])
{
        int Indegree[MaxVertexNum],cnt;
        for(int i=0;i<Graph->Nv;i++)
                time[i]=0;
        Vertex V;
        PtrToAdjVNode W;
        Queue Q=CreateQueue(Graph->Nv);
        for(V=0;V<Graph->Nv;V++)
                Indegree[V]=0;
        for(V=0;V<Graph->Nv;V++)
                for(W=Graph->G[V].FirstEdge;W;W=W->Next)
                        Indegree[W->Adj]++;
        for(V=0;V<Graph->Nv;V++)
                if(Indegree[V]==0)
                        AddQ(Q,V);
        cnt=0;
        while(!IsEmpty(Q))
        {
                V=DeleteQ(Q);
                TopOrder[cnt++]=V;
                for(W=Graph->G[V].FirstEdge;W;W=W->Next)
                {
                        if(time[W->Adj]<time[V]+W->Weight)
                                time[W->Adj]=time[V]+W->Weight;
                        if(--Indegree[W->Adj]==0)
                                AddQ(Q,W->Adj);
                }
        }
        free(Q);
        if(cnt!=Graph->Nv)
                return false;
        else
                return true;
}

void ReverseTopSort(LGraph Graph,Vertex ReTopOrder[],int time[],int early[],int last)
{
        int Outdegree[MaxVertexNum];
        for(int i=0;i<Graph->Nv;i++)
                Outdegree[i]=0;
        PtrToAdjVNode W;
        Vertex V;
        for(int i=0;i<Graph->Nv;i++)
                time[i]=INFINITY;
        for(V=0;V<Graph->Nv;V++)
                for(W=Graph->G[V].FirstEdge;W;W=W->Next)
                        Outdegree[V]++;
        Queue Q=CreateQueue(Graph->Nv);
        for(V=0;V<Graph->Nv;V++)
        {
                if(Outdegree[V]==0)
                {
                        time[V]=early[last];
                        AddQ(Q,V);
                }
        }
        while(!IsEmpty(Q))
        {
                V=DeleteQ(Q);
                for(W=Graph->W[V].FirstEdge;W;W=W->Next)
                {
                        if(time[W->Adj]>=time[V]-W->Weight)
                        {
                                time[W->Adj]=time[V]-(W->Weight);
                                D[W->Adj][V]=time[V]-(W->Weight)-early[W->Adj];
                        }
                        if(--Outdegree[W->Adj]==0)
                                AddQ(Q,W->Adj);
                }
        }
}
void Display(int VertexNum)
{
        int i;
        for(i=0;i<VertexNum;i++)
        {
                for(int j=VertexNum-1;j>=0;j--)
                        if(D[i][j]==0)
                                printf("%d->%d\n",i+1,j+1);
        }
}
void Print(LGraph Graph)
{
        PtrToAdjVNode Tem;
        for(int i=0;i<Graph->Nv;i++)
        {
                printf("%d :",i);
                Tem=Graph->W[i].FirstEdge;
                while(Tem)
                {
                        printf(" %d",Tem->Adj);
                        Tem=Tem->Next;
                }
                putchar('\n');
        }
}
