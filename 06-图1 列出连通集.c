#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
typedef int Vertex;
typedef int WeightType;
typedef struct ENode *PtrToENode;
struct ENode
{
        Vertex V1,V2;
};
typedef PtrToENode Edge;
typedef struct GNode *PtrToGNode;
struct GNode
{
        int Nv;
        int Ne;
        WeightType *G;
};
typedef PtrToGNode MGraph;
MGraph CreateGraph(int VertexNum);
void InsertEdge(Edge E,MGraph Graph);
MGraph BuildGraph(void);
bool IsEdge(MGraph,Vertex,Vertex);
void DFS(MGraph,Vertex V);
void BFS(MGraph Graph,Vertex V);
void Reset(MGraph Graph);
void ListComponents(MGraph Graph);
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
bool *Visit;
int main(void)
{
        MGraph Graph;
        Graph=BuildGraph();
        Visit=(bool *)malloc(sizeof(bool)*Graph->Nv);
        int GNum=(Graph->Nv)*(Graph->Nv-1)/2;
        ListComponents(Graph);
        return 0;
}
MGraph CreateEmptyGraph(int VertexNum)
{
        Vertex V,W;
        MGraph Graph;
        Graph=(MGraph)malloc(sizeof(struct GNode));
        Graph->Nv=VertexNum;
        int GNum=(Graph->Nv)*(Graph->Nv-1)/2;
        Graph->G=(WeightType *)malloc(sizeof(int)*GNum);
        for(int i=0;i<GNum;i++)
        {
                Graph->G[i]=0;
        }
        return Graph;
}
void InsertEdge(Edge E,MGraph Graph)
{
        if(E->V1<E->V2)
        {
                E->V1+=E->V2;
                E->V2=E->V1-E->V2;
                E->V1-=E->V2;
        }
        int Index=(E->V1)*(E->V1-1)/2+E->V2;
        Graph->G[Index]=1;
}
MGraph BuildGraph(void)
{
        MGraph Graph;
        Edge E;
        int Nv,Ne;
        scanf("%d",&Nv);
        Graph=CreateEmptyGraph(Nv);
        scanf("%d",&Graph->Ne);
        if(Graph->Ne)
        {
                E=(Edge)malloc(sizeof(struct ENode));
                for(int i=0;i<Graph->Ne;i++)
                {
                        scanf("%d %d",&E->V1,&E->V2);
                        InsertEdge(E,Graph);
                }
        }
        return Graph;
}
void DFS(MGraph Graph,Vertex V)
{
        Vertex W;
        printf("%d ",V);
        Visit[V]=true;
        for(W=0;W<Graph->Nv;W++)
        {
                if(!Visit[W]&&IsEdge(Graph,V,W))
                {
                        Visit[W]=true;
                        DFS(Graph,W);
                }
        }
}
bool IsEdge(MGraph Graph,Vertex V,Vertex W)
{
        int Index;
        if(V<W)
        {
                V+=W;
                W=V-W;
                V-=W;
        }
        Index=V*(V-1)/2+W;
        if(Graph->G[Index]==1)
                return true;
        return false;
}
void BFS(MGraph Graph,Vertex V)
{
        Vertex T,W;
        printf("%d ",V);
        Visit[V]=true;
        Queue Q=CreateQueue(Graph->Nv);
        AddQ(Q,V);
        while(!IsEmpty(Q))
        {
                T=DeleteQ(Q);
                for(W=0;W<Graph->Nv;W++)
                {
                        if(!Visit[W]&&IsEdge(Graph,T,W))
                        {
                                printf("%d ",W);
                                Visit[W]=true;
                                AddQ(Q,W);
                        }
                }
        }
}
void Reset(MGraph Graph)
{
        for(int i=0;i<Graph->Nv;i++)
                Visit[i]=false;
}
Queue CreateQueue(int Nv)
{
        Queue New;
        New=(Queue)malloc(sizeof(struct QNode));
        New->Capacity=Nv;
        New->Front=New->Rear=0;
        New->Data=(int *)malloc(sizeof(int)*Nv);
        return New;
}
void ListComponents(MGraph Graph)
{
        for(int i=0;i<Graph->Nv;i++)
        {
                if(!Visit[i])
                {
                        printf("{ ");
                        DFS(Graph,i);
                        printf("}\n");
                }
        }
        Reset(Graph);
        for(int i=0;i<Graph->Nv;i++)
        {
                if(!Visit[i])
                {
                        printf("{ ");
                        BFS(Graph,i);
                        printf("}\n");
                }
        }
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
