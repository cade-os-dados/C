#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>
#include "include/pilha.h"

typedef struct cel {
    int valor;
    struct cel *seg;
} celula;

// supomos lista com cabeça
// topo da pilha na segunda célula

celula *nova(){
    celula cabeca;
    celula *p;
    p = &cabeca;
    p -> seg = NULL;
    return p;
}

void empilha(int y, celula *p){
    celula *nova;
    nova = malloc(sizeof(celula));
    nova -> valor = y;
    nova -> seg = p -> seg;
    p -> seg = nova;
}

int desempilha(celula *p){
    int x; celula *q;
    q = p -> seg;
    x = q -> valor;
    p -> seg = q -> seg;
    free (q);
    return x;
}

// 6.4.1 Implemente uma pilha em uma lista encadeada sem celula-cabeca.
// A pilha será especificada pelo endereço da primeira celula da lista
typedef struct celu {
    int value;
    struct celu *anterior;
} pilha;

pilha *push(int y, pilha *last){
    pilha *nova = malloc(sizeof(pilha));
    nova -> value = y;
    nova -> anterior = last;
    return nova;
}

pilha *pop(pilha *last, int *valor){
    pilha *resultado = last -> anterior;
    *valor = last -> value;
    free (last);
    return resultado;
}

pilha *init(int value){
    pilha *stack = malloc(sizeof(pilha));
    stack -> anterior = NULL;
    stack -> value = value;
    return stack;
}

void print_pilha(pilha *stack){
    pilha *loop = stack;
    printf("[ ");
    while (loop != NULL) {
        printf("%d ", loop -> value);
        loop = loop -> anterior;
    }
    printf("]\n");
}

// 6.4.2 Reescreva as funções BemFormada e InfixaParaPosfixa
// (Seções 6.2 e 6.3 respectivamente) armazenando a pilha
// em uma lista encadeada
int BemFormada (char s[]) {
    int nula, i;
    stack *p = nova_pilha();
    for (int i = 0; s[i] != '\0'; i++)
    {
        nula = vazia(p);
        switch (s[i])
        {
            case ')': 
                if (nula != 1 && p -> value == '(')
                    desempilhar(&p);
                else return 0; 
                break;
            case '}': 
                if (nula != 1 && p -> value == '{')
                    desempilhar(&p);
                else return 0;
                break;
            case '{':
            case '(':
                p = empilhar(p, s[i]);
                break;
            default:
                continue;
        }
    }
    nula = vazia(p);
    return nula == 1;
}

char* null_char(char* string){
    string[0] = '\0';
    return string;
}

int is_in(char value, char values[], int n){
    for (int i = 0; i < n; i++){
        if (value == values[i]) return 1;
    }
    return 0;
}

char *InfixaParaPosFixa5(char infix[]){
    // declarando as variaveis e validando
    // se a sequencia é bem formada
    int bem_formada = BemFormada(infix);
    if (bem_formada != 1) return null_char(infix);

    char *posfix, x;
    int i, j;
    stack *p = nova_pilha();
    posfix = malloc(strlen(infix) * sizeof(char));
    char key_operators[3] = {'-', '(', '{'};
    for (j=0, i=0; infix[i] != '\0'; i++){
        switch (infix[i]){
            case '{':
            case '(': p = empilhar(p, infix[i]); break;
            case '}': while ( (vazia(p) != 1) && (x = desempilhar(&p) ) != '{' ) posfix[j++] = x;
                    break;
            case ')': while ( (vazia(p) != 1) && (x = desempilhar(&p) ) != '(' ) posfix[j++] = x;
                    break;
            case '+':
            case '-': while ( (vazia(p) != 1) && (x = p -> value) != '(' && x != '{')
            { desempilhar(&p); posfix[j++] = x; }
                p = empilhar(p, infix[i]);
                break;
            case '*':
            case '/': while ((vazia(p) != 1) && (x = p -> value) != '+' && is_in(x, key_operators, 3) == 0)
            { desempilhar(&p); posfix[j++] = x; }
                p = empilhar(p, infix[i]);
                break;
            default: posfix[j++] = infix[i]; }
    }
    // caso a expressao finalize com operadores
    while ( (i != j) && (vazia(p) != 1) ){
        posfix[j++] = desempilhar(&p);
    }
    free (p);
    posfix[j] = '\0';
    return posfix;
}

