#include "ordenacao.h"

int compar(const void *a, const void *b)
{
    return ( *(int*)a - *(int*)b );
}

int stdsort(int* v, int ini, int n)
{
    qsort(&v[ini], n, sizeof(int), compar);
}