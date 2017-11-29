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
        Vertex AdjV;
        PtrToAdjVNode Next;
};

typedef struct VNode *AdjList;
struct VNode
{
        PtrToAdjVNode FirstEdge;
};

typedef struct GNode *PtrToGNode;
struct GNode
{
        int Nv;
        int Ne;
        AdjList G;
};
typedef PtrToGNode LGraph;

LGraph CreateEmptyGraph(int VertexNum);
void InsertEdge(LGraph Graph,Edge E);
LGraph BuildGraph(void);
void SDS(LGraph);


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
int BFS(int V,LGraph Graph,Queue Q);
void InitializeVisit(int);
void Reset(int);
bool *Visit;
int main(void)
{
        LGraph Graph;
        Graph=BuildGraph();
        SDS(Graph);
        return 0;
}
LGraph CreateEmptyGraph(int VertexNum)
{
        Vertex V;
        LGraph Graph;
        Graph=(LGraph)malloc(sizeof(struct GNode));
        Graph->Nv=VertexNum;
        Graph->Ne=0;
        Graph->G=(AdjList)malloc(sizeof(struct VNode)*(VertexNum+1));
        for(V=0;V<=VertexNum;V++)
                Graph->G[V].FirstEdge=NULL;
        return Graph;
}
void InsertEdge(LGraph Graph,Edge E)
{
        PtrToAdjVNode NewNode;
        NewNode=(PtrToAdjVNode)malloc(sizeof(struct AdjVNode));
        NewNode->AdjV=E->V2;
        NewNode->Next=Graph->G[E->V1].FirstEdge;
        Graph->G[E->V1].FirstEdge=NewNode;

        NewNode=(PtrToAdjVNode)malloc(sizeof(struct AdjVNode));
        NewNode->AdjV=E->V1;
        NewNode->Next=Graph->G[E->V2].FirstEdge;
        Graph->G[E->V2].FirstEdge=NewNode;
}
LGraph BuildGraph(void)
{
        LGraph Graph;
        Edge E;
        Vertex V;
        int Nv;
        scanf("%d",&Nv);
        Graph=CreateEmptyGraph(Nv);
        InitializeVisit(Nv);
        scanf("%d",&Graph->Ne);
        if(Graph->Ne)
        {
                E=(Edge)malloc(sizeof(struct ENode));
                for(int i=0;i<Graph->Ne;i++)
                {
                        scanf("%d %d",&E->V1,&E->V2);
                        InsertEdge(Graph,E);
                }
        }
        return Graph;
}
void InitializeVisit(int N)
{
        Visit=(bool *)malloc(sizeof(bool)*(N+1));
        for(int i=1;i<=N;i++)
        {
                Visit[i]=false;
        }
        Visit[0]=true;
}
void SDS(LGraph Graph)
{
        float Count;
        Queue Q=CreateQueue(Graph->Nv);
        for(int i=1;i<=Graph->Nv;i++)
        {
                Count=(float)BFS(i,Graph,Q);
                printf("%d: %.2f%%\n",i,Count/Graph->Nv*100);
                Reset(Graph->Nv);
        }
}
int BFS(int V,LGraph Graph,Queue Q)
{
        int Count,level=0,last=V,tail;
        PtrToAdjVNode Tem;
        Visit[V]=true;
        Count=1;
        AddQ(Q,V);
        while(!IsEmpty(Q))
        {
                V=DeleteQ(Q);
                Tem=Graph->G[V].FirstEdge;
                while(Tem)
                {
                        if(!Visit[Tem->AdjV])
                        {
                                Visit[Tem->AdjV]=true;
                                AddQ(Q,Tem->AdjV);
                                Count++;
                                tail=Tem->AdjV;
                        }
                        Tem=Tem->Next;
                }
                if(V==last)
                {
                        level++;
                        last=tail;
                }
                if(level==6)
                        break;
        }
        Q->Front=Q->Rear=0;
        return Count;
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
void Reset(int N)
{
        for(int i=1;i<=N;i++)
                Visit[i]=false;
}