// retorna 1 se todos os caracteres forem iguais em
// ambas as strings, se não retorna 0
int match_chars(char string[], char string2[]){
    int n = 0, matches = 0;
    char p = string[n];
    while (p != '\0'){
        p = string[n];
        matches += (p == string2[n]);
        n++;
    }
    return matches == n;
}

int main(){
    pilha *stack = init(5);
    stack = push(10, stack);
    stack = push(15, stack);
    print_pilha(stack);

    int valor;
    stack = pop(stack, &valor);
    print_pilha(stack);
    printf("Valor popped out: %d\n", valor);

    stack = pop(stack, &valor);
    print_pilha(stack);
    printf("Valor popped out: %d\n", valor);

    // testes questao 6.4.2
    assert(BemFormada("{(})") == 0);
    assert(BemFormada("({})") == 1);
    assert(BemFormada("(}") == 0);
    assert(BemFormada("(") == 0);
    assert(BemFormada("()") == 1);

    // expressoes corretas
    char expressao[8] = "(A+B)*C";
    char expressao2[16] = "A+B*C+D*E*F-G/H";
    char expressao3[17] = "A+B*(C+D)*E*F-G/H";
    char expressao4[20] = "{(A+B)*C+D}*E*F-G/H";

    char *posfixa = InfixaParaPosFixa5(expressao);
    char *posfixa2 = InfixaParaPosFixa5(expressao2);
    char *posfixa3 = InfixaParaPosFixa5(expressao3);
    char *posfixa4 = InfixaParaPosFixa5(expressao4);

    assert(match_chars(posfixa, "AB+C*") == 1);
    assert(match_chars(posfixa2, "ABC*+DE*F*+GH/-") == 1);
    assert(match_chars(posfixa3, "ABCD+*E*F*+GH/-") == 1);
    assert(match_chars(posfixa4, "AB+C*D+E*F*GH/-") == 1);

    // expressoes incorretas
    char expressao_errada[16] = "A+B*C+D*)E*F-G/H";
    char expressao_errada2[16] = "A+B*C+D*(E*F-G/H";
    char expressao_errada3[17] = "A+B*C+D*((E*F-G/H";
    char expressao_errada4[17] = "A+B*C+D*{(E*F-G/H";
    char expressao_errada5[17] = "A+B*C+D*{)E*F-G/H";
    char expressao_errada6[17] = "A+B*C+D*(}E*F-G/H";
    char expressao_errada7[19] = "{(A+B}*C)+D*E*F-G/H";

    char *posfixa5 = InfixaParaPosFixa5(expressao_errada);
    char *posfixa6 = InfixaParaPosFixa5(expressao_errada2);
    char *posfixa7 = InfixaParaPosFixa5(expressao_errada3);
    char *posfixa8 = InfixaParaPosFixa5(expressao_errada4);
    char *posfixa9 = InfixaParaPosFixa5(expressao_errada5);
    char *posfixa10 = InfixaParaPosFixa5(expressao_errada6);
    char *posfixa11 = InfixaParaPosFixa5(expressao_errada7);

    assert(posfixa4[0] != '\0'); assert(posfixa5[0] == '\0');
    assert(posfixa6[0] == '\0'); assert(posfixa7[0] == '\0'); 
    assert(posfixa8[0] == '\0'); assert(posfixa9[0] == '\0'); 
    assert(posfixa10[0] == '\0'); assert(posfixa11[0] == '\0'); 
}