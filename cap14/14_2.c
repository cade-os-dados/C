#include "no.h"
#include <stdlib.h>
#include <stdio.h>

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
no treesearch(no r, int valor)
{
    if (r != NULL)
    {
        if(r->valor == valor)
            return r;
        else
        {
            if (r->e != NULL)
            {
                no esquerdo = treesearch(r->e, valor);
                if (esquerdo != NULL)
                    return esquerdo;
            }
            if (r -> d != NULL)
            {
                no direito = treesearch(r->d, valor);
                if (direito != NULL)
                    return direito;
            }
        }
    }
    return NULL;
}



int main(void)
{
    no t = malloc(sizeof(arvore));
    t -> e = malloc(sizeof(arvore));
    t -> d = malloc(sizeof(arvore));
    t -> valor = 5;
    t -> e -> valor = 10;
    t -> d -> valor = 12;
    no find = treesearch(t, 12);
    if (find != NULL)
        printf("Achou");
}