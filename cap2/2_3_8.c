// o livro só pede para executar a funcao abaixo
// com argumentos 7 e 0
#include <stdio.h>

int ff(int n, int ind){
    int i;
    for (i=0; i < ind; i++)
        printf(" ");
    printf("ff (%d, %d)\n", n, ind);
    // se for 1 finaliza
    if (n == 1)
        return 1;
    // se for par divide n/2 e aumenta o espaçamento do print
    if (n % 2 == 0)
        return ff(n/2,ind+1);
    // se for ímpar vai continuar com com as duas opções (n+1)/2 e (n-1)/2
    return ff((n-1)/2,ind+1) + ff((n+1)/2,ind+1);
}

int main(){
    ff(7,0);
}