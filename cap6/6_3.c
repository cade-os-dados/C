#include <stdio.h>
#include <stdlib.h>
#include <string.h> 

char *InfixaParaPosFixa(char infix[]){
    char *posfix, x;
    char *p; int t;
    int n, i, j;
    n = strlen(infix);
    posfix = malloc(n * sizeof(char));
    p = malloc(n * sizeof(char));
    t = 0; p[t++] = infix[0]; /* empilha '(' */
    for (j=0, i=1; infix[i] != '\0'; i++){
        /* p[0..t-1] é uma pilha de caracteres */
        switch (infix[i]){
            case '(': p[t++] = infix[i]; break;
            case ')': while (1) { 
                    x = p[--t]; 
                    if (x == '(') break; 
                    posfix[j++] = x;}
                break;
            case '+':
            case '-': while (t > 0) {
                    x = p[t-1];
                    if (x == '(') break;
                    --t; /* desempilha */
                    posfix[j++] = x;}
                p[t++] = infix[i]; /* empilha */
                break;
            case '*':
            case '/': while (t > 0) {
                    x = p[t-1];
                    if (x == '(' || x == '+' || x == '-')
                        break;
                    --t;
                    posfix[j++] = x; }
                p[t++] = infix[i];
                break;
            default: posfix[j++] = infix[i]; }
    }
    free (p);
    posfix[j] = '\0';
    return posfix;
}

// 6.3.2 Na função InfixaParaPosfixa, suponha que a string infix tem n caracteres
// (sem contar o caractere nulo final). Que altura a pilha pode atingir, no pior caso?
// Em outras palavras, qual o valor máximo da váriavel t? Que acontece se o número de
// parênteses for limitado (menor que 10, por exemplo)?

// R: t(max) = n/2
// Se for limitado então t(max) = limite/2

// 6.3.3 Reescreva o código da função InfixaParaPosfixa de maneira um pouco mais
// compacta, sem os "while (1)". Tire proveito dos recursos sintáticos da linguagem C.

char *InfixaParaPosFixa2(char infix[]){
    char *posfix, x, *p;
    int t, n, i, j;
    n = strlen(infix);
    posfix = malloc(n * sizeof(char));
    p = malloc(n * sizeof(char));
    t = 0; p[t++] = infix[0]; /* empilha '(' */
    for (j=0, i=1; infix[i] != '\0'; i++){
        /* p[0..t-1] é uma pilha de caracteres */
        switch (infix[i]){
            case '(': p[t++] = infix[i]; break;
            case ')': while ( (x = p[--t]) != '(' ) posfix[j++] = x;
                    break;
            case '+':
            case '-': while (t > 0 && (x = p[t-1]) != '(')
            {   --t; posfix[j++] = x;   }
                p[t++] = infix[i]; /* empilha */
                break;
            case '*':
            case '/': while (t > 0 && (x = p[t-1]) != '+' && x != '-' && x != '(') 
            {   --t; posfix[j++] = x;   }
                p[t++] = infix[i];
                break;
            default: posfix[j++] = infix[i]; }
    }
    free (p);
    posfix[j] = '\0';
    return posfix;
}

// 6.3.4 Reescreva a função InfixaParaPosfixa sem supor que a expressão infixa está
// embrulhada em um par de parênteses

char *InfixaParaPosFixa3(char infix[]){
    char *posfix, x, *p;
    int t, n, i, j;
    n = strlen(infix);
    posfix = malloc(n * sizeof(char));
    p = malloc(n * sizeof(char));
    t = 0;
    for (j=0, i=0; infix[i] != '\0'; i++){
        /* p[0..t-1] é uma pilha de caracteres */
        switch (infix[i]){
            case '(': p[t++] = infix[i]; break;
            case ')': while ( (x = p[--t]) != '(' ) posfix[j++] = x;
                    break;
            case '+':
            case '-': while (t > 0 && (x = p[t-1]) != '(')
            {   --t; posfix[j++] = x;   }
                p[t++] = infix[i]; /* empilha */
                break;
            case '*':
            case '/': while (t > 0 && (x = p[t-1]) != '+' && x != '-' && x != '(') 
            {   --t; posfix[j++] = x;   }
                p[t++] = infix[i];
                break;
            default: posfix[j++] = infix[i]; }
    }
    // caso a expressao finalize com operadores
    while (i != j){
        posfix[j++] = p[--t];
    }
    free (p);
    posfix[j] = '\0';
    return posfix;
}

int main(){
    // 6.3.1 Aplique à expressão infixa (A+B)*D+E/(F+A*D)+C o algoritmo
    // de conversão para notação posfixa
    char expressao[19] = "(A+B)*D+E/(F+A*D)+C";
    char *posfixa = InfixaParaPosFixa(expressao); // nao funciona
    printf("%s", posfixa);

    char expressao2[8] = "(A+B)*C";
    char *posfixa2 = InfixaParaPosFixa2(expressao2);
    printf("\n%s", posfixa2);

    char expressao3[16] = "A+B*C+D*E*F-G/H";
    char *posfixa3 = InfixaParaPosFixa3(expressao3);
    printf("\n%s", posfixa3);
}