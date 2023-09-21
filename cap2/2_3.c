#include <stdio.h>
#include "include/min_max.h"

//2.3.1
// este algoritmo faz uma comparação par a par
// de trás para frente, verificando
// qual o maior valor entre os pares
// resultando o valor máximo do vetor
int maximo2r(int v[], int n){
    int x;
    if (n==1) 
        return v[0];
    // faz um slice de uma unidade no vetor
    // e aplica a função de máximo
    x = maximo2r(v+1,n-1); 
    printf("x: %d v[0]: %d\n",x,v[0]);
    // compara o primeiro elemento do vetor
    // com o elemento máximo
    if (x > v[0])
        return x;
    return v[0];
}

int main(int argc, char *argv[]) {
    int v[] = {23,89,56,54,1,9,5,121,554,9,9995,56,1321,3654,46,654,4,31,654, -52};
    int tamanho = sizeof(v) / sizeof(v[0]);
    int valida_maximo = 9995;
    int maximo = maximo2r(v, tamanho);
    if (valida_maximo == maximo)
        printf("Passou no teste!\n");
    else
        printf("Não passou no teste!\n");

    int resultado[2];
    min_max(v, tamanho, resultado);
    printf("A diferenca do maior para o menor eh %d\n", resultado[1] - resultado[0]);
    getchar();
}