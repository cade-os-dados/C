# include "vec.h"
# include <stdlib.h>

void print(int v[], int n){
    printf("[ ");
    for (int i = 0; i < n; i++){
        printf("%d ", v[i]);
    }
    printf("]\n");
}

void assert_eq(int v1[], int v2[], int n){
    for (int i = 0; i < n; i++){
        assert(v1[i] == v2[i]);
    }
}

/* vetor_original deve estar ordenado*/
void unique_copy(int n, int vetor_original[], int vetor_copia[]){
    int j = 1;

    int valor_anterior = vetor_original[0];
    vetor_copia[0] = valor_anterior;
    for (int i = 1; i < n; i++){
        int valor_atual = vetor_original[i];
        if (valor_atual != valor_anterior){
            vetor_copia[j] = valor_atual;
            j++;
        }
        valor_anterior = valor_atual;
    }

}

int *copy_vec (int v[], int n){
    int *resultado = malloc(sizeof(int) * n);
    for (int i = 0; i < n; i++){
        resultado[i] = v[i];
    }
    return resultado;
}

const struct vec libvec = {
    .print = print,
    .assert_eq = assert_eq,
    .unique_copy = unique_copy
};
