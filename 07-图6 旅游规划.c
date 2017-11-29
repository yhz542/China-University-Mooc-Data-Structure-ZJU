#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#define INFINITY 65535
typedef int Vertex;
typedef struct ENode *PtrToENode;
struct ENode
{
        Vertex V1,V2;
        int Length;
        int Cost;
};
typedef PtrToENode Edge;
typedef struct GNode *MGraph;
struct GNode
{
        int Nv;
        int Ne;
        int **Length;
        int **Cost;
} ;
MGraph CreateGraph(int VertexNum);
void InsertEdge(MGraph Graph,Edge E);
MGraph BuildGraph(void);
int Start,Destination;
Vertex FindMinDist(MGraph Graph,int dist[],bool collected[]);
bool Dijkstra(MGraph Graph,int dist[],int path[],int cost[],Vertex S);
void Print(MGraph Graph);
int main(void)
{
        MGraph Graph=BuildGraph();
        //Print(Graph);
        int *path,*dist,*cost;
        path=(int *)malloc(sizeof(int)*Graph->Nv);
        dist=(int *)malloc(sizeof(int)*Graph->Nv);
        cost=(int *)malloc(sizeof(int)*Graph->Nv);
        Dijkstra(Graph,dist,path,cost,Start);
        printf("%d %d",dist[Destination],cost[Destination]);
}
MGraph CreateGraph(int VertexNum)
{
        Vertex V,W;
        MGraph Graph;
        Graph=(MGraph)malloc(sizeof(struct GNode));
        Graph->Nv=VertexNum;
        Graph->Ne=0;
        Graph->Length=(int **)malloc(sizeof(int *)*VertexNum);
        for(int i=0;i<VertexNum;i++)
        {
                Graph->Length[i]=(int *)malloc(sizeof(int)*VertexNum);
        }
        Graph->Cost=(int **)malloc(sizeof(int *)*VertexNum);
        for(int i=0;i<VertexNum;i++)
        {
                Graph->Cost[i]=(int *)malloc(sizeof(int)*VertexNum);
        }
        for(V=0;V<Graph->Nv;V++)
                for(W=0;W<Graph->Nv;W++)
                {
                        Graph->Length[V][W]=INFINITY;
                        Graph->Cost[V][W]=INFINITY;
                }
        return Graph;
}
void InsertEdge(MGraph Graph,Edge E)
{
        Graph->Length[E->V1][E->V2]=E->Length;
        Graph->Length[E->V2][E->V1]=E->Length;
        Graph->Cost[E->V1][E->V2]=E->Cost;
        Graph->Cost[E->V2][E->V1]=E->Cost;
}
MGraph BuildGraph(void)
{
        MGraph Graph;
        Edge E;
        Vertex V;
        int Nv,i;
        scanf("%d",&Nv);
        Graph=CreateGraph(Nv);
        scanf("%d",&(Graph->Ne));
        scanf("%d %d",&Start,&Destination);
        if(Graph->Ne)
        {
                E=(Edge)malloc(sizeof(struct ENode));
                for(int i=0;i<Graph->Ne;i++)
                {
                        scanf("%d %d %d %d",&E->V1,&E->V2,&E->Length,&E->Cost);
                        InsertEdge(Graph,E);
                }
        }
        return Graph;
}
Vertex FindMinDist(MGraph Graph,int dist[],bool collected[])
{
        Vertex MinV,V;
        int MinDist=INFINITY;
        for(V=0;V<Graph->Nv;V++)
        {
                if(collected[V]==false&&dist[V]<MinDist)
                {
                        MinDist=dist[V];
                        MinV=V;
                }
        }
        if(MinDist<INFINITY)
                return MinV;
        else
                return -1;
}
bool Dijkstra(MGraph Graph,int dist[],int path[],int cost[],Vertex S)
{
        bool *collected=(bool *)malloc(sizeof(bool)*Graph->Nv);
        Vertex V,W;
        for(V=0;V<Graph->Nv;V++)
        {
                cost[V]=Graph->Cost[S][V];
                dist[V]=Graph->Length[S][V];
                if(dist[V]<INFINITY)
                        path[V]=S;
                else
                        path[V]=-1;
                collected[V]=false;
        }
        dist[S]=0;
        collected[S]=true;
        cost[S]=0;
        while(1)
        {
                V=FindMinDist(Graph,dist,collected);
                if(V==-1)
                        break;
                collected[V]=true;
                for(W=0;W<Graph->Nv;W++)
                        if(collected[W]==false&&Graph->Length[V][W]<INFINITY)
                        {
                                if(Graph->Length[V][W]<0)
                                        return false;
                                if(dist[V]+Graph->Length[V][W]<dist[W]||(dist[V]+Graph->Length[V][W]==dist[W]&&cost[W]>cost[V]+Graph->Cost[V][W]))
                                {
                                        dist[W]=dist[V]+Graph->Length[V][W];
                                        path[W]=V;
                                        cost[W]=cost[V]+Graph->Cost[V][W];
                                }
                        }
        }
        return true;
}
void Print(MGraph Graph)
{
        for(int i=0;i<Graph->Nv;i++)
        {
                for(int j=0;j<Graph->Nv;j++)
                {
                        printf("length=%5d ",Graph->Length[i][j]);
                        printf("cost=%5d ",Graph->Cost[i][j]);
                }
                putchar('\n');
        }
}
