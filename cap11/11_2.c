# include "vec.h"
# include "separa.h"

/* Recebe um vetor v[p..r] com p <= r. Rearranja os
* elementos do vetor e devolve j em p..r tal que
* v[p..j-1] <= v[j] < v[j+1..r] */
int separa(int p, int r, int v[])
{
    int c, j, k, t;
    c = v[r]; j = p;
    for (k = p; k < r; k++)
        if (v[k] <= c)
        {
            t = v[j], v[j] = v[k], v[k] = t;
            j++;
        }
    v[r] = v[j], v[j] = c;
    return j;
}

/* 11.2.7 ESTABILIDADE a função separa produz um rearranjo
* estável (veja seção 8.5) do vetor? */
/* Não, pois fará um swap se v[k] <= c, alterando a estabilidade
* do vetor */

/* 11.2.8 Escreva uma versão recursiva do algoritmo da separação */
int separaR(int p, int r, int j, int v[])
{
    if (p == r) { swap(v, j, r); return j;}
    if ( v[p] <= v[r] ) { swap(v, p, j); j++; }
    j = separaR(p+1, r, j, v);
    return j;
}

int main(void)
{
    // iterativa
    int vetor[5] = {-1, 0, 15, -5, 13};
    int j = separa(0, 4, vetor);

    // recursiva
    int vetor2[5] = {-1, 0, 15, -5, 13};
    int j2 = separaR(0, 4, 0, vetor2);

    assert(j == j2);
    assert_separada_j(vetor, 5, j);
    assert_separada_j(vetor2, 5, j2);
    assert_vec(vetor, vetor2, 0, 5);
    printf("OK");
}
