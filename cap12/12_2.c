#include <stdlib.h>
#include "vec.h"

/* Esta função recebe n >= 1 e imprime todas as 
* subsequências não vazias de 1, 2, ..., n 
* em ordem lexicográfica. */
void subseqlex (int n)
{
    int *s, k;
    s = malloc((n+1) * sizeof(int));
    s[0] = 0; k = 0;
    while (1) {
        if (s[k] < n) {
            s[k+1] = s[k] + 1;
            k+=1;
        } else {
            s[k-1] += 1;
            k -= 1;
        }
        if (k == 0) break;
        print_vec(s, 1, k+1);
    }
    free(s);
}

/* 12.2.3 Escreva uma função que imprima  uma lista
* de todos os subconjuntos do conjunto {1,2,...,n}. */


int main(int argc, char** argv)
{
    if (argc > 1)
    {
        int n = atoi(argv[1]);
        if (n > 0)
            subseqlex(n);
    }
    return 0;
}
