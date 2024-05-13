# include <string.h>
# include <stdlib.h>
# include <stdio.h>
# include <assert.h>
#include <ctype.h>
# include "include/vec.h"
# include "include/mystring.h"
# include "include/lista.h"

/* 8.4.1 ORDENAÇÃO DE STRINGS. Escreva uma função que coloque
* um vetor de strings em ordem lexicográfica (veja Seção G.3).
* Faça duas versões: uma baseada no algoritmo de inserção e 
* outra baseada no algoritmo de seleção */

void insercao (int n, char *strings[])
{
    int i, j;
    for (i = 1; i < n; i++){
        char *x = strings[i];
        for (j = i-1; j >= 0 && strcmp(strings[j], x) > 0; j--){
            strings[j+1] = strings[j];
        }
        strings[j+1] = x;
    }
}

void permutacao (int i, int j, char *strings[]){
    char *cache = strings[i];
    strings[i] = strings[j];
    strings[j] = cache;
}

void selecao (int n, char *strings[]){
    for (int i = 0; i < n; i++){
        char *texto = strings[i];
        int indice = i;
        for (int j = i; j < n; j++){
            if (strcmp(strings[j], texto) < 0){
                texto = strings[j];
                indice = j;
            }      
        }
        permutacao(indice, i, strings);
    }
}

/* 8.4.2 ORDENAÇÃO DE ARQUIVO. Escreva uma função que rearranje as linhas de um arquivo.
* (veja Apêndice H) em ordem lexicográfica (veja Seção G.3). Compare com o utilitário
* sort presente em todo sistema UNIX e GNU/Linux. */

celula *leituraArquivo (char *path, int buffer_size){
    FILE *entrada = fopen (path, "r");
    int i = 0;
    char c;
    celula *inicial = malloc(sizeof(celula));
    celula *loop = inicial;
    char *buffer = malloc(buffer_size);

    while ((c = getc(entrada)) != EOF) {
        if (c == '\n'){
            buffer[i] = '\0';
            loop -> conteudo = buffer;
            loop = next(loop);
            buffer = malloc(buffer_size);
            i = 0;
        } else {
            buffer[i] = c;
            // aloca mais memória caso o buffer nao seja grande suficiente...
            if ( (i + 1) % buffer_size != 0)
                buffer = realloc(buffer, i+buffer_size);
            i++;
        }
    };
    fclose(entrada);
    buffer[i] = '\0';
    loop -> conteudo = buffer;
    loop -> seg = NULL;
    return inicial;
}

void selecaoLinkedList (celula *strings)
{
    celula *loop_externo = strings;
    
    while (loop_externo != NULL)
    {
        celula *loop_interno = loop_externo;
        
        celula *replace = loop_interno;
        char *x = replace -> conteudo;

        while (loop_interno -> seg != NULL)
        {
            loop_interno = loop_interno -> seg;
            if (strcmp(x, loop_interno -> conteudo) > 0){
                replace = loop_interno;
                x = replace -> conteudo;
            }    
        }
        permutacaoCelula(loop_externo, replace);
        loop_externo = loop_externo -> seg;
    }
}

/* 8.4.3 ORDENAÇÃO DE STRUCTS. Suponha que cada elemento de um vetor
* é um registro que consiste em um inteiro e uma string:
*   struct elem {int i; char *s;};
* Escreva uma função que rearranje o vetor de modo que os campos
* i fiquem em ordem crescente. Escreva outra função que rearranje
* o vetor de modo que os campos s fiquem em ordem lexicográfica 
* (veja Seção G.3). */

typedef struct elem {int i; char *s;} elemento;

void insercaoElemento (int n, elemento *elem[])
{
    int k, j;
    for (k = 1; k < n; k++){
        elemento *x = elem[k]; 
        for (j = k-1; j >= 0 && elem[j] -> i > x -> i; j--){
            elem[j+1] = elem[j];
        }
        elem[j+1] = x;
    }
}

void insercaoElementoLexicografico (int n, elemento *elem[])
{
    int k, j;
    for (k = 1; k < n; k++){
        elemento *x = elem[k]; 
        for (j = k-1; j >= 0 && strcmp(elem[j] -> s, x -> s) > 0; j--){
            elem[j+1] = elem[j];
        }
        elem[j+1] = x;
    }
}

