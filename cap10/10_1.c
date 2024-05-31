# include <assert.h>
# include <stdio.h>

/* 10.1.1 Mostre que todo vetor decrescente é um max-heap
* Mostre que a recíproca não é verdadeira */

/* Hipótese: v é decrescente
* Tese: v é também max-heap
* R: seja v um vetor decrescente, isto é, v[i] >= v[i+1], p/ todo i E (-inf, +inf)
* então, para um dado i, temos que i/2 <= i, logo pela definição acima,
* v[i/2] >= v[i]. CDQ

* Hipótese: v é max-heap
* Tese: v é decrescente
* R: seja v = [12, 11, 7, 8], temos que v[1] >= v[2] e v[1] >= v[3],
* porém v[3] > v[2]. Logo, v é max-heap mas não é decrescente. CQD. */

/* 10.1.2 O vetor 161 41 101 141 71 91 31 21 81 17 16 é um max-heap? */
/*R: não, para i = 2, temos v[1] = 41 < v[2] = 101 */

/* 10.1.3 Escreva uma função que decida se um vetor v[1..m] é ou não
* um max-heap */

int is_max_heap(int v[], int n){
    for (int i = n-1; i > 0; i--)
        if (v[i] > v[i/2]) return 0;
    return 1;
}

int main(void)
{
    int v[4] = {12, 11, 7, 8};
    int v2[11] = {161, 41, 101, 141, 71, 91, 31, 21, 81, 17, 16};

    assert (is_max_heap(v, 4) == 1);
    assert (is_max_heap(v2, 11) == 0);
    printf("OK");
}