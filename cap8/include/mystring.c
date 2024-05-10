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

void stringInsertionSort(char *string)
{
    int n = strlen(string);
    int i, j;
    for (i = 1; i < n; i++){
        char x = string[i];
        for (j = i-1; j >= 0 && string[j] > x; j--){
            string[j+1] = string[j];
        }
        string[j+1] = x;
    }
}

int mystrcmplen(char *str1, char *str2)
{
    // adapted from a gemini generated code
    int len1 = strlen(str1);
    int len2 = strlen(str2);

    if (len1 > len2) return 1;
    else if (len1 < len2) return -1;
    else {
        for (int i = 0; i < len1; i++) {
            if (str1[i] < str2[i]) {
                return -1;
            } else if (str1[i] > str2[i]) {
                return 1;
            }
        }
        return 0;
    }
}
