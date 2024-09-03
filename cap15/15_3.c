#include "bin.h"
#include <assert.h>
#include <stdio.h>

/* 15.1 BEGIN */
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
/* 15.1 END */

arvore new(int k)
{
    arvore novo = malloc(sizeof(no));
    novo->chave=k;
    novo->e=novo->d=NULL;
    return novo;
}

/*
    Recebe uma árvore de busca r e uma folha avulsa novo.
    Insere novo na árvore de modo que a árvore continue
    sendo de busca e devolve o endereço da nova árvore
*/

arvore insere(arvore r, arvore novo)
{
    arvore f,p;
    if(r==NULL) return novo;
    f=r;
    while(f!=NULL)
    {
        p=f;
        if(f->chave > novo->chave) f = f->e;
        else f = f->d;
    }
    if(p->chave > novo->chave) p->e = novo;
    else p->d = novo;
    return r;
}

/*
    15.3.1 Critique a elegância do código da função Insere.
    Escreva uma versão mais elegante. Sugestão: use um
    ponteiro-para-ponteiro, ou seja, um objeto do tipo
    no** ou arvore*
*/

arvore insereElegante(arvore r, arvore novo)
{
    if(r==NULL) return novo;
    arvore p[100]; int i = 0; p[0] = r;
    while(p[i] != NULL)
    {
        if(p[i]->chave > novo->chave) {
            p[i+1] = p[i]->e;
            i++;
        }
        else {
            p[i+1] = p[i]->d;
            i++;
        }
    }
    if(p[i-1]->chave > novo->chave) p[i-1]->e=novo;
    else p[i-1]->d=novo;
    return r;
}

arvore insereR(arvore r, arvore novo)
{
    if(r==NULL) return novo;
    arvore r1 = r, t;
    if(r->chave > novo->chave)
    {
        t = insereR(r->e, novo);
        if(t!=novo) r1=t;
    } else {
        t = insereR(r->d, novo);
        if(t!=novo) r1=t;
    }
    if(r1->chave > novo->chave) r1->e=novo;
    else r1->d=novo;
    return r;
}

int main(void)
{
    no a, b, c, d, e; 
    a.chave=2;a.e=&b;a.d=&c;
    b.chave=1;
    c.chave=4;c.e=&d;c.d=&e;
    d.chave=3;
    e.chave=5;
    b.e=b.d=d.e=d.d=e.e=e.d=NULL;

    arvore novo = new(6);
    insereElegante(&a, novo);
    assert(is_busca(&a));

    insereR(&a, new(10));
    assert(is_busca(&a));

    printf("OK");
}