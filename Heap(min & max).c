#include <stdio.h>
#include <stdlib.h>

/****/
/** ___                   ___
   |   |                 |   \
   |___|    _   _  |     |    |
   |    |/ |_| |_| |-    |    |
   |    |  |_  |_  |_  . |___/

**/
int arr[100];
int size = 0;
int min = 0;
int max = 0;

int parent(int x);
int indexof(int x);
void swap(int x, int y);
void heapifyup(int x);
void insert(int x);
void heapifydown(int x, int n);
void heap_sort();

int parent(int x)
{
    int i;
    for(i=1; i<=size; i++)
    {
        if(arr[i] == x)
            return i/2;
    }
    return 0;
}

int indexof(int x)
{
    int i;
    for(i=1; i<=size; i++)
    {
        if(arr[i] == x)
            return i;
    }
    return 0;
}

void swap(int x, int y)
{
    int t = arr[x];
    arr[x] = arr[y];
    arr[y] = t;
}

void heapifyup(int x)
{
    if(min == 1)
    {
        while(indexof(x)!=1 && x<arr[parent(x)])
        {
            swap(indexof(x), parent(x));
        }
    }

    if(max == 1)
    {
        while(indexof(x)!=1 && x>arr[parent(x)])
        {
            swap(indexof(x), parent(x));
        }
    }

}

void insert(int x)
{
    arr[++size] = x;
    heapifyup(x);
}


void heapifydown(int x, int n)
{
    int smallest, highest;
    int left = indexof(x) * 2;
    int right = indexof(x) * 2 +1;
    if(min == 1)
    {
       if(left <=n && arr[left] < arr[indexof(x)])
            smallest = left;
        else
            smallest = indexof(x);

        if(right <= n && arr[right] < arr[smallest] )
            smallest = right;

        if(smallest != indexof(x))
        {
            swap(indexof(x), smallest);
            heapifydown(arr[smallest], n);
        }
    }

    if(max == 1)
    {
       if(left <=n && arr[left] > arr[indexof(x)])
            highest = left;
        else
            highest = indexof(x);

        if(right <= n && arr[right] > arr[highest] )
            highest = right;

        if(highest != indexof(x))
        {
            swap(indexof(x), highest);
            heapifydown(arr[highest], n);
        }
    }

}

void heap_sort()
{
    int i;
    int n = size;
    for(i=n; i>=2; i--)
    {
        swap(1, i);
        n--;
        heapifydown(arr[1], n);

    }

}

int main()
{
    int op, n, i, x;
    printf("\n MIN_HEAP: 1");
    printf("\n MAX_HEAP: 2\n");
    scanf("%d", &op);
    if(op == 1)
        min = 1;
    else
        max = 1;

    printf("\nEnter number of elements: ");
    scanf("%d", &n);

    for(i=0; i<n; i++)
    {
        scanf("%d", &x);
        insert(x);
    }
    printf("\n\n*********HEAP************\n");
    for(i=1; i<=size; i++)
    {
        printf("%d || ", arr[i]);
    }
    heap_sort();
    printf("\n\n*********SORTED HEAP************\n");
    if(min == 1)
        printf("\nIn Descending order: (MIN HEAP)\n");
    else
        printf("\nIn Ascending order: (MAX HEAP)\n");
    for(i=1; i<=size; i++)
    {
        printf("%d || ", arr[i]);
    }
    printf("\n");
    return 0;

}

/*Output

 MIN_HEAP: 1
 MAX_HEAP: 2
1

Enter number of elements: 5
5
3
4
2
1


*********HEAP************
1 || 2 || 4 || 5 || 3 ||

*********SORTED HEAP************

In Descending order: (MIN HEAP)
5 || 4 || 3 || 2 || 1 ||

Process returned 0 (0x0)   execution time : 15.756 s
Press any key to continue.

************* OUTPUT 2 *************

 MIN_HEAP: 1
 MAX_HEAP: 2
2

Enter number of elements: 5
5
3
4
2
1


*********HEAP************
5 || 3 || 4 || 2 || 1 ||

*********SORTED HEAP************

In Ascending order: (MAX HEAP)
1 || 2 || 3 || 4 || 5 ||

Process returned 0 (0x0)   execution time : 13.166 s
Press any key to continue.


*/
