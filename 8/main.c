#include <omp.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "Buffer.h"

#define MAX_SIZE_BUFFER 50

void wait_pair(buffer_t* buf) {
    while (1) {
        if (!isEmpty(buf)) {
            break;
        }
    }
} 

void wait_calculation(buffer_t* buf) {
    while (1) {
        if (!isFull(buf)) {
            break;
        }
    }    
} 

int main(int argc, char* argv[]) {
    FILE* file;
    int num_pairs, max_size;
    long long* results; 
    buffer_t buffer = init_buffer(MAX_SIZE_BUFFER);


    file = fopen("arrays.txt", "r");
    if (file == NULL) {
        printf("Не удалось открыть файл\n");
        return 1;
    }

    if (fscanf(file, "%d %d", &num_pairs, &max_size) != 2) {
        printf("Ошибка при чтении чисел\n");
        fclose(file);
        return 1;
    }
    results = (long long *)malloc(sizeof(long long) * num_pairs);

    double start = omp_get_wtime();
    #pragma omp parallel sections
    {
        #pragma omp section
        {
            pair_t pair;

            for (int i = 0; i < num_pairs; ++i) {
                wait_calculation(&buffer);
                pair.first = init_vector(max_size);
                pair.second = init_vector(max_size);
                read_vector(&pair.first, file);
                read_vector(&pair.second, file);
                #pragma omp critical 
                {
                    enbuffer(&buffer, &pair);
                    free(pair.first.array);
                    free(pair.second.array);
                }
            }
        }

        #pragma omp section
        {
            long long result;
            pair_t pair;

            for (int i = 0; i < num_pairs; ++i) {
                result = 0;
                wait_pair(&buffer);
                #pragma omp critical
                {
                pair = debuffer(&buffer);
                }
                #pragma omp parallel for reduction(+:result)
                for (int k = 0; k < pair.first.size; ++k) {
                    result += pair.first.array[k] * pair.second.array[k];
                }
                results[i] = result;
            }
        }
    }
    double end = omp_get_wtime();

    if (argc > 1){
        switch (atoi(argv[1]))
        {
        case 1:
            for (int i = 0; i < num_pairs; ++i) {
                printf("%lld ", results[i]);
            }
            printf("\n");

            break;
        
        case 2:
            printf("входные значения в arrays.txt\n");
            for (int i = 0; i < num_pairs; ++i) {
                printf("%lld ", results[i]);
            }
            printf("\n");

            break;
        default:
            break;
        }
    }

    printf("time: %f\n", end - start);

    fclose(file);
    free(results);
    for (int i = 0; i < buffer.size; ++i) {
        free(buffer.data->first.array);
        free(buffer.data->second.array);
    }
    free(buffer.data);

    return 0;
}