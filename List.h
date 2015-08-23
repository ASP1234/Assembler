#ifndef LIST_H_INCLUDED
#define LIST_H_INCLUDED

typedef struct node
{
    void* dataPtr;
    struct node *link;

}NODE;

typedef struct
{
    NODE *head;
    int count;
    int (*compare)(void*,void*);

}LIST;

LIST* createList(int(*compare)(void* arg1,void* arg2))
{
    LIST* list=(LIST*)malloc(sizeof(LIST));

    if(list)
    {
        list->head=NULL;
        list->count=0;
        list->compare=compare;
    }

    return list;
}

static bool _search(void* key,NODE** previous,NODE** current,LIST* list)
{
    #define COMPARE \
    (((*list->compare)(key,(*current)->dataPtr)))

    int result;

    *previous=NULL;
    *current=list->head;

    if(list->count==0)
        return false;

    while((result=COMPARE)!=0)
    {
        *previous=*current;
        *current=(*current)->link;

        if(*current==NULL)
            break;
    }

    if(result==0)
        return true;

    else
        return false;
}

static bool _insert(void* dataInPtr,NODE* previous,LIST* list)
{
    NODE* newPtr=(NODE*)malloc(sizeof(NODE));

    if(!newPtr)
    return false;

    newPtr->dataPtr=dataInPtr;
    if(!previous)
    {
        newPtr->link=list->head;
        list->head=newPtr;
    }

    else
    {
        newPtr->link=previous->link;
        previous->link=newPtr;
    }

    (list->count)++;
    return true;
}

int addNode(void* dataInPtr,LIST* list)
{
    NODE *previous,*current;
    bool found,success;

    found=_search(dataInPtr,&previous,&current,list);

    if(found)
        return 1;

    success=_insert(dataInPtr,previous,list);

    if(!success)
        return -1;

    return 0;
}

bool searchList(void** dataOutPtr,void* key,LIST* list)
{
    bool found;
    NODE *previous,*current;

    found=_search(key,&previous,&current,list);

    if(found)
    *dataOutPtr=current->dataPtr;

    else
        *dataOutPtr=NULL;

    return found;
}

LIST* destroyList(LIST* list)
{
    NODE* current;

    if(list)
    {

        while(list->count>0)
        {
            current=list->head;
            list->head=list->head->link;
            list->count--;
            free(current);
        }

        free(list);
    }

    return NULL;
}


#endif // LIST_H_INCLUDED
