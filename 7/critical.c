#include <stdlib.h>
#include <stdio.h>
#include <omp.h>
#include "init.h"

int main(int argc, char* argv[]) {
    int** matrix = generateMatrix();
    if (!matrix) {
        printf("матрица не сгенерирована \n");
        return 1;
    }
    int maxValue, sumValues=0;
    
    double start = omp_get_wtime();
    #pragma omp parallel for private(maxValue)
    for (int i = 0; i < N; ++i) {
        maxValue = -MAX;
        for (int j = 0; j < M; ++j) {
            if (maxValue < matrix[i][j]) maxValue = matrix[i][j];
        }
        #pragma omp critical
        sumValues += maxValue;
    }
    double end = omp_get_wtime();

    if (argc > 1){
        switch (atoi(argv[1]))
        {
        case 1:
            printf("sum: %d\n", sumValues);
            break;
        
        case 2:
            printMatrix(matrix);
            printf("sum: %d\n", sumValues);
            break;
        default:
            break;
        }
    }
    printf("time: %f\n", end - start);

    return 0;
}