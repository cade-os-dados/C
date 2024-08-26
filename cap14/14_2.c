#include "no.h"
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

void erd(no r)
{
    if(r != NULL)
    {
        erd(r->e);
        printf("%d\n", r->valor);
        erd(r->d);
    }
}

/*14.2.1 Encontre um nó com conteúdo k em uma árvore binária*/
no treesearch(no r, int k)
{
    if (r != NULL)
    {
        if(r->valor == k)
            return r;
        else
        {
            if (r->e != NULL)
            {
                no esquerdo = treesearch(r->e, k);
                if (esquerdo != NULL)
                    return esquerdo;
            }
            if (r -> d != NULL)
            {
                no direito = treesearch(r->d, k);
                if (direito != NULL)
                    return direito;
            }
        }
    }
    return NULL;
}

/* 14.2.2 Calcule o número de nós de uma árvore binária */
void count(no arv, int* contagem)
{
    (*contagem)++;
    if (arv -> e != NULL)
        count(arv -> e, contagem);
    if (arv -> d != NULL)
        count(arv -> d, contagem);
}

/* 14.2.3 Imprima as folhas de uma árvore binária em ordem e-r-d*/
void imprime_folhas(no arv)
{
    int c = 0;
    if ((arv -> d) != NULL) imprime_folhas(arv -> d);
    else c++;
    if ((arv -> e) != NULL) imprime_folhas(arv -> e);
    else c++;
    if (c == 2) printf("%d ", arv -> valor);
}

void imprime_folhas_with_brackets(no arv)
{
    printf("{ ");
    imprime_folhas(arv);
    printf("}\n");
}

int main(void)
{
    no t = malloc(sizeof(arvore));
    no_malloc_child(t);
    no_append_child_null(t -> e);
    no_append_child_null(t -> d);
    t -> valor = 5; 
    t -> e -> valor = 10; 
    t -> d -> valor = 12;

    assert(treesearch(t,12) != NULL);
    assert(treesearch(t,8) == NULL);

    int c = 0;
    count(t, &c);
    assert(c == 3);

    imprime_folhas_with_brackets(t);

    printf("OK");
}