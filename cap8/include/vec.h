# include <stdio.h>
# include <assert.h>

int *copy_vec (int[], int);

struct vec {
    void (*print)(int [], int);
    void (*assert_eq)(int [], int [], int);
    void (*unique_copy)(int, int[], int[]);
};

extern const struct vec libvec;
