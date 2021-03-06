#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFFER_SIZE 1000
#define MEMORY_ALLOCATION_ERROR  -1

// list node
typedef struct Node {
    int *data;
    int array_size;
    struct Node* next;
    struct Node* prev;
} Node;

// doubly linked list
typedef struct List {
    Node *head;
    Node *tail;
    int size;
} List;

// iterator
typedef struct iterator {
    int position;
    struct Node* node_ptr;
} iterator;

// forward initialization
iterator begin(Node* head) {
    iterator it = {0, head};
    return it;
}

// backward initialization
iterator end(Node* tail) {
    iterator it = {tail->array_size - 1, tail};
    return it;
}

// initialize list
void init(List *list) {
    list->head = NULL;
    list->tail = NULL;
    list->size = 0;
}

// ---------------------------------------------- to implement ...

// append element to the list
void push_back(List *list, int *data, int array_size) {
    Node *n = malloc(sizeof(Node));
    Node *tmp;
    if(n == NULL) exit(MEMORY_ALLOCATION_ERROR);
    n->data = data;
    n->array_size = array_size;
    if (list->head == NULL)
    {
        n->next = NULL;
        n->prev = NULL;
        list->head = n;
        list->tail = n;
        list->size += 1;
    }
    else
    {
        //list->tail->next = n;

        tmp = list->head;
        while (tmp->next != NULL)
        {
            tmp = tmp->next;
        }
        tmp->next = n;
        n->prev = tmp;

        n->next = NULL;
        list->size += 1;

    }
}

// set iterator to move n elements forward from its current position
void skip_forward(iterator* itr, int n) {
    Node *p = itr->node_ptr;
    int suma = 0;
    while (suma != n)
    {
        
    }
}

// forward iteration - get n-th element in the list
int get_forward(List *list, int n) {
    int suma = 0;
    Node *p = list->head;
    while (suma < n)
    {
        suma += p->array_size;
        p = p->next;
    }
    p = p->prev;
    int index = n - suma + p->array_size - 1;
    return *(p->data + index);
}

// set iterator to move n elements backward from its current position
void skip_backward(iterator* itr, int n) {
    Node *p = itr->node_ptr;
    for (int i = 0; i < n; i++)
    {
        p = p->prev;
    }
}

// backward iteration - get n-th element from the end of the list
int get_backward(List *list, int n) {
    int suma = 0;
    int sum = 0;
    Node *p1 = list->head;
    Node *k = list->head;
    Node *p = list->tail;
    while (k->next != NULL)
    {
        sum += k->array_size;
        k = k->next;
    }

    if (k->array_size + sum == n)
    {
        return *(p1->data + 0);
    }
    if (k->array_size >= n)
    {
        int index = k->array_size - n;
        return *(k->data + index);
    }
    sum += k->array_size;
    return get_forward(list,sum-n+1);
}

// remove n-th element; if array empty remove node
void remove_at(List *list, int n) {
    int suma = 0;
    Node *p = list->head;
    while (suma < n && p->next != NULL)
    {
        suma += p->array_size;
        p = p->next;
    }
    if (suma >= n) {
        p = p->prev;
    }
    else
    {
        suma += p->array_size;
    }
    if (p->array_size > 1){
        int index = n - suma + p->array_size - 1;
        int *dat = p->data;
        int* temp = malloc((p->array_size - 1) * sizeof(int));

        memmove(
                temp,
                dat,
                (index + 1) * sizeof(int));
        memmove(
                temp + index,
                (dat) + (index + 1),
                (p->array_size - index) * sizeof(int));


        free (dat);
        p->data = temp;
        p->array_size -= 1;
    }
    else
    {
        if (p == list->head)
        {
            Node *tmp2 = p;
            list->head = list->head->next;
            free(tmp2);
            tmp2 = NULL;
        }
        else if (p->next != NULL)
        {
            Node *tmp2 = p->prev;
            tmp2->next = p->next;
            p->next->prev = tmp2;
            free(p);
            p = NULL;
        }
        else
        {
            Node *t = p->prev;
            t->next = NULL;
            list->tail = t;
            free(p);
        }
    }
}

// -------------------- helper functions

// print list
void dumpList(const List *list) {
    for(Node *node = list->head; node != NULL; node = node->next) {
        printf("-> ");
        for (int k = 0; k < node->array_size; k++) {
            printf("%d ", node->data[k]);
        }
        printf("\n");
    }
}

// remove the first element
void delete_front(List *list) {
    Node *to_delete;
    if(list->head == NULL) return;
    to_delete = list->head;
    list->head = list->head->next;
    if(list->head == NULL) list->tail = NULL;
    free(to_delete->data);
    free(to_delete);
    list->size--;
}

// free list
void freeList(List *list) {
    while(list->head) {
        delete_front(list);
    }
}

// read int vector
void read_vector(int tab[], int n) {
    for (int i = 0; i < n; ++i) {
        scanf("%d", tab + i);
    }
}

// initialize the list and push data
void read_list(List *list) {
    int size, n;
    init(list);
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        scanf("%d", &size);
        int *tab = (int*) malloc((size_t)size * sizeof(int));
        read_vector(tab, size);
        push_back(list, tab, size);
    }
}

int main() {
    int to_do, size, m;
    List list;

    scanf("%d", &to_do);
    read_list(&list);
    switch (to_do) {
        case 1:
            dumpList(&list);
            break;
        case 2:
            scanf("%d", &size);
            for (int i = 0; i < size; i++) {
                scanf("%d", &m);
                printf("%d ", get_forward(&list, m));
            }
            printf("\n");
            break;
        case 3:
            scanf("%d", &size);
            for (int i = 0; i < size; i++) {
                scanf("%d", &m);
                printf("%d ", get_backward(&list, m));
            }
            printf("\n");
            break;
        case 4:
            scanf("%d", &size);
            for (int i=0; i < size; i++) {
                scanf("%d", &m);
                remove_at(&list, m);
            }
            dumpList(&list);
            break;
        default:
            printf("NOTHING TO DO FOR %d\n", to_do);
            break;
    }
    freeList(&list);

    return 0;
}
