#include <stdio.h>
#include <stdlib.h>

typedef struct _NODE {
    char data;
    struct _NODE* link;
} NODE;

NODE* head;
NODE* list;
int length;

void InsertNodeAt(char a, int index);
void PrintList();

int main()
{
    InsertNodeAt('p', 0);
    InsertNodeAt('p', 0);
    InsertNodeAt('e', 100);
    InsertNodeAt('a', 0);
    InsertNodeAt('l', 3);
    PrintList();

    return 0;
}

void InsertNodeAt(char a, int index)
{
    NODE* front;

    if(head==NULL)
    {
        list = (NODE*)malloc(sizeof(NODE));
        head = list;
        front = head;
        length = 1;
        head->data = a;
        head->link = NULL;
    }
    
    else
    {
        if(index>=length)
        {
            length += 1;
            front = head;
            list = (NODE*)realloc(list, sizeof(NODE)*length);
            while(1)
            {
                if((front->link) == NULL)
                {
                    break;
                }
                
                else
                {
                    front = (front->link);
                }
            }
            
            (front->link) = &(list[length-1]);
            ((list[length-1]).data) = a;
            ((list[length-1]).link) = NULL;
            
        }
        
        else
        {
            front = head;
            length += 1;
            list = (NODE*)realloc(list, sizeof(NODE)*length);
            
            for(int i=0; i<index-1; i++)
            {
                front = (front->link);
            }
            
            NODE* save;
            if(index == 0)
            {
                save = head;
                head = &(list[length-1]);
                ((list[length-1]).data) = a;
                ((list[length-1]).link) = save;
            }

            else
            {
                save = (front->link);
                (front->link) = &(list[length-1]);
                ((list[length-1]).data) = a;
                ((list[length-1]).link) = save;
            }
        }
    }
    
    return;
}

void PrintList()
{
    NODE* scan = head;
    printf("PrintList(): ");
    while(1)
    {
        printf("%c", (scan->data));
        
        if(scan->link == NULL)
        {
            break;
        }
        
        else
        {
            scan = scan->link;
        }
    }
    printf("\n");
}