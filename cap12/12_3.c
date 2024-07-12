#include "vec.h"

/* recebe s[1..k] e m e imprime, em ordem lexicográfica,
* cada uma das subsequências não vazias de m, ..., n precedida
* do prefixo s[1..k]. Em outras palavras, imprime todas as
* sequências que têm a forma s[1],.., s[k], t[k+1], ..., sendo
* t[k+1], ... uma subsequência não vazia de m, ..., n. */
void sseqr(int s[], int k, int m, int n)
{
    if (m <= n)
    {
        s[k+1] = m;
        print_vec(s, 1, k+2);
        sseqr(s, k+1, m+1, n); /* inclui m */
        sseqr(s, k, m+1, n); /* não inclui m */
    }
}

/* Recebe n >= 1 e imprime, em ordem lexicográfica,
* todas as subsequências não vazias de 1, 2, ..., n */
void subseqlex2(int n)
{
    int *s;
    s = malloc((n+1) * sizeof(int));
    sseqr(s, 0, 1, n);
    free(s);
}

/* 12.3.1 Escreva uma função que receba um vetor estritamente crescente
* s[1..k] representando uma subsequência s1, s2, ..., sk de 1,2,...n
* e grave, no espaço alocado a s, a próxima subsequência na ordem lexicográfica.
* A função deve devolver o número de termos (k+1 ou k-1) da nova subsequência*/

/* R: apenas relembrando a definição de ordem lexicográfica de
* uma subsequência...

* Uma sequência r1, r2,..., rj é lexicograficamente menor que
* outra s1,s2,...,sk se
* 1. j < k e r1,...,rj é igual a s1,...,sj ou
* 2. existe i tal que r1, ..., r_{i-1} é igual a s1, ..., s_{i-1} e ri < si. */

int next(int v[], int *s, int i, int n)
{
    if (v[i-1] < n)
    {
        s = realloc(s, sizeof(int) * i+1);
        copy_vec(v, s, i);
        s[i] = s[i-1] + 1;
        return i+1;
    }
    else
    {
        copy_vec(v, s, i);
        s[i-2] = v[i-2] + 1;
        return i-1;
    }
}

int main(int argc, char** argv)
{
    int *vetor = sqt_vec(10, 0);
    for (int i = 0; i < 10; i++) vetor[i] = vetor[i] + 1;
    int expected[9] = {1, 2, 3, 4, 5, 6, 7, 8, 10};

    int *s = malloc(sizeof(int) * 10);
    int new_n = next(vetor, s, 10, 10);

    int vetor2[2] = {1, 2};
    int expected2[3] = {1, 2, 3};
    int *s2 = malloc(sizeof(int) * 2);
    int new_n2 = next(vetor2, s2, 2, 3);

    assert_vec(expected, s, 0, new_n);
    assert_vec(expected2, s2, 0, new_n2);
    printf("OK");
}