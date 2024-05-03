# include <string.h>
# include <stdlib.h>
# include <stdio.h>
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

celula *teste (char *path, int buffer_size){
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

int main(void){
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

    celula *txt = teste("sample/teste.txt", 1024);
    selecaoLinkedList(txt);
    
    char *temp[3] = {
        stringpointer("hallo welt!"),
        stringpointer("hello world!"),
        stringpointer("ola mundo!")
    };
    celula *expected2 = from_array(temp, 3);
    assert_eq_celula(txt, expected2);

    printf("OK");
}
