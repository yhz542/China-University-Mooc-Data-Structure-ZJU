#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#define MaxVertexNum 1000
#define INIFINITY 65535
typedef int Vertex;
typedef Vertex SetName;
typedef Vertex ElementType;
typedef ElementType SetType[MaxVertexNum];
typedef struct ENode *Edge;
struct ENode
{
        Vertex V1,V2;
        int Cost;
};
typedef struct GNode *MGraph;
struct GNode
{
        int Nv;
        int Ne;
        int **Cost;
};
typedef struct AdjVNode *PtrToAdjVNode;
struct AdjVNode
{
        Vertex AdjV;
        int Cost;
        PtrToAdjVNode Next;
};
typedef struct VNode
{
        PtrToAdjVNode FirstEdge;
}*AdjList;
typedef struct LGNode *LGraph;
struct LGNode
{
        int Nv;
        int Ne;
        AdjList G;
};
MGraph CreateGraph(int);
void InsertEdge(MGraph,Edge);
void InsertLEdge(LGraph,Edge);
MGraph BuildGraph(void);
LGraph CreateLGraph(int);
Vertex FindMinDist(MGraph Graph,int cost[]);
int Prim(MGraph Graph,LGraph MSt);
void Print(MGraph Graph);
int main(void)
{
        MGraph Graph=BuildGraph();
        LGraph MST;
        int TotalCost;
        TotalCost=Prim(Graph,MST);
        printf("%d",TotalCost);
        return 0;
}
MGraph CreateGraph(int VertexNum)
{
        MGraph Graph;
        Graph=(MGraph)malloc(sizeof(struct GNode));
        Graph->Nv=VertexNum;
        Graph->Ne=0;
        Graph->Cost=(int **)malloc(sizeof(int *)*VertexNum);
        for(int i=0;i<VertexNum;i++)
        {
                Graph->Cost[i]=(int *)malloc(sizeof(int)*VertexNum);
        }
        for(int i=0;i<VertexNum;i++)
                for(int j=0;j<VertexNum;j++)
                        Graph->Cost[i][j]=INIFINITY;
        return Graph;
}
void InsertEdge(MGraph Graph,Edge E)
{
        Graph->Cost[--E->V1][--E->V2]=E->Cost;
        Graph->Cost[E->V2][E->V1]=E->Cost;
}
MGraph BuildGraph(void)
{
        MGraph Graph;
        Edge E;
        int Nv;
        scanf("%d",&Nv);
        Graph=CreateGraph(Nv);
        scanf("%d",&(Graph->Ne));
        if(Graph->Ne)
        {
                E=(Edge)malloc(sizeof(struct ENode));
                for(int i=0;i<Graph->Ne;i++)
                {
                        scanf("%d %d %d",&(E->V1),&(E->V2),&(E->Cost));
                        InsertEdge(Graph,E);
                }
        }
        return Graph;
}
LGraph CreateLGraph(int VertexNum)
{
        Vertex V;
        LGraph Graph;
        Graph=(LGraph)malloc(sizeof(struct LGNode));
        Graph->Nv=VertexNum;
        Graph->Ne=0;
        Graph->G=(AdjList)malloc(sizeof(struct VNode)*VertexNum);
        for(V=0;V<VertexNum;V++)
                Graph->G[V].FirstEdge=NULL;
        return Graph;
}
Vertex FindMinDist(MGraph Graph,int cost[])
{
        Vertex MinV,V;
        int MinDist=INIFINITY;
        for(V=0;V<Graph->Nv;V++)
        {
                if(cost[V]&&cost[V]<MinDist)
                {
                        MinDist=cost[V];
                        MinV=V;
                }
        }
        if(MinDist<INIFINITY)
                return MinV;
        else
                return -1;
}
int Prim(MGraph Graph,LGraph MST)
{
        int cost[MaxVertexNum],TotalCost;
        Vertex parent[MaxVertexNum],V,W;
        int VCount;
        Edge E;
        for(V=0;V<Graph->Nv;V++)
        {
                cost[V]=Graph->Cost[0][V];
                parent[V]=0;
        }
        TotalCost=0;
        VCount=0;
        MST=CreateLGraph(Graph->Nv);
        E=(Edge)malloc(sizeof(struct ENode));
        cost[0]=0;
        VCount++;
        parent[0]=-1;
        while(1)
        {
                V=FindMinDist(Graph,cost);
                if(V==-1)
                        break;
                E->V1=parent[V];
                E->V2=V;
                E->Cost=cost[V];
                InsertLEdge(MST,E);
                TotalCost+=cost[V];
                cost[V]=0;
                VCount++;
                for(W=0;W<Graph->Nv;W++)
                        if(cost[W]&&Graph->Cost[V][W]<INIFINITY)
                        {
                                if(Graph->Cost[V][W]<cost[W])
                                {
                                        cost[W]=Graph->Cost[V][W];
                                        parent[W]=V;
                                }
                        }
        }
        if(VCount<Graph->Nv)
                TotalCost=-1;
        return TotalCost;
}
void InsertLEdge(LGraph Graph,Edge E)
{
        PtrToAdjVNode NewNode;
        NewNode=(PtrToAdjVNode)malloc(sizeof(struct AdjVNode));
        NewNode->AdjV=E->V2;
        NewNode->Cost=E->Cost;
        NewNode->Next=Graph->G[E->V1].FirstEdge;
        Graph->G[E->V1].FirstEdge=NewNode;
        NewNode=(PtrToAdjVNode)malloc(sizeof(struct AdjVNode));
        NewNode->AdjV=E->V1;
        NewNode->Cost=E->Cost;
        NewNode->Next=Graph->G[E->V2].FirstEdge;
        Graph->G[E->V2].FirstEdge=NewNode;
}
void Print(MGraph Graph)
{
        for(int i=0;i<Graph->Nv;i++)
        {

                for(int j=0;j<Graph->Nv;j++)
                        printf("%d ",Graph->Cost[i][j]);
                putchar('\n');
        }
}
