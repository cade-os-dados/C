# include "mystring.h"
# include <stdlib.h>
# include <string.h>
# include <stdio.h>
# include <assert.h>

char *stringpointer(char raw_string[]){
    int len = strlen(raw_string);
    char *pointer = malloc(sizeof(char) * len+1);
    for (int i = 0; i < len; i++){
        pointer[i] = raw_string[i];
    }
    pointer[len] = '\0';
    return pointer;
}

void print_texts(int n, char *texts[]){
    printf("{ ");
    for (int i=0; i < 3; i++){
        printf("%s ", texts[i]);
    }
    printf("}\n");
}

void assert_vecstring(char *strings1[], char *strings2[], int n){
    for (int i = 0; i < n; i++){
        assert( strcmp(strings1[i], strings1[i]) == 0 );
    }
}
