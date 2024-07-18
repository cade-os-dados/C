#include "comb.h"

darray init_darray(int k)
{
    darray indices = dnew(sizeof(int) * k, 4);
    for (int i = 0; i < k; i++)
        push(&indices, i);
    return indices;
}

int next_combination(
    int n, int k,
    darray* indices)
{
    int idx = k-1;
    if (indices->valores[0] == (n-k))
        return 0;
    if (indices->valores[idx] < n-1)
        (indices->valores[idx])++;
    else{
        int cidx = idx-1;
        while(indices->valores[cidx] == (n-(k-cidx)))
            cidx--;
        int value = indices->valores[cidx] + 1;
        for (int i = cidx; i < k; i++)
        {
            indices->valores[i] = value;
            value++;
        }
    }
    return 1;
}

void combine(int* v, int n, int k, int* counter)
{
    darray indices = init_darray(k);
    do {
        (*counter)++;
        print_by_index(v, &indices);
    } while (next_combination(n, k, &indices));
}

// C(n,k) = n! / k! (n-k)!
int ncombs(int n, int k)
{
    return fatorial(n) / (fatorial(k) * fatorial(n-k));
}