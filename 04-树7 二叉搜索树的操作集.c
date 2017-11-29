BinTree Insert( BinTree BST, ElementType X )
{
        if(!BST)
        {
                BST=(BinTree)malloc(sizeof(struct TNode));
                BST->Data=X;
                BST->Left=BST->Right=NULL;
        }
        else
        {
                if(X<BST->Data)
                        BST->Left=Insert(BST->Left,X);
                else
                        BST->Right=Insert(BST->Right,X);
        }
        return BST;
}
BinTree Delete( BinTree BST, ElementType X )
{
        Position Temp;
        if(!BST)
                printf("Not Found\n");
        else
        {
                if(X<BST->Data)
                        BST->Left=Delete(BST->Left,X);
                else if(X>BST->Data)
                        BST->Right=Delete(BST->Right,X);
                else
                {
                        if(BST->Left&&BST->Right)
                        {
                                Temp=FindMin(BST->Right);
                                BST->Data=Temp->Data;
                                BST->Right=Delete(BST->Right,BST->Data);
                        }
                        else
                        {
                                Temp=BST;
                                if(!BST->Right)
                                        BST=BST->Left;
                                else
                                        BST=BST->Right;
                                free(Temp);
                        }
                }
        }
        return BST;
}
Position Find( BinTree BST, ElementType X )
{
        while(1)
        {
                if(!BST)
                        return NULL;
                else if(X>BST->Data)
                        BST=BST->Right;
                else if(X<BST->Data)
                        BST=BST->Left;
                else if(X==BST->Data)
                        return BST;
        }
}
Position FindMin( BinTree BST )
{
        if(!BST)
                return NULL;
        while(1)
        {
                if(BST->Left)
                        BST=BST->Left;
                else
                        return BST;
        }
}
Position FindMax( BinTree BST )
{
        if(!BST)
                return NULL;
        while(1)
        {
                if(BST->Right)
                        BST=BST->Right;
                else
                        return BST;
        }
}
