#include<stdio.h>
#include<stdlib.h>
typedef struct treenode *tree;
struct treenode
{
        int data;
        tree left;
        tree right;
        int height;
};
int max(int,int);
int getheight(tree);
tree doubleleft(tree target);
tree doubleright(tree target);
tree leftright(tree target);
tree rightleft(tree target);
tree insert(tree one,int data);
int main(void)
{
        int length,tem;
        int *array;
        tree head=NULL;
        scanf("%d",&length);
        for(int i=0;i<length;i++)
        {
                scanf("%d",&tem);
                head=insert(head,tem);
        }
        printf("%d",head->data);
        return 0;
}
int max(int a,int b)
{
        return a>b?a:b;
}
int getheight(tree one)
{
        int height;
        if(!one)
                height=-1;
        else
        {
                height=max(getheight(one->left),getheight(one->right))+1;
        }
        return height;
}
tree doubleleft(tree target)
{
        tree newhead=target->left;
        target->left=newhead->right;
        newhead->right=target;
        newhead->height=getheight(newhead);
        target->height=getheight(target);
        return newhead;
}
tree doubleright(tree target)
{
        tree newhead=target->right;
        target->right=newhead->left;
        newhead->left=target;
        newhead->height=getheight(newhead);
        target->height=getheight(target);
        return newhead;
}
tree leftright(tree target)
{
        target->left=doubleright(target->left);
        return doubleleft(target);
}
tree rightleft(tree target)
{
        target->right=doubleleft(target->right);
        return doubleright(target);
}
tree insert(tree one,int data)
{
        if(!one)
        {
                one=(tree)malloc(sizeof(struct treenode));
                one->data=data;
                one->height=0;
                one->left=one->right=NULL;
        }
        else if(data<one->data)
        {
                one->left=insert(one->left,data);
                if(getheight(one->left)-getheight(one->right)>1)
                        if(data<one->left->data)
                                one=doubleleft(one);
                        else
                                one=leftright(one);
        }
        else if(data>one->data)//右子树
        {
                one->right=insert(one->right,data);
                if(getheight(one->right)-getheight(one->left)>1)
                        if(data>one->right->data)
                                one=doubleright(one);
                        else
                                one=rightleft(one);
        }
        one->height=getheight(one);
        return one;
}
