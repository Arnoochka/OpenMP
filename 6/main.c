#include <omp.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define N 5000
#define MAX 1000
#define MAX_SIZE 100

// сгенерировать N векторов
int main(int argc, char* argv[]) {
    int sign, n;
    srand(time(0));
    int* arr[2][N];
    FILE *file = fopen("arrays.txt", "w");

    double start = omp_get_wtime();
    #pragma omp parallel private(n)
    {
        #pragma omp for 
        for (int k = 0; k < N; ++k) {
            n = (rand() % MAX_SIZE) + 1;
            arr[0][k] = (int *)malloc(sizeof(int) * n);
            arr[1][k] = (int *)malloc(sizeof(int) * n);
            for (int i = 0; i < n; ++i) {
                arr[0][k][i] = rand() % MAX;
                arr[1][k][i] = rand() % MAX;

                if (rand() % 2) arr[0][k][i] = -arr[0][k][i];
                if (rand() % 2) arr[1][k][i] = -arr[1][k][i];
            }

            #pragma omp critical
            {
                for (int i = 0; i < n; ++i) {
                    fprintf(file, "%d ", arr[0][k][i]);
                }
                fprintf(file, "\n");

                for (int i = 0; i < n; ++i) {
                    fprintf(file, "%d ", arr[1][k][i]);
                }
                fprintf(file, "\n");
                fprintf(file, "\n");
            }
        }
        #pragma omp for 
        for (int k = 0; k < N; ++k) {
            free(arr[0][k]);
            free(arr[1][k]);
        }  
    }
    fclose(file);
    double end = omp_get_wtime();

    printf("time: %f\n", end - start);
    return 0;
}