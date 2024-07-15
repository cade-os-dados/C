#include "comb.h"

// 1 2 3 4 5
// 1 2 3
// 1 2 4
// 1 2 5
// 1 3 4
// 1 3 5
// 1 4 5
// 2 3 4
// 2 3 5
// 2 4 5
// 3 4 5

// C(5, 3) = 10
// 5! / 3! (5-3)! = 120 / 6*(2) = 120/12 = 10

void combinacoes(int* v, int n, int k)
{
    darray indices = dnew(sizeof(int) * k, 4);
    for (int i = 0; i < k; i++)
        push(&indices, i);

    int gap = (n - k);
    while (indices.valores[0] <= gap)
    {
        print_by_index(v, &indices);

        // rode 3 vezes, 2 , 1
        for (int i = 1; i <= gap - indices.valores[0]; i++)
        {
            for (int c = 1; c < k; c++)
                indices.valores[c]++;
            print_by_index(v, &indices);
        }

        // reset
        indices.valores[0]++;
        for (int i = 1; i < k; i++)
           indices.valores[i] = indices.valores[0] + i;
    }
}