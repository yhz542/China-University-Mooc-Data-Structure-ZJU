List Merge( List L1, List L2 )
{
        List Head,Tem,l1,l2;
        Head=(PtrToNode)malloc(sizeof(struct Node));
        Head->Next=NULL;
        Tem=Head;
        l1=L1->Next;
        l2=L2->Next;
        while(l1&&l2)
        {
                if(l1->Data<l2->Data)
                {
                        Tem->Next=l1;
                        l1=l1->Next;
                }
                else
                {
                        Tem->Next=l2;
                        l2=l2->Next;
                }
                Tem=Tem->Next;
        }
        while(l1)
        {
                Tem->Next=l1;
                l1=l1->Next;
                Tem=Tem->Next;
        }
        while(l2)
        {
                Tem->Next=l2;
                l2=l2->Next;
                Tem=Tem->Next;
        }
        L1->Next=NULL;
        L2->Next=NULL;
        return Head;
}
