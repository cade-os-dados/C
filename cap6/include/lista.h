#include <stdlib.h>

struct cel {
    char *conteudo;
    struct cel *seg;
};

typedef struct cel celula;

int contagem(celula *primaria){
    celula *temp = primaria;
    int contagem = 1; // para listas com cabeça seria 0
    while (temp -> seg != NULL){
        temp = temp -> seg;
        contagem++;
    }
    return contagem;
}

char *to_vec(char *v[], celula *primaria){
    celula *temp = primaria;
    int indice = 0;
    while (temp != NULL) {
        v[indice] = temp -> conteudo;
        temp = temp -> seg; indice++;
    }
}