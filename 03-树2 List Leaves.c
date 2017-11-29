#include<stdio.h>
#include<stdlib.h>
struct node;
typedef struct node *tree;
struct node
{
        int left;
        int right;
};
int create(tree *,int);
int *rearrange(tree,int,int);
void print_leaves(tree,int *,int);
int main(void)
{
        tree T;
        int num;//有多少个节点 分支
        int root;
        int *target;
        scanf("%d",&num);
        root=create(&T,num);
        target=rearrange(T,num,root);
        print_leaves(T,target,num);
        return 0;
}
int create(tree *one,int num)
{
        getchar();
        char l,r;
        int check[num];
        for(int i=0;i<num;i++)
        {
                check[i]=0;
        }
        int root=-1;
        *one=(tree)malloc(num*sizeof(struct node));
        for(int i=0;i<num;i++)
        {
                scanf("%c %c",&l,&r);
                getchar();
                if('-'==l)
                        (*one)[i].left=-1;
                else
                {
                        (*one)[i].left=l-'0';
                        check[(*one)[i].left]=1;
                }
                if('-'==r)
                        (*one)[i].right=-1;
                else
                {
                        (*one)[i].right=r-'0';
                        check[(*one)[i].right]=1;
                }
        }
        for(int i=0;i<num;i++)
        {
                if(!check[i])
                {
                        root=i;
                        break;
                }
        }
        return root;
}
int *rearrange(tree source,int num,int root)
{
        int i=1,k=0;
        int *target=(int *)malloc(sizeof(int)*num);
        target[0]=root;
        while(i<num)
        {
                if(source[target[k]].left!=-1)
                {
                        target[i]=source[target[k]].left;
                        i++;
                }
                if(source[target[k]].right!=-1)
                {
                        target[i]=source[target[k]].right;
                        i++;
                }
                k++;
        }
        return target;
}
void print_leaves(tree one,int *target,int num)
{
        int i;
        for(i=0;i<num;i++)
        {
                if(one[target[i]].left==-1&&one[target[i]].right==-1)
                {
                    printf("%d",target[i]);
                    break;
                }
        }
        for(++i;i<num;i++)
        {
                if(one[target[i]].left==-1&&one[target[i]].right==-1)
                {
                    printf(" %d",target[i]);
                }
        }
}
