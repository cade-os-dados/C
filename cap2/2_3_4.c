// escrever a soma dos dígitos
// de um número

// solução:
// se o numero tiver 1 digito, retornar o numero
// caso contrario, pegar o resto da divisao por 10 * n
// sendo n o numero de digitos
// e continuar somando...
#include <stdio.h>
#include <math.h>

int ipow(int base, int exp){
    int result = 1;
    while (exp != 0){
        result *= base;
        --exp;
    }
    return result;
}

int soma_digito(int numero, int n, int resultado){
    if (n == 1)
        resultado += numero;
    else if (n > 1){
        int divisor = ipow(10, n-1);
        int resto = numero % divisor;
        resultado += (numero / divisor);
        --n;
        resultado = soma_digito(resto, n, resultado);
    }
    return resultado;
}

int main(){
    int numero = 1234;
    int n = 4;
    int resultado = 0; // Inicialize resultado para zero
    resultado = soma_digito(numero, n, resultado);
    printf("O resultado eh %d\n", resultado);
    return 0;
}