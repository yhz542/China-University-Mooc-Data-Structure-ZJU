#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#define Infinity 65535
typedef int Vertex;
typedef struct AdjVNode *PtrToAdjVNode;
struct AdjVNode
{
        int Index;
        PtrToAdjVNode Next;
};
typedef struct VNode
{
        PtrToAdjVNode FirstEdge;
        int X,Y;
}*AdjList;
typedef struct GNode *LGraph;
struct GNode
{
        int Nv;
        AdjList G;
};
bool FirstJump(int,int,int);
bool IsLinked(LGraph,int,int,int);
LGraph CreateGraph(int VertexNum);
void InsertEdge(LGraph Graph,int,int);
LGraph BuildGraph(int,int);
void ConnectEdge(LGraph,int);
void Unweighted(LGraph,int dist[],int path[],Vertex S);
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
bool IsSafe(LGraph,int,int);
void Rearrange(LGraph);
int BackToFirst(LGraph,int [],int);
void Display(LGraph,int [],int );

int main(void)
{
        int Nv,JumpDist,flag=0;
        scanf("%d %d",&Nv,&JumpDist);
        LGraph Graph=BuildGraph(Nv,JumpDist);
        if(Graph->G[0].FirstEdge==NULL)
        {
                printf("0");
                return 0;
        }
        Rearrange(Graph);
        //Print(Graph);
        int dist[Graph->Nv+1],path[Graph->Nv+1];
        int distance=Infinity,result;
        for(int i=0;i<=Graph->Nv;i++)
        {
                dist[i]=-1;
        }
        Unweighted(Graph,dist,path,0);
        /*for(int i=0;i<=Graph->Nv;i++)
        {
                printf("dist[%d]=%d,path[%d]=%d\n",i,dist[i],i,path[i]);
        }*/
        for(int i=0,sum=Infinity,tem;i<=Graph->Nv;i++)
        {
                if(IsSafe(Graph,i,JumpDist)&&dist[i]<=distance&&dist[i]>=0)
                {
                        flag=1;
                        tem=BackToFirst(Graph,path,i);
                        if(dist[i]<distance||tem<sum)
                        {
                                sum=tem;
                                distance=dist[i];
                                result=i;
                        }
                }
        }
        if(!flag)
        {
                printf("0");
                return 0;
        }
        printf("%d\n",distance+1);
        if(result)
                Display(Graph,path,result);
        return 0;
}


