
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lista.h"

// https://stackoverflow.com/questions/26620388/c-substrings-c-string-slicing
void slice(const char* str, char* result, size_t start, size_t end)
{
    strncpy(result, str + start, end - start);
}

// https://medium.com/@kkhicher1/how-to-slice-string-in-c-language-7a5fd3a5db46
int strLen(const char str[])
{
    int count = 0;
    while (str[count] != '\0')
    {
        ++count;
    }
    return count;
}

char *sliceString(char *str, int start, int end)
{
    int i;
    int size = end - start + 1;
    char *output = (char *)malloc(size * sizeof(char));

    for (i = 0; start <= end; start++, i++)
    {
        *(output+i) = str[start];
    }
    *(output+i) = '\0';
    return output;
}

celula *nova_celula(char *token){
    celula *nova = malloc(sizeof(celula));
    nova -> conteudo = token;
    return nova;
}

celula *tokenize(char *string){
    int init = 0;
    int final = 0;
    int tamanho = strLen(string);
    celula *primaria = malloc(sizeof(celula)); // com cabeça
    celula *atual = primaria;
    primaria -> seg = atual;
    for (int index=0; index<tamanho; index++){
        if (string[index] == ' ' | index == tamanho-1){
            // depois arrumar isto aqui
            if (index != tamanho - 1)
                final = index - 1;
            else
                final = index;
            char *token = sliceString(string, init, final);
            celula *nova = nova_celula(token);
            atual -> seg = nova;
            atual = nova;
            init = index+1;
        }
    }
    atual -> seg = NULL;
    return primaria;
}

void print_celula(celula *primaria){
    celula *temp = primaria -> seg; // lista com cabeça
    while (temp != NULL) {
        printf("%s ", temp -> conteudo);
        temp = temp -> seg;
    }
    printf("\n");
}