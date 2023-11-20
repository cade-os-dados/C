#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>
#include <assert.h>

struct cel {
    int conteudo;
    struct cel *seg;
};

typedef struct cel celula;

// 4.4 
// Esta função recebe o endereço p de uma célula em sua
// lista encadeada e remove da lista a célula p->seg
// A função supõe que p != NULL e p->seg != NULL
void Remove(celula *p){
    celula *lixo;
    lixo = p -> seg;
    p->seg = lixo->seg;
    free (lixo);
}

// 4.4.1 Critique a seguinte variante da funcao remove
void Remove2(celula *p){
    celula *lixo;
    lixo = p->seg;
    if (lixo->seg == NULL) p->seg = NULL; // ineficiente
    else p->seg = lixo->seg; // adiciona um passo desnecessário
    free(lixo);
}

// 4.4.2 LISTA SEM CABEÇA Escreva uma função que remova uma
// determinada célula de uma célula de uma lista encadeada
// sem cabeça. (Será preciso tomar algumas decisões de projeto
// antes de começar a programar)
void removeSemCabeca(celula *p){
    celula *next = p -> seg;
    p -> conteudo = next -> conteudo;
    p -> seg = next -> seg;
    free (next);
}

// essa foi a solução que cheguei porém talvez para
// linked list sem header teria que ser uma double
// linked list, que armazena o endereço anterior
// e posterior

int main() {
    celula *p = malloc(sizeof(celula));
    celula *p2 = malloc(sizeof(celula));
    p -> conteudo = 2;
    p2 -> conteudo = 10;
    p -> seg = p2;
    p2 -> seg = NULL;

    removeSemCabeca(p); // liberou p2 e copiou p2 para p
    printf("%d", p -> conteudo);
}