LGraph CreateGraph(int VertexNum)
{
        int V;
        LGraph Graph;
        Graph=(LGraph)malloc(sizeof(struct GNode));
        Graph->Nv=VertexNum;
        Graph->G=(AdjList)malloc(sizeof(struct VNode)*(VertexNum+1));
        for(V=0;V<=Graph->Nv;V++)
                Graph->G[V].FirstEdge=NULL;
        Graph->G[0].X=Graph->G[0].Y=0;
        return Graph;
}
void InsertEdge(LGraph Graph,int V1,int V2)
{
        PtrToAdjVNode NewNode;
        NewNode=(PtrToAdjVNode)malloc(sizeof(struct AdjVNode));
        NewNode->Index=V2;
        NewNode->Next=Graph->G[V1].FirstEdge;
        Graph->G[V1].FirstEdge=NewNode;
        NewNode=(PtrToAdjVNode)malloc(sizeof(struct AdjVNode));
        NewNode->Index=V1;
        NewNode->Next=Graph->G[V2].FirstEdge;
        Graph->G[V2].FirstEdge=NewNode;
}
LGraph BuildGraph(int Nv,int JumpDist)
{
        LGraph Graph;
        Vertex V;
        Graph=CreateGraph(Nv);
        for(int i=1;i<=Nv;i++)
        {
                scanf("%d %d",&(Graph->G[i].X),&(Graph->G[i].Y));
        }
        ConnectEdge(Graph,JumpDist);
        return Graph;
}
bool FirstJump(int JumpDist,int X,int Y)
{
        float JumpReach;
        X*=X;
        Y*=Y;
        JumpReach=7.5+(float)JumpDist;
        if((float)(X+Y)<=JumpReach*JumpReach)
                return true;
        else
                return false;
}
bool IsLinked(LGraph Graph,int V1,int V2,int JumpDist)
{
        int X1,X2,Y1,Y2,X,Y;
        X1=Graph->G[V1].X;
        Y1=Graph->G[V1].Y;
        X2=Graph->G[V2].X;
        Y2=Graph->G[V2].Y;
        X=X2-X1;
        Y=Y2-Y1;
        X*=X;
        Y*=Y;
        if(X+Y<=JumpDist*JumpDist)
                return true;
        else
                return false;
}
void ConnectEdge(LGraph Graph,int JumpDist)
{
        for(int i=1;i<=Graph->Nv;i++)
                if(FirstJump(JumpDist,Graph->G[i].X,Graph->G[i].Y))
                        InsertEdge(Graph,0,i);
        for(int i=1;i<=Graph->Nv;i++)
                for(int j=i+1;j<=Graph->Nv;j++)
                        if(IsLinked(Graph,i,j,JumpDist))
                                InsertEdge(Graph,i,j);
}
void Print(LGraph Graph)
{
        PtrToAdjVNode Tem;
        for(int i=0;i<=Graph->Nv;i++)
        {
                printf("%2d X=%4d Y=%4d linkpoint: ",i,Graph->G[i].X,Graph->G[i].Y);
                Tem=Graph->G[i].FirstEdge;
                while(Tem)
                {
                        printf("%2d ",Tem->Index);
                        Tem=Tem->Next;
                }
                putchar('\n');
        }
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
void Unweighted(LGraph Graph,int dist[],int path[],Vertex S)
{
        Queue Q;
        Vertex V;
        PtrToAdjVNode W;
        Q=CreateQueue(Graph->Nv);
        dist[S]=0;
        path[S]=0;
        AddQ(Q,S);
        while(!IsEmpty(Q))
        {
                V=DeleteQ(Q);
                for(W=Graph->G[V].FirstEdge;W;W=W->Next)
                {
                        if(dist[W->Index]==-1)
                        {
                                dist[W->Index]=dist[V]+1;
                                path[W->Index]=V;
                                AddQ(Q,W->Index);
                        }
                }
        }
}
bool IsSafe(LGraph Graph,int i,int JumpDist)
{
        if(i==0)
                JumpDist+=7.5;
        int X=Graph->G[i].X;
        int Y=Graph->G[i].Y;
        int D;
        if(X<0)
                X=-X;
        if(Y<0)
                Y=-Y;
        if(X>Y)
                D=X;
        else
                D=Y;
        if(50-D<=JumpDist)
                return true;
        else
                return false;
}
void Rearrange(LGraph Graph)
{
        int x,y,flag,cnt=0,s;
        PtrToAdjVNode Tem,Head,Object;
        Tem=Graph->G[0].FirstEdge;
        while(Tem)
        {
                cnt++;
                Tem=Tem->Next;
        }
        Head=Graph->G[0].FirstEdge;
        Tem=Head->Next;
        while(--cnt>0)
        {
                flag=0;
                x=Graph->G[Head->Index].X;
                y=Graph->G[Head->Index].Y;
                s=Head->Index;
                while(Tem)
                {
                        if(x*x+y*y>Graph->G[Tem->Index].X*Graph->G[Tem->Index].X+Graph->G[Tem->Index].Y*Graph->G[Tem->Index].Y)
                        {
                                flag=1;
                                x=Graph->G[Tem->Index].X;
                                y=Graph->G[Tem->Index].Y;
                                Object=Tem;
                        }
                        Tem=Tem->Next;
                }
                if(flag)
                {
                        Head->Index=Object->Index;
                        Object->Index=s;
                }
                Head=Head->Next;
                Tem=Head->Next;
        }
}
int BackToFirst(LGraph Graph,int path[],int i)
{
        int tem=path[i],x,y;
        int sum;
        while(path[tem]!=0)
        {
                tem=path[tem];
        }
        x=Graph->G[tem].X;
        y=Graph->G[tem].Y;
        sum=x*x+y*y;
        return sum;
}
void Display(LGraph Graph,int path[],int result)
{
        if(path[result])
                Display(Graph,path,path[result]);
        printf("%d %d\n",Graph->G[result].X,Graph->G[result].Y);
}
