# include "vec.h"
# include <stdio.h>

void print_vec(int v[], int i, int n)
{
    printf("[ ");
    for (; i < n; i++) printf("%d ", v[i]); 
    printf("]\n");
}

int is_max_heap(int v[], int n){
    for (int i = n-1; i > 0; i--)
        if (v[i] > v[i/2]) return 0;
    return 1;
}

int is_almost_max_heap(int v[], int n)
{
    for (int i = n-1; i > 3; i--)
        if (v[i] > v[i/2]) return 0;
    return 1;
}
