#pragma once
#include <stdlib.h>

struct cel {
    int chave;
    int conteudo;
    struct cel* e;
    struct cel* d;
};
typedef struct cel no;
typedef no* arvore;

void fillno(arvore r, int chave, arvore e, arvore d)
{
    r->chave = chave;
    r->e=e;
    r->d=d;
}