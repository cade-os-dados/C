#include "bin.h"
#include <stdio.h>
#include <assert.h>


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

/* 15.2 BEGIN */
int count(arvore r)
{
    if(r==NULL) return 0;
    int i = 1;
    i+=count(r->e);
    i+=count(r->d);
    return i;
}
/* 15.2 END */

/*
    Recebe uma árvore não vazia r, remove a raiz da árvore
    e rearranja a árvore de modo que ela continue sendo
    de busca. Devolve o endereço da nova raiz
*/
arvore RemoveRaiz(arvore r, int is_heap)
{
    arvore p, q;
    if(r->e==NULL) q = r->d;
    else
    {
        p = r; q = r->e;
        while(q->d != NULL)
        {
            p = q; q = q->d;
        }
        /* q é o nó anterior a r na ordem e-r-d */
        /* p é o pai de q */
        if (p != r)
        {
            p->d = q->e;
            q->e = r->e;
        }
        q->d = r->d;
    }
    if(is_heap)
        free(r);
    return q;
}

/*
    Agora para remover os filhos de x, basta fazer
    x->e = RemoveRaiz(x->e);
    x->d = RemoveRaiz(x->d);
*/

/*
    15.4.1 Suponha que nós com chaves 50,30,70,20,40,60,80,15,25,
    35,45,36 são inseridos, nesta ordem, numa árvore de busca
    inicialmente vazia. Desenhe a árvore que resulta. Em seguida,
    remova o nó que tem chave 30 de modo que a árvore continue
    sendo de busca.
*/

/*
    15.4.2 Critique a elegância do código da função RemoveRaiz.
    Tente escrever uma versão mais elegante.

    R: Mesma situação da seção anterior, poderia utilizar
    uma pilha para armazenar o pai do nó
*/

/*
    13.4.3 Escreva uma função recursiva da função RemoveRaiz.
*/

/* 
    o que faz o algoritmo? 
    se r->e for nulo retorna r->d e apaga r
    se r->e nao for nulo, toma q = max(r->e)
    e p = pai(max(r->e))
    se r->e->d != NULL entao troca
    p->d = q->e e q->e = r->e

    no final q->d = r->d

    3 casos então
    1. se r->e NULL retorna r->d / free(r)
    portanto, a nova raiz é r->d
    2. se r->e!=NULL e r->e->d NULL então r->e->d = r->e / free(e)
    portanto, a nova raiz é r->e
    3. mais fácil ilustrar com o diagrama abaixo

    (antes)
                7
            2e       8d
        1e       4d
            3e       6d
                 5e
    
    (depois)
                6
            2e      8d
        1e       4d
             3e       5d
*/

/* 
    lembrando que aqui não dou free
    porque estou supondo que r está na stack
 */
arvore RemoveRaizR(arvore r, arvore i)
{
    if(r==i)
    {
        if(r->e==NULL) return r->d;
        if(r->e->d==NULL)
        {
            r->e->d = r->d;
            return r->e;
        }
        arvore pq[2]; // p = pq[0], q = pq[1]
        pq[0] = RemoveRaizR(r,i->e);
        pq[1] = pq[0]->d;
        pq[0]->d = pq[1]->e;
        pq[1]->e = r->e;
        pq[1]->d = r->d;
        return pq[1];
    }

    if(i->d->d==NULL) 
        return i;
    else 
        return RemoveRaizR(r,i->d);
}

int main(void)
{
    /* 15.4.1 BEGIN */
    no a,a1,a2,a3,a4,a5,a6,a7,a8,a9,a10,a11;
    fillno(&a,50,&a1,&a2);
    fillno(&a1,30,&a3,&a4);
    fillno(&a2,70,&a5,&a6);
    fillno(&a3,20,&a7,&a8);
    fillno(&a4,40,&a9,&a10);
    fillno(&a5,60,&a11,NULL);
    fillno(&a6,80,NULL,NULL);
    fillno(&a7,15,NULL,NULL);
    fillno(&a8,25,NULL,NULL);
    fillno(&a9,35,NULL,NULL);
    fillno(&a10,45,NULL,NULL);
    fillno(&a11,36,NULL,NULL);

    assert(is_busca(&a));
    assert(count(&a) == 12);

    a.e=RemoveRaiz(a.e, 0);
    assert(is_busca(&a)); 
    assert(count(&a) == 11);
    /* 15.4.1 END */

    // 15.4.3
    a.e=RemoveRaizR(a.e, a.e);
    assert(is_busca(&a));
    assert(count(&a) == 10);

    printf("DETONADO!!!");
}