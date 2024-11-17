#pragma once

#include <omp.h>
#include <vector>
#include <random>
#include <time.h>
#define MAX 10000
#define MIN -MAX
#define NUM 100

void initMatrix(std::vector<std::vector<int>> &matrix) {
    int sign;
    #pragma omp parallel for
    for (int i = 0; i < NUM; ++i) {
        #pragma omp parallel for
        for (int j = 0; j < NUM; ++j) {
            matrix[i][j] = rand() % MAX;
            sign = rand() % 2;
            if (sign){
                matrix[i][j] = -matrix[i][j];
            }
        }
    }
}