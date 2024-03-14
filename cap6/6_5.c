#include <stdlib.h>
#include <stdio.h>
#include "include/intpilha.h"
#include <assert.h>

// exemplo livro
int G (int a, int b){
    return a+b;
}
int F (int i, int j, int k){
    int x;
    x = /*2*/ G(i,j) /*3*/;
    return x+k;
}

// coloquei como comentario para nao atrapalhar a execucao do exercicio
// int main(void){
//     int i, j, k, y;
//     i = 111; j = 222; k = 444;
//     y = /*1*/ F(i, j, k) /*4*/;
//     printf("%d\n", y);
//     return EXIT_SUCCESS;
// }

// pilha de execucao
// em 1 -> as variáveis i, j, k e y são inicializadas
// e a funcao main é iniciada
// na chamada da função F, main é suspensa e entra em F
// então F é colocado na pilha e inicializada junto
// aos parametros i, j, k e a variável (local) x
// em 2, o mesmo ocorre, G é colocado na pilha, as
// suas variáveis são inicializadas e F suspensa
// após isto, a função devolve 333 e G é removido da pilha
// e assim por diante até que a função main seja encerrada

// 6.5.1 Escreva uma função iterativa que simule o
// comportamento da função recursiva abaixo. Use uma pilha.
int TTT(int x[], int n){
    if (n==0) return 0;
    if (x[n] > 0) return x[n] + TTT(x, n-1);
    else return TTT(x, n-1);
}

int TTT_iter(int x[], int n){
    intPilha *pilha = nova_pilha(); // inicia com 0
    int resultado = pilha -> value;
    for (int i = n; i > 0; i--){
        resultado = (x[i] > 0) * x[i];
        resultado = resultado + desempilhar(&pilha);
        pilha = empilhar(pilha, resultado);
    }
    free(pilha);
    return resultado;
}

int main(){
    int exemplo[6] = {1,2,-3,4,5,6};
    int n = 6;
    int resultado = TTT(exemplo, n);
    int comparar = TTT_iter(exemplo, n);
    assert(resultado == comparar);
}