elemento *newElem (int i, char *s){
    elemento *new = malloc(sizeof(elemento));
    new -> i = i;

    int len = strlen(s) + 1;
    new->s = malloc(len * sizeof(char));
    strncpy(new->s, s, len);
    new -> s[len] = '\0';
    return new;
}

/* 8.4.4 ORDENAÇÃO DE LISTA ENCADEADA. Escreva uma função que ordene uma lista
* encadeada. Inspire-se no algoritmo de ordenação por inserção. Faça duas versões:
* uma para lista com cabeça e outra para lista sem cabeça (Sua função precisa devolver 
* alguma coisa?). Repita o exercício com base no algoritmo de ordenação por seleção. */

void insercaoLinkedList (celula *strings)
{
    int j;
    int tamanho = lenList(strings) + 1;
    
    for (int i = 1; i < tamanho; i++)
    {
        char *x = busca(i, strings) -> conteudo;
        for (j = i-1; j >= 0 && strcmp(busca(j, strings) -> conteudo, x) > 0; j--){
            busca(j+1, strings) -> conteudo = busca(j, strings) -> conteudo;
        }
        busca(j+1, strings) -> conteudo = x;
    }
}

/* 8.4.5 PROJETO DE PROGRAMAÇÃO. Digamos que duas palavras são equivalentes se
* uma é anagrama da outra, ou seja, se a sequência de letras de uma é permutação da
* sequência de letras da outra. Por exemplo, "aberto" e "rebato" são equivalentes
* Uma classe de equivalência de palavras é um conjunto de palavras duas a duas equivalentes.
* Escreva um programa que receba um arquivo de palavras (uma palavra por linha) e extraia
* desse arquivo uma classe de equivalência de tamanho máximo. Aplique o seu programa ao arquivo
* de palavras www.ime.usp.br/pf/algoritmos/dicios que contém todas as palavras do português
* falado no Brasil (o arquivo foi extraído do Dicionário br.ispell[20]) */

int anagrama(char *strptr1, char *strptr2)
{
    int len1 = strlen(strptr1);
    int len2 = strlen(strptr2);

    if (len1 != len2) return 0;

    // allocate memory
    char *strptr1_copy = malloc(sizeof(char) * len1);
    char *strptr2_copy = malloc(sizeof(char) * len2);

    // copy
    strcpy(strptr1_copy, strptr1);
    strcpy(strptr2_copy, strptr2);

    // sort
    stringInsertionSort(strptr1_copy);
    stringInsertionSort(strptr2_copy);

    // comparison
    for (int i = 0; i < len1; i++){
        if (strptr1_copy[i] != strptr2_copy[i]) return 0;
    }

    // if pass all check they are equals
    return 1;
}

/* Pegar as celulas de strings, dar um sort nisso,
* em seguida, iterar para verificar se a celula seguinte
* tem o mesmo anagrama da atual, se sim somar, se não
* adicionar a contagem, indice inicial
* numa lista ligada, para depois verificar qual 
* anagrama que mais se repete */

typedef struct contador {
    char *anagrama;
    int contagem;
    struct contador *next;
} counter;

counter *newCounter(char *anagrama, int contagem){
    counter *novo = malloc(sizeof(counter));
    novo -> anagrama = anagrama;
    novo -> contagem = contagem;
    novo -> next = NULL;
    return novo;
}

/* variacao do selection sort mas que antes 
* de considerar a ordem lexicográfica
* considera o tamanho da string*/
void sortStringsByLen (celula *strings)
{    
    char *x;
    celula *loop_interno, *replace;

    int contador = 0;
    celula *loop_externo = strings;

    while (loop_externo != NULL)
    {
        loop_interno = loop_externo;
        replace = loop_interno;
        x = replace -> conteudo;

        while (loop_interno -> seg != NULL)
        {
            loop_interno = loop_interno -> seg;
            if (mystrcmplen(x, loop_interno -> conteudo) > 0){
                replace = loop_interno;
                x = replace -> conteudo;
            }    
        }
        permutacaoCelula(loop_externo, replace);

        // index++
        loop_externo = loop_externo -> seg;
        
        // debug
        contador++;
        if (contador % 50 == 0){
            printf("%d strings processed\n", contador);
        }
    }
}

