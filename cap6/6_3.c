#include <stdio.h>
#include <stdlib.h>
#include <string.h> 
#include <assert.h>
#include "include/bemformada.h"

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
    while (i != j & t > 0){
        posfix[j++] = p[--t];
    }
    free (p);
    posfix[j] = '\0';
    return posfix;
}

// 6.3.5 Reescreva a função InfixaParaPosfixa supondo que a expressão infixa
// pode estar incorreta

// OBS: uma alternativa seria assertar se é bem formada utilizando uma função específica

char *InfixaParaPosFixa4(char infix[]){
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
            case ')': while ( (x = p[--t]) != '(' && t >= 0 ) posfix[j++] = x;
                if (x != ')' && x != '(' ) {
                    printf("\nWrong synxtax! Your sequence isnt well-formed...");
                    free (p);
                    posfix[0] = '\0';
                    return posfix;
                }
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
    while (i != j & t > 0){
        posfix[j++] = p[--t];
        if (p[t] == '(') {
            printf("\nWrong synxtax! Your sequence isnt well-formed...");
            free (p);
            posfix[0] = '\0';
            return posfix;
        }
    }
    free (p);
    posfix[j] = '\0';
    return posfix;
}

// 6.3.6 Reescreva a função InfixaParaPosfixa supondo que a expressão
// pode ter parênteses e chaves

char* null_char(char* string){
    string[0] = '\0';
    return string;
}

char *InfixaParaPosFixa5(char infix[]){

    // declarando as variaveis e validando
    // se a sequencia é bem formada
    char *posfix, x, *p;
    int bem_formada = BemFormada(infix);
    if (bem_formada != 1) return null_char(infix);

    int t, n, i, j;
    n = strlen(infix);
    posfix = malloc(n * sizeof(char));
    p = malloc(n * sizeof(char));
    t = 0;
    for (j=0, i=0; infix[i] != '\0'; i++){
        /* p[0..t-1] é uma pilha de caracteres */
        switch (infix[i]){
            case '{':
            case '(': p[t++] = infix[i]; break;
            case '}': while ( (x = p[--t]) != '{' && t >= 0 ) posfix[j++] = x;
                    break;
            case ')': while ( (x = p[--t]) != '(' && t >= 0 ) posfix[j++] = x;
                    break;
            case '+':
            case '-': while (t > 0 && (x = p[t-1]) != '(' && x != '{')
            {   --t; posfix[j++] = x;   }
                p[t++] = infix[i]; /* empilha */
                break;
            case '*':
            case '/': while (t > 0 && (x = p[t-1]) != '+' && x != '-' && x != '(' && x != '{') 
            {   --t; posfix[j++] = x;   }
                p[t++] = infix[i];
                break;
            default: posfix[j++] = infix[i]; }
    }
    // caso a expressao finalize com operadores
    while (i != j & t > 0){
        posfix[j++] = p[--t];
    }
    free (p);
    posfix[j] = '\0';
    return posfix;
}

// 6.3.7 VALOR DE EXPRESSÃO POSFIXA. Suponha dada uma expressão aritmética
// em notação posfixa sujeita às seguintes restrições: cada variável consiste
// em uma única letra do conjunto A..Z; não há constantes; os únicos operadores
// são +, -, *, / (todos exigem dois operandos). Suponha dado também um vetor
// inteiro val, indexado por A..Z, que dá os valores das variáveis. Escreva
// uma função que calcule o valor da expressão. Cuidado com divisões por zero.

// ler da esquerda para a direita
// armazenar os resultados das operações par a par
// em uma stack 

// esta funcao recebe um vetor com valores
// o qual será retornado o valor referente
// a letra índice A..Z, 
// sendo A indice 0, Z indice 25
int transform(int valores[], char letra){
    int indice = (int) letra - 65;
    return valores[indice];
}

int evaluate(char* expression){
    int n = strlen(expression);
    int resultado, operando;
    int t = 0;
    for (int i = n; i >= 0; i--){
        switch (expression[i])
        {
        case '*':
            resultado = resultado * operando;
            t--;
        case '/':
            resultado = resultado / operando;
            t--;
        case '+':
            resultado = resultado + operando;
            t--;
        case '-':
            resultado = resultado - operando;
            t--;
        default:
            operando = expression[i];
            break;
        }
    }
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

    char expressao4[17] = "A+B*(C+D)*E*F-G/H";
    char *posfixa4 = InfixaParaPosFixa3(expressao4);
    printf("\n%s", posfixa4);

    char expressao_errada[16] = "A+B*C+D*)E*F-G/H";
    char *posfixa5 = InfixaParaPosFixa4(expressao_errada);
    if (posfixa5[0] != '\0') printf("\n%s", posfixa5);

    char expressao_errada2[16] = "A+B*C+D*(E*F-G/H";
    char *posfixa6 = InfixaParaPosFixa4(expressao_errada2);
    if (posfixa6[0] != '\0') printf("\n%s", posfixa6);

    char expressao_errada3[17] = "A+B*C+D*((E*F-G/H";
    char *posfixa7 = InfixaParaPosFixa4(expressao_errada3);
    if (posfixa7[0] != '\0') printf("\n%s", posfixa7);

    char expressao5[20] = "{(A+B)*C+D}*E*F-G/H";
    char *posfixa8 = InfixaParaPosFixa5(expressao5);
    if (posfixa8[0] != '\0') printf("\n%s", posfixa8);

    // tests
    char expressao_errada4[17] = "A+B*C+D*{(E*F-G/H";
    char expressao_errada5[17] = "A+B*C+D*{)E*F-G/H";
    char expressao_errada6[17] = "A+B*C+D*(}E*F-G/H";
    char expressao_errada7[19] = "{(A+B}*C)+D*E*F-G/H";
    char *posfixa9 = InfixaParaPosFixa5(expressao_errada4);
    char *posfixa10 = InfixaParaPosFixa5(expressao_errada5);
    char *posfixa11 = InfixaParaPosFixa5(expressao_errada6);
    char *posfixa12 = InfixaParaPosFixa5(expressao_errada7);
    assert(posfixa9[0] == '\0'); assert(posfixa10[0] == '\0'); 
    assert(posfixa11[0] == '\0'); assert(posfixa12[0] == '\0');

    int vetor[5] = {1,2,3,4,5};
    char letra = 'A';
    assert(transform(vetor, letra) == 1);
}