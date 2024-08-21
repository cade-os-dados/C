#pragma once
#include <time.h>
#include <stdio.h>
#include <stdlib.h>

#define benchmark(x) do {\
    clock_t start_time = clock();\
    x;\
    double elapsed_time = (double)(clock() - start_time) / CLOCKS_PER_SEC;\
    printf("Done in %f seconds\n", elapsed_time);\
} while(0)
