# include "vec.h"
# include "separa.h"
# include <stdio.h>

/* Esta função rearranja o vetor v[p..r] com p <= r+1,
* de modo que ele fique em ordem crescente */
void quicksort (int p, int r, int v[])
{
    int j;
    if (p < r) {
        j = separacao(p, r, v);
        quicksort(p, j-1, v);
        quicksort(j+1, r, v); 
    }
}

/* 11.3.6 TAIL RECURSION. Moestre que a segunda invocação da função quicksort
* pode ser eliminada se trocarmos o if por um while apropriado */
void tailquicksort(int p, int r, int v[])
{
    while (p < r)
    {
        int j = separacao(p, r, v);
        tailquicksort(p, j-1, v);
        p = j+1;
    }  
}

/* 11.3.11 VERSÃO ITERATIVA. Escreva uma versão não recursiva
* do algoritmo quicksort */
void iterquicksort(int v[], int n)
{
    int p = 0; int r = n;
    while (p < r)
    {
        int j = separacao(p,r,v);
        p = j+1;
    }

    p = 0; r = n;
    while (p < r)
    {
        int j = separacao(p,r,v);
        r = j-1;
    }
}

int main(void)
{
    int vetor[5] = {14, 5, -5, 18, 20};
    int vetor2[5] = {14, 5, -5, 18, 20};
    int vetor3[12] = {14, 5, -5, 18, 20, 74, -15, 24, 40, 0, 3, -44};
    int expected[5] = {-5, 5, 14, 18, 20};
    int expected2[12] = {-44, -15, -5, 0, 3, 5, 14, 18, 20, 24, 40, 74};
    quicksort(0, 4, vetor);
    tailquicksort(0, 4, vetor2);
    iterquicksort(vetor3, 11);
    assert_vec(vetor, expected, 0, 5);
    assert_vec(vetor2, expected, 0, 5);
    assert_vec(vetor3, expected2, 0, 12);
    printf("OK");
}
