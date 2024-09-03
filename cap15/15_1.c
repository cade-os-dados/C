#include <stdio.h>
#include <assert.h>
#include "bin.h"

/*
    15.1.1 Escreva uma função que decida se uma dada
    árvore binária é ou não é de busca
*/

arvore minr(arvore r)
{
    if(r==NULL) return r;
    arvore min_e = minr(r->e);
    arvore min_d = minr(r->d);
    arvore resultado = r;
    if(min_e!=NULL && min_e->chave<resultado->chave)
        resultado = min_e;
    if(min_d!=NULL && min_d->chave<resultado->chave)
        resultado = min_d;
    return resultado;
}

arvore maxr(arvore r)
{
    if(r==NULL) return r;
    arvore max_e = maxr(r->e);
    arvore max_d = maxr(r->d);
    arvore resultado = r;
    if(max_e!=NULL && max_e->chave > resultado->chave)
        resultado = max_e;
    if(max_d!=NULL && max_d->chave > resultado->chave)
        resultado = max_d;
    return resultado;
}

int is_busca(arvore r)
{
    if(r==NULL) return 1;
    if(r->e!=NULL)
    {
        if((r->chave < minr(r->e)->chave) || !is_busca(r->e))
            return 0;
    }
    if(r->d!=NULL)
    {
        if((r->chave > maxr(r->d)->chave) || !is_busca(r->d))
            return 0;
    }
    return 1;
}

/* 
    15.1.2 Suponha que x.e->chave <= x.chave <= x.d->chave para
    cada nó X de uma árvore binária. Esta árvore é de busca?

    R: não, pois não garante que x.chave >= max(x.e)->chave
    ou x.chave <= min(x.d)->chave
*/

int main(void)
{
    no a, b, c, d, e; 
    a.chave=2;a.e=&b;a.d=&c;
    b.chave=1;
    c.chave=4;c.e=&d;c.d=&e;
    d.chave=3;
    e.chave=5;
    b.e=b.d=d.e=d.d=e.e=e.d=NULL;

    /*     
            a
        b       c
            d       e
    */
   assert(is_busca(&a));
   printf("OK");
}