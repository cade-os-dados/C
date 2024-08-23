#include "no.h"
#include "pilha.h"
#include <stdio.h>
#include <assert.h>

/* Devolve a altura da árvore binária r*/
int altura(no r)
{
    if (r==NULL) return -1;
    else
    {
        int he = altura(r->e);
        int hd = altura(r->d);
        if (he < hd) return hd+1;
        else return he+1;
    }
}

/* 14.3.2 Escreva uma função iterativa que calcule
* a altura de uma árvore binária. */

int alturai(no r)
{
    int max = 0;
    pilha p; p.idx = 0;
    while(1)
    {
        int t = 0;
        while(r != NULL)
        {
            push(&p, r);
            r = r -> d;
            t++;
        }
        if(max < p.idx) max = p.idx;
        if (p.idx == 0) break;
        if (t == 0) 
            r = pop(&p);
        else 
            r = get(&p);
        r = r -> e;
    }
    return max+1;
}

/* 
    14.3.3 ÁRVORES AVL. Uma árvore é balanceada no sentido AVL
    se, para cada nó x, as alturas das subárvores esquerda e
    direita de x diferem em no máximo uma unidade. Escreva uma
    função que decida se uma dada árvore é balanceada no sentido
    AVL. Procure escrever sua função de modo que ela visite cada
    nó no máximo uma vez.
*/

/*
    R: não passa apenas 1 vez em cada nó mas ainda assim
    é uma solução elegante!
*/

int is_avl(no r)
{
    if(r == NULL) return 1;
    if ((is_avl(r -> d)) & (is_avl(r -> e)))
    {
        int he = altura(r -> e);
        int hd = altura(r -> d);
        if (abs(he-hd) <= 1)
            return 1;
    }
    return 0;
}

int main(void)
{  
    /* 
        Aqui eu joguei tudo para heap sem necessidade
        igual quando estou trabalhando com lista ligada
    */
    no t = malloc(sizeof(arvore));
    no_malloc_child(t);
    no_malloc_child(t -> e);
    no_malloc_child(t -> e -> e);
    no_malloc_child(t -> e -> e -> d);
    no_malloc_child(t -> e -> e -> d -> e);
    t -> valor = 5; 
    t -> e -> valor = 10; 
    t -> d -> valor = 12;
    t -> e -> e -> valor = 8;
    t -> e -> d -> valor = 50;
    t -> e -> e -> e -> valor = 15;
    t -> e -> e -> d  -> valor = 7;
    t -> e -> e -> d -> d = NULL;
    t -> e -> e -> d -> e  -> valor = 18;
    t -> e -> e -> d -> e  -> e = NULL;
    t -> e -> e -> d -> e  -> d -> valor = 200;
    
    int h = altura(t);
    assert(h == 5);
    assert(h == alturai(t));
    
    assert(is_avl(t) == 0);
    assert(is_avl(t->e->e->d) == 0);
    assert(is_avl(t->e->e->d->e) == 1);

    printf("OK\n");
}