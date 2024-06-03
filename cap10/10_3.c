# include "include/vec.h"
# include <stdio.h>
# include <assert.h>

/* Rearranja um quase max-heap v[1..m] de modo a 
* transformá-lo em max-heap */
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

/* Mostre que os invariantes da função SacodeHeap valem no início da primeira
* iteração. Supondo que os invariantes valem no início de uma iteração, mostre que elas
* continuam válidas no início da iteração seguinte */

/* invariante => v[[1/2i]] >= v[i] p/ todo i E [2..m], (i != f) & (i != f+1) 

* R: na primeira iteração temos v[1/2i] >= v[i] para i E [4..m] por definição (quase max-heap),
* mas como f = 2 (hipótese) então v[1/2i] >= v[i] para i E [2..m] (i!=f) & (i != f+1);
* Seja k uma dada iteração, que v[1/2i] >= v[i] para i E [2..m] (i!= f = 2^k) & (i != f+1),
* supomos que na iteração k+1 v[1/2i] >= v[i] não é válido para i E [2..m] (i != f = 2^(k+1)) & (i != f+1),
* portanto existe um i tal que v[1/2i] < v[i], mas como por hipótese v[1/2i] >= v[i] para i E [2..m] (i!= f = 2^k) & (i != f+1),
* então a única alternativa é que v[1/2i] < v[i] para i = 2^k ou v[1/2i] < v[i] para i = 2^(k+1).
* Supondo que v[2^(k+1)] > v[2^k] então temos que v[2^(k+1) / 2] < v[2^(k+1)], mas isto é um absurdo,
* pois se v[2^(k+1)/2] > v[2^(k+1)], o algoritmo faz a permutação. Idem para o caso em que v[2^(k+1)] <= v[2^k]*/

/* OBS: a demonstração acima supoe que o vetor é v[1..m], mas a implementação em C, parte do índice 0
* (pelo menos para o compilador clang que está sendo utilizado...)*/

/* 10.3.4 Escreva uma versão recursiva da função SacodeHeap*/
void SacodeHeapR(int f, int m, int v[])
{
    if (f > m) return;
    else {
        if (f < m && v[f] < v[f+1]) ++f;
        if (v[f/2] >= v[f]) return;
        int t = v[f/2]; v[f/2] = v[f]; v[f] = t;
        SacodeHeapR(2*f, m, v);
    }
}

int main(void)
{
    int n = 9;
    int max_heap[9] = {5, 50, 30, 20, 15, 12, 10, 3, 1};

    SacodeHeapR(1, n, max_heap);

    assert (is_max_heap(max_heap, n) == 1);   
    printf("OK");
}