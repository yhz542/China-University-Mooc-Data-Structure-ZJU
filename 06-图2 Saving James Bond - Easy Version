#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
typedef struct GNode *MGraph;
typedef struct CroNode *PositionCro;
struct GNode
{
        int Nv;
        PositionCro Cro;
};
struct CroNode
{
        int X,Y;
} ;

MGraph GetCroPosition(int NumCro);
MGraph CreateEmptyGraph(int);
void Insert(struct CroNode,MGraph);
void Save007(MGraph,int);
void InitializeVisit(int);
bool FirstJump(struct CroNode,int);
bool DFS(int,MGraph,int);
bool IsSafe(struct CroNode,int);
bool Jump(struct CroNode,struct CroNode,int);
int *Visit;
int main(void)
{
        int NumCro,JumpDist;
        MGraph Graph;
        scanf("%d %d",&NumCro,&JumpDist);
        Graph=GetCroPosition(NumCro);
        Save007(Graph,JumpDist);
        return 0;
}
MGraph GetCroPosition(int NumCro)
{
        MGraph Graph;
        Graph=CreateEmptyGraph(NumCro);
        InitializeVisit(NumCro);
        struct CroNode C;
        for(int i=0;i<NumCro;i++)
        {
                scanf("%d %d",&(Graph->Cro[i].X),&(Graph->Cro[i].Y));
        }
        return Graph;
}
MGraph CreateEmptyGraph(int NumCro)
{
        MGraph New;
        New=(MGraph)malloc(sizeof(struct GNode));
        New->Nv=NumCro;
        New->Cro=(PositionCro)malloc(sizeof(struct CroNode)*NumCro);
        return New;
}
void InitializeVisit(int Num)
{
        Visit=(int *)malloc(sizeof(int)*Num);
        for(int i=0;i<Num;i++)
                Visit[i]=0;
}
void Save007(MGraph Graph,int JumpDist)
{
        bool answer=false;
        for(int i=0;i<Graph->Nv;i++)
        {
                if(!Visit[i]&&FirstJump(Graph->Cro[i],JumpDist))
                {
                        answer=DFS(i,Graph,JumpDist);
                        if(answer)
                                break;
                }
        }
        if(answer)
                puts("Yes");
        else
                puts("No");
}
bool FirstJump(struct CroNode coord,int JumpDist)
{
        int Vertical,Horizontal,Distance;
        float JumpReach;
        Vertical=coord.X*coord.X;
        Horizontal=coord.Y*coord.Y;
        Distance=Vertical+Horizontal;
        JumpReach=7.5+JumpDist;
        JumpReach*=JumpReach;
        if((float)Distance<=JumpReach)
                return true;
        else
                return false;
}
bool DFS(int Vertex,MGraph Graph,int JumpDist)
{
        bool answer=false;
        Visit[Vertex]=true;
        if(IsSafe(Graph->Cro[Vertex],JumpDist))
                answer=true;
        else
        {
                for(int i=0;i<Graph->Nv;i++)
                        if(!Visit[i]&&Jump(Graph->Cro[Vertex],Graph->Cro[i],JumpDist))
                        {
                                answer=DFS(i,Graph,JumpDist);
                                if(answer)
                                        break;
                        }
        }
        return answer;
}
bool IsSafe(struct CroNode P,int JumpDist)
{
        int D;
        if(P.X<0)
                P.X=-P.X;
        if(P.Y<0)
                P.Y=-P.Y;
        if(P.X>P.Y)
                D=P.X;
        else
                D=P.Y;
        if(50-D<=JumpDist)
                return true;
        else
                return false;
}
bool Jump(struct CroNode V1,struct CroNode V2,int JumpDist)
{
        int XDist,YDist;
        XDist=V1.X-V2.X;
        YDist=V1.Y-V2.Y;
        XDist*=XDist;
        YDist*=YDist;
        if(XDist+YDist<=JumpDist*JumpDist)
                return true;
        else
                return false;
}
