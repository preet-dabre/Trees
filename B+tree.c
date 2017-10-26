#include <stdio.h>
#include <stdlib.h>
#define T 5
/****/
/** ___                   ___
   |   |                 |   \
   |___|    _   _  |     |    |
   |    |/ |_| |_| |-    |    |
   |    |  |_  |_  |_  . |___/

**/
typedef struct node {
    int n; // keys
    int keys[T-1]; // key array
    struct node *p[T]; //children
}vertex, *vertexp;

vertexp root = NULL;  //null at first

typedef struct list{  //linked list for leaf nodes
    vertexp data;
    struct list* next;

}llist, *llistp;

llistp head = NULL; //NULL at first


//Methods
void addToList(vertexp nod);
int isLeaf(vertexp nod);
int position(int key, int *k_array, int n);
int insertHelp(vertexp ptr, int key, int *pKey,vertexp *newnode);
void insert(int key);
void inorder(vertexp ptr);
void search(int key);
void searchFromList(int key, vertexp nod);


void addToList(vertexp nod)
{
    llistp newnode = (llistp)malloc(sizeof(llist));
    newnode->data = nod;
    newnode->next = NULL;
    if(head == NULL)
    {
         head = newnode;
         return;
    }
    llistp temp = head;
    while(temp->next!=NULL)
    {
        temp = temp->next;
    }
    temp->next = newnode;
    return;


}

int isLeaf(vertexp nod)
{
    int i=0;
    for(i=0; i<=nod->n; i++)
    {
        if(nod->p[i]!=NULL) //if child exists means it isn't leaf
            break;
    }
    if(i==nod->n)
        return 1;
    else
        return 0;
}

void insert(int key)
{
    vertexp newnode;
    int pKey;
    int value;
    value = insertHelp(root, key, &pKey, &newnode);  //call by reference {multiple return values so}
    /*level increases by 1 if enter below*/
    if (value == 1)
    {
        vertexp uproot = root;
        root=malloc(sizeof(vertex));
        root->n = 1;
        root->keys[0] = pKey;
        root->p[0] = uproot;
        root->p[1] = newnode;
        if(isLeaf(root) == 1)
            addToList(root);
    }/*if*/

}/*insert()*/

int insertHelp(vertexp ptr, int key, int *pKey, vertexp *newnode)
{
    vertexp newPtr;
    vertexp lastPtr;
    int pos, median;
    int i, n;
    int newKey, lastKey;
    int value;
    if (ptr == NULL)
    {
        *newnode = NULL;
        *pKey = key;
        return 1;
    }
    n = ptr->n;
    pos = position(key, ptr->keys, n);
    value = insertHelp(ptr->p[pos], key, &newKey, &newPtr);
    if (value != 1)
        return value;
    /*If node is not full*/
    if (n < T - 1)
    {
        pos = position(newKey, ptr->keys, n);
        /*Shifting keys and children right to create space for new key*/
        for (i=n; i>pos; i--)
        {
            ptr->keys[i] = ptr->keys[i-1];
            ptr->p[i+1] = ptr->p[i];
        }
        /*Key is inserted at space created*/
        ptr->keys[pos] = newKey;
        ptr->p[pos+1] = newPtr;
        ++ptr->n; /*Number of keys in increased by 1*/
        return 2;
    }/*if*/
    /*If full */
    //if key is to be inserted at last position
    if (pos == T - 1)
    {
        lastKey = newKey;
        lastPtr = newPtr;
    }
    else // full and not last
    {
        lastKey = ptr->keys[T-2];
        lastPtr = ptr->p[T-1];
        for (i=T-2; i>pos; i--)
        {
            ptr->keys[i] = ptr->keys[i-1];
            ptr->p[i+1] = ptr->p[i];
        }
        ptr->keys[pos] = newKey;
        ptr->p[pos+1] = newPtr;
    }
    median = (T - 1)/2;
    (*pKey) = ptr->keys[median];

    (*newnode)=malloc(sizeof(vertex));/*Right node after split*/ /* ptr is now left split node*/
    ptr->n = median; /*no of keys for Left split node*/
    if(isLeaf(ptr) == 1)
    {
        (*newnode)->n = T-1-median+1;/**Added 1 here**//*no of keys for Right split node*/
    }
    else
    {
        (*newnode)->n = T-1-median;//*no of keys for Right split node*/
    }
    //constructing right child
    for (i=0; i < (*newnode)->n; i++)
    {
        if(isLeaf(ptr) == 1)
        {
            (*newnode)->p[i] = ptr->p[i+median];/** removed 1 here **/
            if(i < (*newnode)->n - 1)
                (*newnode)->keys[i] = ptr->keys[i+median];  /** removed 1 here **/
            else
                (*newnode)->keys[i] = lastKey;
        }
        else
        {
            (*newnode)->p[i] = ptr->p[i+median + 1];
            if(i < (*newnode)->n - 1)
                (*newnode)->keys[i] = ptr->keys[i+median + 1];
            else
                (*newnode)->keys[i] = lastKey;
        }

    }
    (*newnode)->p[(*newnode)->n] = lastPtr;
    if(isLeaf(ptr) == 1)
    {
        addToList(*newnode);
    }
    return 1;
}/*insertHelp()*/

int position(int key, int *k_array, int n)
{
    int pos=0;
    while (pos < n && key > k_array[pos])
        pos++;
    return pos;
}/*position()*/

