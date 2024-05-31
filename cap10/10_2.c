# include "include/vec.h"
# include <assert.h>

/* Esta função recebe um max-heap v[1..m] e transforma
* v[1..m+1] em max-heap */
void InsereEmHeap(int m, int v[])
{
    int f = m+1;
    while (f > 1 && v[f/2] < v[f]){
        int t = v[f/2]; v[f/2] = v[f]; v[f] = t;
        f = f/2;
    }
}

/* 10.2.1 Por que a seguinte implementação da função InsereEmHeap é
* ligeiramente mais eficiente que a dada no texto? */

void heapInsertion(int m, int v[])
{
    int p, f = m+1;
    while (f > 1 && v[p = f/2] < v[f])
    {
        int t = v[p]; v[p] = v[f]; v[f] = t;
        f = p;
    }
}

/* Evita recalcular f/2 várias vezes, porém talvez o compilador
* possa realizar este ajuste sozinho */

/* 10.2.2 Escreva uma versão recursiva da função InsereEmHeap*/
void heapInsertionR(int m, int v[])
{
    if (m <= 0) return;
    if (v[m/2] < v[m]){
        int t = v[m/2]; 
        v[m/2] = v[m]; 
        v[m] = t;
    }
    heapInsertionR(m/2, v);
}

/* 10.2.3 CONSTRUÇÃO DE UM MAX-HEAP. Escreva uma função eficiente que rearranje
* um vetor arbitrário de modo a transformá-lo em um max-heap. (Sugestão: use a função
* InsereEmHeap.) */

void to_max_heap(int v[], int n)
{
    for (int i = 2; i < n; i++)
    {
        heapInsertionR(i, v);
    }
}

/* 10.2.4 Critique a seguinte ideia: para transformar um vetor arbitrário
* em max-heap, basta colocá-lo em ordem decrescente. */

/* R: Em geral,é mais custoso (computacionalmente) utilizar um algoritmo de ordenação */

int main(void)
{
    /* 10.2.2 && 10.2.3 */
    int vetor3[10] = {-1, 14, 11, 9, 12, 7, 13, 5, 4, 16};
    to_max_heap(vetor3, 10);

    assert( is_max_heap(vetor3, 10) == 1 );
}