# include "include/vec.h"
# include <stdio.h>

void InsereEmHeap(int m, int v[])
{
    int f = m+1;
    while (f > 1 && v[f/2] < v[f]){
        int t = v[f/2]; v[f/2] = v[f]; v[f] = t;
        f = f/2;
    }
}

void SacodeHeap(int m, int v[])
{
    int t, f = 2;
    while (f <= m)
    {
        if (f < m && v[f] < v[f+1]) ++f;
        if (v[f/2] >= v[f]) break;
        t = v[f/2]; v[f/2] = v[f]; v[f] = t;
        f *= 2;
    }
}

/* Rearranja o vetor v[1..n] de modo que ele fique crescente*/
void heapsort (int n, int v[])
{
    int m;
    for (m=1; m < n; m++)
        InsereEmHeap(m,v); /*transforma em max heap*/
    for (m = n; /*X*/ m > 1; m--)
    {
        int t = v[1]; v[1] = v[m]; v[m] = t; /*pega o valor máximo do vetor v[1..m] e coloca em v[m]*/
        SacodeHeap(m-1, v); /*transforma v[1..m] em max-heap*/
    }
}

/*10.4.1 Use a função Heapsort para ordenar o vetor 16 15 14 13 12 11 10 9 8 7 6 5 4*/
/*R: está na função main*/

/*10.4.2 Suponha que o vetor v[1..n] é um max-heap. O seguinte fragmento de código
* rearranja o vetor em ordem crescente? */
/*R: Sim, ele utiliza o algoritmo de inserção para ordenar o vetor [1..m]*/
void heapsort2 (int n, int v[])
{
    int m;
    for (m=1; m < n; m++)
        InsereEmHeap(m,v); /*transforma em max heap*/
    for (m = n; /*X*/ m >= 2; m--)
    {
        int x = v[1];
        for (int j=1; j < m; j++) v[j] = v[j+1];
        v[m] = x;
    }
}

/*10.4.3 Verifique os invariantes da função Heapsort*/
/*R: Estão descritos de maneira informal na função*/

int main(void)
{
    int vetor[5] = {0, 12, 4, 15, 100};
    int expected[5] = {0, 4, 12, 15, 100};
    heapsort(4, vetor);
    assert_vec(vetor, expected, 1, 5);

    /*10.4.1*/
    int vetor2[13] = {16, 15, 14, 13, 12, 11, 10, 9, 8, 7, 6, 5, 4};
    int vetor3[13] = {16, 15, 14, 13, 12, 11, 10, 9, 8, 7, 6, 5, 4};
    int expected2[13] = {16, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15};
    
    heapsort(12, vetor2);
    heapsort2(12, vetor3);

    assert_vec(vetor2, expected2, 1, 13);
    assert_vec(vetor3, expected2, 1, 13);

    printf("OK");
}