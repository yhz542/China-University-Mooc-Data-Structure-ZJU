#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#define MaxVertexNum 100
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
};
typedef PtrToGNode LGraph;
LGraph CreateGraph(int);
void InsertEdge(LGraph,Edge);
LGraph BuildGraph(void);
bool TopSort(LGraph,Vertex [],int []);
void Print(LGraph);
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

int main(void)
{
        LGraph Graph;
        Graph=BuildGraph();
        //Print(Graph);
        int *time;
        time=(int *)malloc(sizeof(int)*Graph->Nv);
        Vertex TopOrder[MaxVertexNum];
        if(TopSort(Graph,TopOrder,time))
        {
                int Max=time[0];
                for(int i=1;i<Graph->Nv;i++)
                {
                        if(Max<time[i])
                                Max=time[i];
                }
                printf("%d",Max);
        }
        else
                printf("Impossible");
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
        for(V=0;V<VertexNum;V++)
                Graph->G[V].FirstEdge=NULL;
        return Graph;
}
void InsertEdge(LGraph Graph,Edge E)
{
        PtrToAdjVNode NewNode;
        NewNode=(PtrToAdjVNode)malloc(sizeof(struct AdjVNode));
        NewNode->Adj=E->V2;
        NewNode->Weight=E->Weight;
        NewNode->Next=Graph->G[E->V1].FirstEdge;
        Graph->G[E->V1].FirstEdge=NewNode;
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
        if(cnt!=Graph->Nv)
                return false;
        else
                return true;
}
void Print(LGraph Graph)
{
        PtrToAdjVNode Tem;
        for(int i=0;i<Graph->Nv;i++)
        {
                Tem=Graph->G[i].FirstEdge;
                printf("%d :",i);
                while(Tem)
                {
                        printf("%d ",Tem->Adj);
                        Tem=Tem->Next;
                }
                putchar('\n');
        }
}
