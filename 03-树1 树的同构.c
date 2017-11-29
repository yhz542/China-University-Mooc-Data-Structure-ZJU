#include<stdio.h>
#include<stdlib.h>
struct node
{
        char symbol;
        int left;
        int right;
};
typedef struct node *tree;
int input(tree,int);
int contrast(tree,tree,int,int);
int main(void)
{
        tree first,second;
        int num_f,num_s,root_f,root_s;
        scanf("%d",&num_f);
        getchar();
        first=(tree)malloc(num_f*sizeof(struct node));
        root_f=input(first,num_f);
        scanf("%d",&num_s);
        getchar();
        second=(tree)malloc(num_s*sizeof(struct node));
        root_s=input(second,num_s);
        printf("%s",contrast(first,second,root_f,root_s)==1?"Yes":"No");
        free(first);
        free(second);
        return 0;
}
int input(tree one,int num)
{
        int check[num];
        int root=-1;
        char left,right;
        for(int i=0;i<num;i++)
                check[i]=0;
        for(int i=0;i<num;i++)
        {
                scanf("%c %c %c",&(one[i].symbol),&left,&right);
                getchar();
                if('-'!=left)
                {
                        one[i].left=left-'0';
                        check[one[i].left]=1;
                }
                else
                        one[i].left=-1;
                if('-'!=right)
                {
                        one[i].right=right-'0';
                        check[one[i].right]=1;
                }
                else
                        one[i].right=-1;
        }
        for(int i=0;i<num;i++)
        for(int i=0;i<num;i++)
        {
                if(!check[i])
                        root=i;
        }
        return root;
}
int contrast(tree first,tree second,int root_f,int root_s)
{
        if((-1==root_f)&&(-1==root_s))
                return 1;
        else if((-1!=root_f)&&(-1==root_s)||(-1!=root_s)&&(-1==root_f))
                return 0;
        else if(first[root_f].symbol!=second[root_s].symbol)
                return 0;
        else if((first[root_f].left==-1)&&(-1==second[root_s].left))
                return contrast(first,second,first[root_f].right,second[root_s].right);
        else if((first[root_f].left!=-1)&&(-1!=second[root_s].left)&&(first[first[root_f].left].symbol==second[second[root_s].left].symbol))
                return contrast(first,second,first[root_f].left,second[root_s].left)&&contrast(first,second,first[root_f].right,second[root_s].right);
        else
                return contrast(first,second,first[root_f].left,second[root_s].right)&&contrast(first,second,first[root_f].right,second[root_s].left);
}
