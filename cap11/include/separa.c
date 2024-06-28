#include "separa.h"

void assert_separada(int v[], int n)
{
    int meio;
    for (int i = 0; i < n; i++)
        if (v[i] > 0) {meio = i; break;}
    for (int i = 0; i < meio; i++)
        assert(v[i] <= 0);
    for (int i = meio; i < n; i++)
        assert(v[i] > 0);
}

void assert_separada_j(int v[], int n, int j)
{
    for (int i = 0; i < j; i++) assert (v[i] <= v[j]);
    for (int i = j+1; i < n; i++) assert (v[i] > v[j]);
}