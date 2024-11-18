#include <stdlib.h>
#include <stdio.h>
#include <omp.h>
#include <time.h>

#define N 5000 // количество векторов
#define M 1000 // размер векторов
#define MAX 5

int** generateMatrix() {
    int** matrix = (int**)malloc(N * sizeof(int*));
    if (!matrix) {
        perror("Ошибка выделения памяти для строк матрицы");
        return NULL;
    }
    for (int i = 0; i < N; i++) {
        matrix[i] = (int*)malloc(M * sizeof(int));
        if (!matrix[i]) {
            perror("Ошибка выделения памяти для столбцов матрицы");
            for (int j = 0; j < i; j++) {
                free(matrix[j]);
            }
            free(matrix);
            return NULL;
        }
    }
    #pragma omp parallel for
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            matrix[i][j] = rand() % MAX;
            if (rand() %2) matrix[i][j] = -matrix[i][j];
        }
    }

    return matrix;
}

void freeMatrix(int** matrix) {
    #pragma omp parallel for
    for (int i = 0; i < N; i++) {
        free(matrix[i]);
    }
    free(matrix);
}

void printMatrix(int** matrix) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            printf("%d ", matrix[i][j]);
        }
        printf("\n");
    }
}