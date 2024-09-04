#include "bin.h"
#include <assert.h>
#include <stdio.h>
#include <math.h>

/*
    Recebe k e uma árvore de busca r. Devolve um nó cuja
    chave é k ou devolve NULL se tal nó não existe
*/
arvore busca(arvore r, int k)
{
    if(r==NULL || r->chave == k)
        return r;
    if(r->chave > k)
        return busca(r->e,k);
    else
        return busca(r->d,k);
}

arvore buscaIter(arvore r, int k)
{
    while(r!=NULL && r->chave != k)
    {
        if(r->chave>k) r = r->e;
        else r = r->d;
    }
    return r;
}

/*
    15.2.1 Escreva uma função que encontre uma chave mínima em
    uma árvore de busca. Escreva uma função que encontre uma
    chave máxima.
*/
arvore minima(arvore r)
{
    while(r->e!=NULL) r=r->e;
    return r;
}

arvore maxima(arvore r)
{
    while(r->d!=NULL) r=r->d;
    return r;
}

/*
    15.2.2 Suponha que as chaves de nossa árvore de busca são
    distintas duas a duas. Escreva uma função que receba uma
    chave k e devolva a chave seguinte na ordem crescente
*/

int next(arvore r, int k)
{
    while(r->chave <= k) r = r->d;
    return r->chave;
}

/*
    15.2.3 Escreva uma função que transforme um vetor
    crescente em uma árvore de busca balanceada
*/
arvore from_array(int v[], int i, int n, int outOfBounds)
{
    if(i>n || i >= outOfBounds) return NULL;
    arvore r=malloc(sizeof(no));
    int mid = (n+i)/2;
    r->chave=mid;
    r->conteudo=v[mid];
    r->e = from_array(v, i, mid-1, outOfBounds);
    r->d = from_array(v, mid+1, n, outOfBounds);
    return r;
}

/*
    15.2.4 Escreva uma função que transforme uma árvore
    de busca em um vetor crescente
*/
int count(arvore r)
{
    if(r==NULL) return 0;
    int i = 1;
    i+=count(r->e);
    i+=count(r->d);
    return i;
}

void from_arvore(arvore r, int* vetor, int i, int n)
{
    if (r==NULL) return;
    int mid = (i+n)/2;
    vetor[mid] = r->conteudo;
    from_arvore(r->e, vetor, i, mid-1);
    from_arvore(r->d, vetor, mid+1, n);
}

/*
    15.2.5 BUSCA BINÁRIA. Há uma relação muito íntima entre
    árvores de busca e o algoritmo de busca binária num vetor
    (veja Capítulo 7). Qual é, exatamente esta relação?

    R: a relação é que na busca binária estamos sempre
    calculando o índice do meio e na árvore de busca
    binária, o nó é equivalente ao indíce do meio,
    tendo em vista que tudo à esquerda é menor e
    tudo à direita é maior
*/

int main(void)
{
    no a, b, c, d, e; 
    fillno(&a, 2, &b, &c);
    fillno(&b, 1, NULL, NULL);
    fillno(&c, 4, &d, &e);
    fillno(&d, 3, NULL, NULL);
    fillno(&e, 5, NULL, NULL);

    assert(minima(&a) == &b); // 15.2.1
    assert(maxima(&a) == &e); // 15.2.1
    assert(next(&a,3)==4); // 15.2.2

    int v[6] = {1,2,3,4,5,6};
    arvore r = from_array(v,0,6,6);
    assert(busca(r,2)->conteudo==3); // 15.2.3

    int n = count(r);
    assert(n == 6);
    int vetor[n];
    from_arvore(r, vetor, 0, n); // 15.2.4

    for(int i = 0; i < n; i++)
        assert(vetor[i] == v[i]);

    printf("OK");
}