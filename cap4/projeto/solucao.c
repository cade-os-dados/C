// 4.7.12 PROJETO DE PROGRAMAÇÃO Digamos que um documento é um vetor
// de caracteres contendo apenas letras, espaços e sinais de pontuação.
// Digamos que uma palavra é um segmento maximal que consiste apenas
// de letras. Escreva uma função que imprima uma relação de todas as palavras
// de um documento dado juntamente com o número de ocorrências de cada palavra.

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct cel {
    char *conteudo;
    struct cel *seg;
};

typedef struct cel celula;

// https://stackoverflow.com/questions/26620388/c-substrings-c-string-slicing
void slice(const char* str, char* result, size_t start, size_t end)
{
    strncpy(result, str + start, end - start);
}

char *collect_substring(char *string, int init, int index){
    int token_length = index-1-init;
    char *token = malloc(sizeof(token_length));
    slice(string, token, init, index);
    return token;
}

celula *new(char *token){
    celula *nova = malloc(sizeof(celula));
    nova -> conteudo = token;
    return nova;
}

celula *tokenize(char *string){
    int init = 0;
    int tamanho = sizeof(string);
    celula *primaria = malloc(sizeof(celula)); // com cabeça
    celula *atual = primaria;
    primaria -> seg = atual;
    for (int index=0; index<tamanho; index++){
        if (string[index] == ' '){
            char *token = collect_substring(string, init, index);
            celula *nova = new(token);
            atual -> seg = nova;
            atual = nova;
            init = index+1;
        }
    }
    atual -> seg = NULL;
    return primaria;
}

void print_celula(celula *primaria){
    celula *temp = primaria;
    while (temp != NULL) {
        printf("%s", temp -> conteudo);
    }
}

int main() {
    // string in heap
    char *greetings = strdup("Hello World!");
    greetings[0] = 'J';
    printf("%s", greetings);
    celula *primaria = tokenize(greetings);
    print_celula(primaria);
}