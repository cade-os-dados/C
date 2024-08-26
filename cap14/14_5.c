#include "no.h"
#include <stdio.h>
#include <assert.h>

/*
    Recebe um no x de uma arvore binaria cujos nós tem
    campo pai e devolve o no seguinte na ordem e-r-d
    A função supoe que x != NULL
*/
noComPai next(noComPai x)
{
    if (x -> d != NULL)
    {
        noComPai y = x->d;
        while(y->e != NULL) y = y->e;
        return y;
    }
    while(x -> pai != NULL && x->pai->d == x)
        x = x->pai;
    return x->pai;
}

/* 
    14.5.1 Escreva uma função que receba um nó x de uma árvore binária
    e encontre o nó anterior a x na ordem e-r-d
*/

/*anterior com e-r-d*/
noComPai previous(noComPai node)
{
    // supondo d
    if(node -> pai != NULL && node -> pai -> d == node)
        return node->pai;
    // supondo r
    if(node->e!= NULL)
    {
        noComPai y = node->e;
        while(y->d != NULL) 
            y = y->d;
        return y;
    }
    //supondo e
    while(node -> pai != NULL && node->pai->e == node)
        node = node->pai;
    return node->pai;
}

int main(void)
{
    noComPai a,b,c,d,e, p;
    a=newcp(4);b=newcp(2);c=newcp(5);
    d=newcp(1);e=newcp(3);
    a->e=b;b->pai=a;
    a->d=c;c->pai=a;
    b->e=d;b->d=e;
    d->pai=b;e->pai=b;

    /* testando a função de referência */
    p = d;
    int expected[5] = {1,2,3,4,5};
    for (int i = 0; i < 5; i++)
    {
        assert(p -> valor == expected[i]);
        p = next(p);
    }
    assert(p == NULL);

    /* 14.5.1 */
    p = c;
    int expected2[5] = {5,4,3,2,1};
    for (int i = 0; i < 5; i++)
    { 
        assert(p -> valor == expected2[i]);
        p = previous(p);
    }
    assert(p == NULL);

    printf("OK");
}