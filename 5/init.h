#pragma once

#include <vector>
#include <random>
#include <time.h>
#include <omp.h>
#include <algorithm>
#define MAX 5
#define MIN -MAX
#define NUM 10
#define K 3

std::vector<std::vector<int>> initTapeMatrixWithSafeMemory() {
    std::vector<std::vector<int>> matrix(NUM, std::vector<int>());
    int sign, limit;
    omp_set_dynamic(1);
    #pragma omp parallel private(sign, limit)
    {
        #pragma omp for
        for (int i = 0; i < NUM; ++i) {
            if (NUM - i <= K){
                limit = K - i + NUM;
            }
            else {
                limit = std::min(i + 1 + K, 2*K + 1);
            }
            for (int j = 0; j < limit; ++j) {
                matrix[i].push_back(rand() % MAX);
                sign = rand() % 2;
                if (sign){
                    matrix[i][j] = -matrix[i][j];
                }
            }
        }
    }
    return matrix;
}

std::vector<std::vector<int>> initTriangeMatrixWithSafeMemory() {
    std::vector<std::vector<int>> matrix(NUM, std::vector<int>());
    int sign;
    omp_set_dynamic(1);
    #pragma omp parallel private(sign)
    {
        #pragma omp for
        for (int i = 0; i < NUM; ++i) {
            for (int j = 0; j < NUM - i; ++j) {
                matrix[i].push_back(rand() % MAX);
                sign = rand() % 2;
                if (sign){
                    matrix[i][j] = -matrix[i][j];
                }
            }
        }
    }
    return matrix;
}