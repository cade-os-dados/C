#pragma once
#include <stdlib.h>
#include "vec.h"

typedef struct Subsets{
    farray *vec;
    struct Subsets *next;
} Subset;

Subset *lnew();