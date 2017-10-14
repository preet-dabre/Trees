#include <stdio.h>
#include <stdlib.h>
/****/
/** ___                   ___
   |   |                 |   \
   |___|    _   _  |     |    |
   |    |/ |_| |_| |-    |    |
   |    |  |_  |_  |_  . |___/

**/
typedef struct nd
{
    int data;
    int height;
    struct nd* left;
    struct nd* right;
}node, *nodep;

int max(int a, int b)
{
    int c;
    c = (a>b)?a:b;
    return c;
}
int getHeight(nodep x)
{
    if(x==NULL)
        return 0;
    return x->height;
}

nodep createNode(int data)
{
    nodep newnode = (nodep)malloc(sizeof(node));
    if(!newnode)
        return NULL;
    newnode->data = data;
    newnode->left = NULL;
    newnode->right = NULL;
    newnode->height = 1;
    return newnode;
}

nodep rightRotate(nodep y)
{
    nodep x = y->left;
    nodep Rx = x->right;

    //rotating
    x->right = y;
    y->left = Rx;

    //changing heights
    y->height = max(getHeight(y->left), getHeight(y->right))+1;
    x->height = max(getHeight(x->left), getHeight(x->right))+1;
    return x;

}

nodep leftRotate(nodep y)
{
    nodep x = y->right;
    nodep Lx = x->left;

    //rotating
    x->left = y;
    y->right = Lx;

    //changin heights
    y->height = max(getHeight(y->left), getHeight(y->right))+1;
    x->height = max(getHeight(x->left), getHeight(x->right))+1;
    return x;

}

nodep leftRightRotate(nodep y)
{
    y->left = leftRotate(y->left);
    return rightRotate(y);
}

nodep rightLeftRotate(nodep y)
{
    y->right = rightRotate(y->right);
    return leftRotate(y);
}

int getBalanceFactor(nodep x)
{
    if(x==NULL)
        return 0;
    return (getHeight(x->left)-getHeight(x->right));
}

void inorder(nodep root)
{
    if(root->left)
    inorder(root->left);
    printf(" %d[%d]", root->data, getBalanceFactor(root));
    if(root->right)
    inorder(root->right);
}


nodep insertAVL(nodep root, int data)
{
    if(root==NULL)
        return(createNode(data));

    if(data < root->data)
        root->left = insertAVL(root->left, data);
    else if(data > root->data)
        root->right = insertAVL(root->right, data);
    else  // Duplicte condi
        return root; // not inserted

    //heigth of root
    root->height = 1 + max(getHeight(root->left), getHeight(root->right));
    //printf("\nInorder traversal befor rotations: ");


    //check whether root becomes unbalanced
    int balance = getBalanceFactor(root);
    if(balance < -1 || balance > 1)
    {
        printf("\nInorder traversal befor rotations: \n");
        inorder(root);
        printf("\n");
    }
    //*****************LL*****************
    if(balance > 1 && data < root->left->data)
    {
        printf("\n For Inserting %d Left of Left Rotation required!", data);
        return rightRotate(root);
    }

    ////*****************RR*****************
    if(balance < -1 && data > root->right->data)
    {
        printf("\n For Inserting %d Right of Right Rotation required!", data);
        return leftRotate(root);
    }

    //*****************LR*****************
    if(balance > 1 && data > root->left->data)
    {
        printf("\n For Inserting %d Left of Right Rotation required!", data);
        return leftRightRotate(root);
    }

    //*****************RL*****************
    if(balance < -1 && data < root->right->data)
    {
        printf("\n For Inserting %d Right of Left Rotation required!", data);
        return rightLeftRotate(root);
    }

    return root;
}

int searchAVL(nodep root, int key)
{
    if(root==NULL)
        return 0;
    if(key==root->data)
        return 1;
    else{
        if(key<root->data)
        {
            if(root->left)
            return searchAVL(root->left, key);
            else
                return 0;
        }
        if(key>root->data)
        {
            if(root->right)
            return searchAVL(root->right, key);
            else
                return 0;
        }
    }
}

nodep getSuccessor(nodep root)
{
    nodep curr = root;

    while(curr->left!=NULL)
        curr = curr->left;
    return curr;

}

nodep deleteAVL(nodep root, int key)
{

    //normal binary delete
    if(root==NULL)
        return root;
    if (key<root->data)  //to left
        root->left = deleteAVL(root->left, key);
    else if(key>root->data) //to right
         root->right = deleteAVL(root->right, key);
    else //this node delete
    {
        //node with only one child or leaf
        if((root->left==NULL) || (root->right==NULL))
        {
            nodep temp = root->left ? root->left : root->right;
            if(temp == NULL)
            {
                temp = root;
                root = NULL;
            }
            else //one child
               *root = *temp;
            free(temp);
        }
        else
        {   //node with two children
            //get successor
            nodep temp = getSuccessor(root->right);
            //put successor to this position
            root->data = temp->data;
            //delete redundant node
            root->right = deleteAVL(root->right, temp->data);
        }
    }

    if(root == NULL)
        return root; //if had only one node which got deleted

    //Update height
    root->height = 1 + max(getHeight(root->left), getHeight(root->right));

    //get balance factor to check whether unbalanced
    int balance = getBalanceFactor(root);
    // if unbalanced
    /********LL************/
    if(balance > 1 && getBalanceFactor(root->left) >= 0)
        return rightRotate(root);
    /********LR************/
    if(balance > 1 && getBalanceFactor(root->left) < 0)
        return leftRightRotate(root);
    /********RR************/
    if(balance < -1 && getBalanceFactor(root->right) <= 0)
        return leftRotate(root);
    /********RL************/
    if(balance < -1 && getBalanceFactor(root->right) > 0)
        return rightLeftRotate(root);

    return root;


}

