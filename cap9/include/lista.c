# include "lista.h"
# include <stdlib.h>
# include <stdio.h>
# include <string.h>
# include <assert.h>

celula *next (celula *atual){
    atual -> seg = malloc(sizeof(celula));
    return atual -> seg;
}

void print_celula(celula *inicio){
    celula *loop = inicio;
    printf("[ ");
    while (loop -> seg != NULL){
        printf("%d ", loop -> conteudo);
        loop = loop -> seg;
    }
    printf("%d ]\n", loop -> conteudo);
}

celula *from_array(int *vec, int n){
    celula *inicio = malloc(sizeof(celula));
    celula *loop = inicio;
    loop -> conteudo = vec[0];
    for (int i = 1; i < n; i++){
        loop = next(loop);
        loop -> conteudo = vec[i];
    }
    loop -> seg = NULL;
    return inicio;
}

void assert_eq_celula(celula *cel1, celula *cel2){
    celula *loop1 = cel1;
    celula *loop2 = cel2;
    while (loop1 != NULL && loop2 != NULL){
        assert ( loop1 -> conteudo == loop2 -> conteudo );
        loop1 = loop1 -> seg;
        loop2 = loop2 -> seg;
    }
}

int lenList(celula *lista){
    int i = 0;
    celula *loop = lista;
    while (loop -> seg != NULL){
        loop = loop -> seg;
        i++;
    }
    return i;
}
