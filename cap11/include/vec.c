# include "vec.h"

void print_vec(int v[], int i, int n)
{
    printf("[ ");
    for (; i < n; i++) printf("%d ", v[i]); 
    printf("]\n");
}

void swap(int v[], int a, int b)
{
    int valor = v[a];
    v[a] = v[b];
    v[b] = valor;
}

void assert_vec(int v[], int v2[], int i, int n)
{
    for (; i < n; i++)
    {
        assert (v[i] == v2[i]);
    }
}
