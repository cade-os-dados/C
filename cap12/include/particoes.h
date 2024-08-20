#include <stdlib.h>

typedef struct mlist
{
    int *v;
    int n;
    struct mlist* next;
} Subconjunto;

typedef struct
{
    struct mlist* next;
} SubconjuntoHead;

/*push at position 0*/
void pushp0(Subconjunto* list, int a);
void filterp0(SubconjuntoHead* head, int v);

/* tamanhos de subconjuntos -> exemplo
    1 1 1
    1 2
    3

    1 1 1 1
    1 1 2
    2 2
    1 3
    4

    5
    4,1
    3,2
    3,1,1
    2,2,1
    2,1,1,1
    1,1,1,1,1

    6
    5 1
    4 2
    4 1 1
    3 3
    3 2 1
    3 1 1 1
    2 2 2
    2 2 1 1
    2 1 1 1 1
    1 1 1 1 1 1
*/