void main()
{
    nodep root = NULL;
    int n;
    int x;
    while(1)
    {
        printf("\n0. Insert Series: ");
        printf("\n1. Insertion: ");
        printf("\n2. Deletion: ");
        printf("\n3. Search: ");
        printf("\n4. Quit: ");
        scanf("%d", &n);
        switch(n)
        {
            case 0: printf("\n Enter 1111 to stop series insertion");
                    while(1)
                    {
                        printf("\nElement to Insert: ");
                        scanf("%d",&x);
                        if(x==1111)
                            break;
                            printf("\nInserting node: %d", x);
                            root = insertAVL(root, x);
                            printf("\nInorder Traversal: ");
                            inorder(root);
                            printf("\n \n");

                    }
                    break;

            case 1: printf("\nElement to Insert: ");
                    scanf("%d",&x);
                    printf("\nInserting node: %d", x);
                    root = insertAVL(root, x);
                    printf("\nInorder Traversal: ");
                    inorder(root);
                    printf("\n \n");
                    break;
            case 2: printf("\nElement to delete: ");
                    scanf("%d",&x);
                    if(searchAVL(root, x))
                    {
                        root = deleteAVL(root, x);
                        printf("\nInorder Traversal: ");
                        inorder(root);
                    }
                    else
                        printf("\nNode not found!");
                    break;
            case 3: printf("\nElement to Search: ");
                    scanf("%d",&x);
                    if(searchAVL(root, x))
                        printf("\nFound");
                    else
                        printf("\nNot Found");
                    break;
            case 4: printf("\nFinal Inorder Traversal \n");
                    inorder(root);
                    exit(1);
        }
    }


}

/* Output

0. Insert Series:
1. Insertion:
2. Deletion:
3. Search:
4. Quit: 0

 Enter 1111 to stop series insertion
Element to Insert: 10

Inserting node: 10
Inorder Traversal:  10[0]


Element to Insert: 20

Inserting node: 20
Inorder Traversal:  10[-1] 20[0]


Element to Insert: 30

Inserting node: 30
Inorder traversal befor rotations:
 10[-2] 20[-1] 30[0]

 For Inserting 30 Right of Right Rotation required!
Inorder Traversal:  10[0] 20[0] 30[0]


Element to Insert: 8

Inserting node: 8
Inorder Traversal:  8[0] 10[1] 20[1] 30[0]


Element to Insert: 7

Inserting node: 7
Inorder traversal befor rotations:
 7[0] 8[1] 10[2]

 For Inserting 7 Left of Left Rotation required!
Inorder Traversal:  7[0] 8[0] 10[0] 20[1] 30[0]


Element to Insert: 9

Inserting node: 9
Inorder traversal befor rotations:
 7[0] 8[-1] 9[0] 10[1] 20[2] 30[0]

 For Inserting 9 Left of Right Rotation required!
Inorder Traversal:  7[0] 8[0] 9[0] 10[0] 20[-1] 30[0]


Element to Insert: 35

Inserting node: 35
Inorder traversal befor rotations:
 20[-2] 30[-1] 35[0]

 For Inserting 35 Right of Right Rotation required!
Inorder Traversal:  7[0] 8[0] 9[0] 10[0] 20[0] 30[0] 35[0]


Element to Insert: 34

Inserting node: 34
Inorder Traversal:  7[0] 8[0] 9[0] 10[-1] 20[0] 30[-1] 34[0] 35[1]


Element to Insert: 1111

0. Insert Series:
1. Insertion:
2. Deletion:
3. Search:
4. Quit: 2

Element to delete: 33

Node not found!
0. Insert Series:
1. Insertion:
2. Deletion:
3. Search:
4. Quit: 2

Element to delete: 10

Inorder Traversal:  7[0] 8[0] 9[0] 20[0] 30[0] 34[0] 35[0]
0. Insert Series:
1. Insertion:
2. Deletion:
3. Search:
4. Quit: 3

Element to Search: 6

Not Found
0. Insert Series:
1. Insertion:
2. Deletion:
3. Search:
4. Quit: 3

Element to Search: 9

Found
0. Insert Series:
1. Insertion:
2. Deletion:
3. Search:
4. Quit: 4

Final Inorder Traversal
 7[0] 8[0] 9[0] 20[0] 30[0] 34[0] 35[0]
Process returned 1 (0x1)   execution time : 159.059 s
Press any key to continue.

*/
