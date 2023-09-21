#include <stdio.h>

int log2n_iterativa(int n){
    int contagem = 0;
    double resultado = n;
    while (resultado >= 2){
        contagem++;
        resultado = resultado / 2;
    }
    return contagem;
}

int log2n_recursiva(int n, int contagem){
    if (n >= 2){
        contagem ++;
        log2n_recursiva(n/2, contagem);
    }
    else
        return contagem;
}

int main(){
    int numero = 127;
    int resultado = log2n_iterativa(numero);
    printf("O resultado da funcao iterativa eh %d \n", resultado);
    int contagem = 0;
    int resultado2 = log2n_recursiva(numero, contagem);
    printf("O resultado da funcao recursiva eh %d", resultado2);
}