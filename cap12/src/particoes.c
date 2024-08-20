#include "particoes.h"

void pushp0(Subconjunto* list, int a)
{
    int new_n = (list -> n) + 1;
    realloc(list -> v, sizeof(int)*new_n);
    list -> n = new_n;

    int* vetor = list -> v;
    for (int i = 0; i < new_n - 1; i++)
    {
        vetor[i+1] = vetor[i];
    }
    vetor[0] = a;
}

void filterp0(SubconjuntoHead* head, int v)
{
    Subconjunto* anterior = head -> next;
    Subconjunto* loop = anterior -> next;
    
    if ((anterior -> v)[0] > v)
    {
        free(anterior -> v);
        head -> next = loop;
        free(anterior);
        anterior = loop;
        loop = loop -> next;
    }

    while (loop != NULL)
    {
        if ((loop -> v)[0] > v)
        {
            free(loop -> v);
            anterior -> next = loop -> next;
            free(loop);
            loop = anterior -> next;
        }
        else{
            anterior = loop;
            loop = loop -> next;
        } 
    }
}