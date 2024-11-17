#include <stdio.h>
#include <stdlib.h>

typedef struct vector
{
    int size;
    int max_size;
    int* array;
} vector_t;

vector_t init_vector(int max_size) {
    vector_t vec;
    vec.size = 0;
    vec.max_size = max_size;
    vec.array = (int *)malloc(sizeof(int) * vec.max_size); 

    return vec;
}

void read_vector(vector_t* vec, FILE* file) {
    while (fscanf(file, "%d", &vec->array[vec->size]) == 1) {
        vec->size++;
        if (getc(file) == '\n') break; 
    }
}

void print_vector(vector_t* vec) {
    for (int i =0; i < vec->size - 1; ++i) {
        printf("%d ", vec->array[i]);
    }
    printf("%d\n", vec->array[vec->size - 1]);
}

vector_t vector_copy(vector_t* vec) {
    vector_t new_vec = init_vector(vec->max_size);
    new_vec.size = vec->size;
    for (int i = 0; i < vec->size; ++i) {
        new_vec.array[i] = vec->array[i];
    }
    return new_vec;
}

