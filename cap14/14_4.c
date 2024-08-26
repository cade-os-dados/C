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
    if(arv->pai != NULL && (arv->pai->valor) < arv->valor)
        return 0;
    if (!is_max_heap(arv -> e))
        return 0;
    if(!is_max_heap(arv -> d))
        return 0;
    return 1;
}

int is_almost_max_heap(noComPai arv)
{
    if(!is_max_heap(arv -> e -> e))
        return 0;
    if(!is_max_heap(arv -> e -> d))
        return 0;
    if(!is_max_heap(arv -> d -> e))
        return 0;
    if(!is_max_heap(arv -> d -> d))
        return 0;
    return 1;
}

/* 
    Input: arv -> e != NULL & arv -> d != NULL
    Result: 1 -> d, 0 -> e

*/
int no_cmp(noComPai arv)
{
    if ((arv -> d -> valor) > (arv -> e -> valor))
        return 1;
    return 0;
}

void SacodeHeapTree(noComPai arv)
{
    /*break condition*/
    if ((arv -> e == NULL) & (arv -> d == NULL))
        return;

    noComPai child;

    if ((arv -> e == NULL) | (no_cmp(arv)))
        child = arv -> d;
    else 
        child = arv -> e;

    no_swap(arv, child);
    SacodeHeapTree(child);       
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

    
    int array[6] = {4,10,3,5,1,12};
    int array2[6] = {4,12,10,5,3,1};

    noComPai arv = from_array(array, 6);
    to_heap(arv); // transforma em heap
    assert(is_max_heap(arv));

    noComPai arv2 = from_array(array2, 6);
    assert(!is_max_heap(arv2));
    assert(is_almost_max_heap(arv2));
    
    SacodeHeapTree(arv2);
    assert(is_max_heap(arv2));

    printf("OK");

}