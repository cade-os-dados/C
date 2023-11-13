// Escreva uma função recursiva eficiente que receba inteiros positivos
// k e n e calcule o valor de k^n. Suponha que k^n cabe em um int.
// Quantas multiplicações sua função executa aproximadamente?

#include<stdio.h>

int power(unsigned int k, unsigned int n) {
    unsigned int result;
    if (n == 1) 
        return k;
    else 
        return k * power(k, n-1);
}

int main() {
    unsigned int base = 2; unsigned int exp = 32;
    unsigned int resultado = power(base,exp) - 1;
    printf("Resultado de %u elevado a %u eh: %u", base, exp, resultado);
}