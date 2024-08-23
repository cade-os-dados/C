#include "no.h"
#include <assert.h>
#include <stdio.h>

/*
    14.4.1 Escreva uma função que preencha corretamente todos
    os campos pai de uma árvore binária
*/

void preencher(noComPai no)
{
    if(no == NULL) return;
    if(no -> d != NULL) 
    {
        no -> d -> pai = no;
        preencher(no -> d);
    }
    if(no -> e != NULL) 
    {
        no -> e -> pai = no;
        preencher(no -> e);
    }
}

/*
    14.4.2 A profundidade de um nó em uma árvore binária é
    a distância entre o nó e a raiz da árvore. Mais precisa_
    mente, a profundidade de um nó X é o comprimento do (único)
    caminho que vai da raiz até X. Por exemplo, a profundidade
    da raiz é 0 e a profundidade de qualquer filho da raiz é 1.
    Escreva uma função que determine a profundidade de um nó dado.
*/

int profundidade(noComPai a)
{
    int i = 0;
    while(a -> pai != NULL)
    {
        a = a -> pai;
        i++;
    }
    return i;
}

/*
    14.4.5 HEAP. Em que condições uma árvore binária pode ser
    considerada um heap (veja Seção 10.1)? Escreva uma função
    que transforme um max-heap em uma árvore binária quase com-
    pleta. Escreva uma versão da função SacodeHeap (Seção 10.3)
    para um max-heap representado por uma árvore binária

    R: é um max-heap se p/ todo nó, valor(pai) >= valor(no)
    e min-heap valor(pai) <= valor(no) p/ todo no
*/

void print_arvore(noComPai arvore)
{
    if (arvore != NULL)
    {
        printf("%d ", arvore -> valor);
        print_arvore(arvore -> e);
        print_arvore(arvore -> d);
    }
}

void print_no(noComPai arv)
{
    printf("{ ");
    print_arvore(arv);
    printf("}\n");
}

/* Transformar uma array em uma árvore binária */
noComPai from_array2(int v[], int n)
{
    int esquerda = 1; int idx = 0;
    int t = sizeof(arvoreComPai);
    noComPai arv = malloc(t);
    noComPai loop = arv;

    while(idx < n)
    {
        loop -> valor = v[idx];
        if(esquerda)
        {
            loop -> e = malloc(t);
            loop -> e -> pai = loop;
            loop = loop -> e;
            loop -> e = loop -> d = NULL;
            esquerda = 0;
        }
        else
        {
            loop = loop -> pai;
            loop -> d = malloc(t);
            loop -> d -> pai = loop;
            loop = loop -> d;
            loop -> e = loop -> d = NULL;
            esquerda = 1;
        }
        idx++;
    }
    if(esquerda)
        loop -> pai -> d = NULL;
    else
        loop -> pai -> e = NULL;

    free(loop);
    return arv;
}

void to_heap(noComPai arv)
{
    if (arv == NULL)
        return;
    to_heap(arv -> e);
    to_heap(arv -> d);
    if (arv -> e != NULL)
    {
        if((arv -> e -> valor) > (arv -> valor))
        {
            int valor = arv -> valor;
            arv -> valor = arv -> e -> valor;
            arv -> e -> valor = valor;
        }
    }
    if (arv -> d != NULL)
    {
        if((arv -> d -> valor) > (arv -> valor))
        {
            int valor = arv -> valor;
            arv -> valor = arv -> d -> valor;
            arv -> d -> valor = valor;
        }
    }
}

int is_max_heap(noComPai arv)
{
    if (arv == NULL)
        return 1;
    if ((arv -> pai -> valor) < arv -> valor)
        return 0;
    if (!is_max_heap(arv -> e))
        return 0;
    if(!is_max_heap(arv -> d))
        return 0;
    return 1;
}

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
    int t,f = 2;
    while(f <= m)
    {
        if (f < m && v[f] < v[f+1]) ++f;
        if(v[f/2] >= v[f]) break;
        t = v[f/2]; v[f/2] = v[f]; v[f] = t;
        f *= 2;
    }
}

int main(void)
{
    arvoreComPai r, n1, n2, n3, n4, n5, n6;

    r.valor = 5; r.pai = NULL;
    no_append_insere_compai(&r, &n1, &n2, 10, 12);
    no_append_insere_compai(&n1, &n3, &n4, 15, 18);
    no_append_insere_compai(&n2, &n5, &n6, 8, 14);

    no_inserenull_compai(&n3); no_inserenull_compai(&n4);
    no_inserenull_compai(&n5); no_inserenull_compai(&n6);

    preencher(&r);

    assert(n1.pai == &r); assert(n2.pai == &r);
    assert(n3.pai == &n1); assert(n4.pai == &n1);
    assert(n5.pai == &n2); assert(n6.pai == &n2);
    assert(profundidade(&n3) == 2);
    assert(profundidade(&n5) == 2);
    assert(profundidade(&n2) == 1);
    assert(profundidade(&r) == 0);

    int array2[6] = {4,10,3,5,1,12};

    noComPai arv2 = from_array2(array2, 6);
    to_heap(arv2);

    assert(is_max_heap(arv2) == 1);

    printf("OK");

}