counter *contagemAnagramas(celula *strings){

    counter *anagramasHead = malloc(sizeof(counter));
    counter *anagramas = anagramasHead;

    int contagem = 1;
    int len = lenList(strings);
    
    celula *loop = strings;
    char *strptr;

    for (int i = 1; i < len; i++){
        if (i % 50 == 0){
            float percentual = i/ (float)len;
            printf("Processed: %.2f %\n", percentual);
        }

        strptr = loop -> conteudo;
        if (anagrama(strptr, loop -> seg -> conteudo) == 1){
            contagem++;
        } else {
            anagramas -> next = newCounter(strptr, contagem);
            anagramas = anagramas -> next;
            contagem = 1;
        }
        loop = loop -> seg;
    }
    return anagramasHead;
}

counter *topEquivalencia(counter *anagramas){
    counter *loop = anagramas;
    counter *top = loop;
    while (loop -> next != NULL){
        if (loop -> contagem > top -> contagem){
            top = loop;
        }
        loop = loop -> next;
    }
    return top;
}

void lower(celula *strings){
    celula *loop = strings;
    while (loop -> seg != NULL){
        char *strptr1 = loop -> conteudo;
        int tamanho = strlen(strptr1);
        for(int i = 0; i < tamanho; i++){
            strptr1[i] = tolower(strptr1[i]);
        }
        loop = loop -> seg;
    }
}


int main(void){

    const int BUFFER_SIZE = 1024;

    char *texts[3] = { 
        stringpointer("banana"), 
        stringpointer("abacate"), 
        stringpointer("sorvete") 
    };
    char *texts2[3] = {
        stringpointer("sorvete"),
        stringpointer("banana"),
        stringpointer("abacate")
    };

    char *expected[3] = { 
        stringpointer("abacate"),
        stringpointer("banana"), 
        stringpointer("sorvete") 
    };

    insercao(3, texts);
    assert_vecstring(texts, expected, 3);

    selecao(3, texts2);
    assert_vecstring(texts2, expected, 3);

    celula *txt = leituraArquivo("sample/teste.txt", BUFFER_SIZE);
    selecaoLinkedList(txt);
    
    char *temp[3] = {
        stringpointer("hallo welt!"),
        stringpointer("hello world!"),
        stringpointer("ola mundo!")
    };
    celula *expected2 = from_array(temp, 3);
    assert_eq_celula(txt, expected2);

    elemento *elem[3] = {
        newElem(2, "a"),
        newElem(0, "b"),
        newElem(1, "c")
    };

    insercaoElemento(3, elem);

    assert(elem[0] -> i == 0 && strcmp(elem[0] -> s, "b") == 0);
    assert(elem[1] -> i == 1 && strcmp(elem[1] -> s, "c") == 0);
    assert(elem[2] -> i == 2 && strcmp(elem[2] -> s, "a") == 0);

    insercaoElementoLexicografico(3, elem);

    assert(elem[0] -> i == 2 && strcmp(elem[0] -> s, "a") == 0);
    assert(elem[1] -> i == 0 && strcmp(elem[1] -> s, "b") == 0);
    assert(elem[2] -> i == 1 && strcmp(elem[2] -> s, "c") == 0);


    // 8.4.4
    char *init[3] = {
        stringpointer("ordenar"),
        stringpointer("string"),
        stringpointer("lexicograficamente")
    };

    celula *sample = from_array(init, 3);

    char *temp2[3] = {
        stringpointer("lexicograficamente"),
        stringpointer("ordenar"),
        stringpointer("string")
    };

    celula *expected3 = from_array(temp2, 3);

    insercaoLinkedList(sample);
    assert_eq_celula(sample, expected3);

    // 8.4.5
    char *string_sample1 = stringpointer("banana");
    char *string_sample2 = stringpointer("maca");
    char *string_sample3 = stringpointer("nanaba");

    assert (anagrama(string_sample1, string_sample2) == 0);
    assert (anagrama(string_sample1, string_sample3) == 1);
    assert (anagrama(string_sample2, string_sample3) == 0);

    celula *txt2 = leituraArquivo("sample/anagramas.txt", BUFFER_SIZE);
    assert(lenList(txt2) == 245365);
    lower(txt2);
    sortStringsByLen(txt2);
    counter *anagramas = contagemAnagramas(txt2);
    counter *top_anagrama = topEquivalencia(anagramas);

    printf(
        "O anagrama de maior equivalencia eh: %s \n Contagem Equivalentes: %d\n", 
        top_anagrama -> anagrama, 
        top_anagrama -> contagem
    );

    printf("OK");
}
