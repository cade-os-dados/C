/*10.5.1 ORDEM DECRESCENTE. Escreva uma versão do algoritmo Heapsort 
* que rearranje um vetor v[1..n] de modo que ele fique em ordem decrescente */


/* 10.5.2 ORDENAÇÃO DE STRINGS. Escreva uma versão do algoritmo Heapsort
* que coloque um vetor de strings em ordem lexicográfica*/

/*R: Mesma coisa, só substituir por strcmp*/

# include "include/vec.h"
# include <stdio.h>
# include <assert.h>

void heap_insertion(int m, int v[])
{
    int f = m;
    while (f > 1 && v[f/2] > v[f]){
        int t = v[f/2]; v[f/2] = v[f]; v[f] = t;
        f = f/2;
    }
}

void to_min_heap(int n, int v[])
{
    for (int m=1; m < n; m++)
        heap_insertion(m, v);
}

void sacode_heap(int m, int v[])
{
    int t, f = 2;
    while (f <= m)
    {
        if (f < m && v[f] >= v[f+1]) ++f;
        if (v[f/2] < v[f]) break;
        t = v[f/2]; v[f/2] = v[f]; v[f] = t;
        f *= 2;
    }
}

/*v[0..n] é max heap ... v[1..n] = ?*/

/* Rearranja o vetor v[1..n] de modo que ele fique crescente*/
void heapsort (int n, int v[])
{
    to_min_heap(n, v);
    for (int m = n-1; m > 1; m--)
    {
        int t = v[1]; v[1] = v[m]; v[m] = t; 
        sacode_heap(m-1, v);
    }
}

int main(void)
{
    int vetor[10] = {200, 3, 15, 5, 20, 17, 13, 11, 22, 21};
    int expected[10] = {1, 22,21,20,17,15,13,11,5,3};

    heapsort(10, vetor);
    assert_vec(vetor, expected, 1, 10);
    printf("OK");
}