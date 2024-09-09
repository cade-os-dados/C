#pragma once

#include <stdlib.h>

typedef struct sfarr
{
    int* array;
    int n;
} safeArray;

typedef safeArray* safeArrayPtr;

int safecmp(safeArray a, safeArray b);
safeArray safenew(int* vetor, int n);
void safeswap(safeArrayPtr sp, int i, int j);
int safepart(safeArrayPtr sp, int left, int right);
void safeqsort(safeArrayPtr sp, int left, int right);
int _compare(const void* a, const void* b);
void safeqsortElements(safeArrayPtr sp, int n);