void search(int key)  /**Changes Here (Major)**/
{
    int pos, n;
    vertexp ptr = root;
    while (!isLeaf(ptr))
    {
        n = ptr->n;
        pos = position(key, ptr->keys, n);
        ptr = ptr->p[pos];
    }
    searchFromList(key, ptr);
}/*search()*/

void searchFromList(int key, vertexp nod)
{
    int i;
    if(head == NULL)
    {
         printf("\nKey not found");
         return;
    }
    llistp temp = head;
    while(temp->next->data!=nod)
    {
        temp = temp->next;
    }
    temp = temp->next;
    while(temp->next!=NULL)
    {
        for(i=0; i<temp->data->n; i++)
        {
            if(temp->data->keys[i]==key)
            {
                printf("\nKey Found");
                return;
            }
        }
    }
    printf("\nKey not found");
    return;

}

void inorder(vertexp ptr)   /**Changes Here (Major)**/
{
    int i;
    if(head == NULL)
    {
         printf("\nNull Tree");
         return;
    }
    llistp temp = head;
    while(temp->next!=NULL)
    {
        for(i=0; i<temp->data->n; i++)
        {
            printf("%d ", temp->data->keys[i]);
        }

    }

}/*inorder()*/


int main()
{
    int key;
    int choice;
    printf("B+tree OPERATIONS order =%d\n",T);
    while(1)
    {
        printf("1.Insert\n");
        printf("2.Search\n");
        printf("3.Traverse\n");
        printf("4.Quit\n");
        printf("Enter your choice : ");
        scanf("%d",&choice);

        switch(choice)
        {
        case 1:
            printf("Enter the key : ");
            scanf("%d",&key);
            insert(key);
            printf("Traversal: ");
            inorder(root);
            printf("\n");
            break;
        case 2:
            printf("Enter the key : ");
            scanf("%d",&key);
            search(key);
            break;
        case 3:
            printf("B+tree traversal:\n");
            inorder(root); printf("\n");
            break;
        case 4:
            exit(1);
        default:
            printf("Wrong choice\n");
            break;
        }/*switch*/
    }/*while*/
    return 0;
}/*main()*/

/**Output**/
/*
B+tree OPERATIONS order=5
1.Insert
2.Search
3.Traverse
4.Quit
Enter your choice : 1
Enter the key : 10
Traversal: 10
1.Insert
2.Search
3.Traverse
4.Quit
Enter your choice : 1
Enter the key : 20
Traversal: 10 20
1.Insert
2.Search
3.Traverse
4.Quit
Enter your choice : 1
Enter the key : 30
Traversal: 10 20 30
1.Insert
2.Search
3.Traverse
4.Quit
Enter your choice : 1
Enter the key : 40
Traversal: 10 20 30 40
1.Insert
2.Search
3.Traverse
4.Quit
Enter your choice : 1
Enter the key : 50
Traversal: 10 20 30 40 50
1.Insert
2.Search
3.Traverse
4.Quit
Enter your choice : 1
Enter the key : 29
Traversal: 10 20 29 30 40 50
1.Insert
2.Search
3.Traverse
4.Quit
Enter your choice : 1
Enter the key : 28
Traversal: 10 20 28 29 30 40 50
1.Insert
2.Search
3.Traverse
4.Quit
Enter your choice : 1
Enter the key : 27
Traversal: 10 20 27 28 29 30 40 50
1.Insert
2.Search
3.Traverse
4.Quit
Enter your choice : 1
Enter the key : 21
Traversal: 10 20 21 27 28 29 30 40 50
1.Insert
2.Search
3.Traverse
4.Quit
Enter your choice : 1
Enter the key : 22
Traversal: 10 20 21 22 27 28 29 30 40 50
1.Insert
2.Search
3.Traverse
4.Quit
Enter your choice : 1
Enter the key : 23
Traversal: 10 20 21 22 23 27 28 29 30 40 50
1.Insert
2.Search
3.Traverse
4.Quit
Enter your choice : 1
Enter the key : 51
Traversal: 10 20 21 22 23 27 28 29 30 40 50 51
1.Insert
2.Search
3.Traverse
4.Quit
Enter your choice : 1
Enter the key : 52
Traversal: 10 20 21 22 23 27 28 29 30 40 50 51 52
1.Insert
2.Search
3.Traverse
4.Quit
Enter your choice : 1
Enter the key : 54
Traversal: 10 20 21 22 23 27 28 29 30 40 50 51 52 54
1.Insert
2.Search
3.Traverse
4.Quit
Enter your choice : 1
Enter the key : 53
Traversal: 10 20 21 22 23 27 28 29 30 40 50 51 52 53 54
1.Insert
2.Search
3.Traverse
4.Quit
Enter your choice : 2
Enter the key : 31
Key 31 not found
1.Insert
2.Search
3.Traverse
4.Quit
Enter your choice : 2
Enter the key : 51
Key 51 found
1.Insert
2.Search
3.Traverse
4.Quit
Enter your choice : 2
Enter the key : 22
Key 22 found
1.Insert
2.Search
3.Traverse
4.Quit
Enter your choice : 3
B+tree traversal:
10 20 21 22 23 27 28 29 30 40 50 51 52 53 54
1.Insert
2.Search
3.Traverse
4.Quit
Enter your choice : 4

Process returned 1 (0x1)   execution time : 133.567 s
Press any key to continue.
*/










