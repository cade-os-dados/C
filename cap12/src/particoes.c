#include "particoes.h"

void pushp0(Subconjunto* list, int a)
{
    int new_n = (list -> n) + 1;
    list -> v = (int*)realloc(list -> v, sizeof(int)*new_n);
    list -> n = new_n;

    int* vetor = list -> v;
    for (int i = new_n - 1; i >= 1; i--)
    {
        vetor[i] = vetor[i-1];
    }
    vetor[0] = a;
}

void pushp0all(SubconjuntoHead* head, int a)
{
    Subconjunto* loop = head -> next;
    while(loop != NULL)
    {
        pushp0(loop, a);
        loop = loop -> next;
    }
}

void filterp0(SubconjuntoHead* head, int v)
{
    Subconjunto* anterior = head -> next;
    Subconjunto* loop = anterior -> next;
    
    while ((anterior -> v)[0] > v && anterior != NULL)
    {
        free(anterior -> v);
        head -> next = loop;
        free(anterior);
        anterior = loop;
        loop = loop -> next;
    }
}

Subconjunto* from_array(int vetor[], int n)
{
    Subconjunto* r = malloc(sizeof(Subconjunto));
    r -> v = malloc(sizeof(int)*n);
    int* v = r -> v;
    for(int i = 0; i < n; i++)
    {
        v[i] = vetor[i];
    }
    r -> n = n;
    return r;
}

void printsub(SubconjuntoHead* head)
{
    Subconjunto* ploop = head -> next;

    while(ploop != NULL)
    {
        print_vec(ploop -> v, 0, ploop -> n);
        ploop = ploop -> next;
    }
}


void appendsub(Subconjunto* tail, SubconjuntoHead* l2)
{
    tail -> next = l2 -> next;
    free(l2);
}

Subconjunto* tailsub(Subconjunto* nottail)
{
    Subconjunto* tail = nottail;
    while(tail -> next != NULL)
        tail = tail -> next;
    return tail;
}