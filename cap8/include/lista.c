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
        char *string = loop -> conteudo;
        printf("%s, ", string);
        loop = loop -> seg;
    }
    printf("%s ]\n", loop -> conteudo);
}

celula *busca(int n, celula *inicio){
    celula *loop = inicio;
    for (int i = 0; i < n; i++){
        if (loop -> seg != NULL)
            loop = loop -> seg;
    }
    return loop;
}

void permutacaoCelula(celula *cel1, celula *cel2){
    char *valor1 = cel1 -> conteudo;
    cel1 -> conteudo = cel2 -> conteudo;
    cel2 -> conteudo = valor1;
}

void permutacaoCelulaBusca(int i, int j, celula *inicio){
    celula *cel1 = busca(i, inicio);
    celula *cel2 = busca(j, inicio);
    permutacaoCelula(cel1, cel2);
}

celula *from_array(char **strings, int n){
    celula *inicio = malloc(sizeof(celula));
    celula *loop = inicio;
    loop -> conteudo = strings[0];
    for (int i = 1; i < n; i++){
        loop = next(loop);
        loop -> conteudo = strings[i];
    }
    loop -> seg = NULL;
    return inicio;
}

void assert_eq_celula(celula *cel1, celula *cel2){
    celula *loop1 = cel1;
    celula *loop2 = cel2;
    while (loop1 != NULL && loop2 != NULL){
        assert ( strcmp(loop1 -> conteudo, loop2 -> conteudo) == 0);
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
