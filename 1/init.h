#pragma once

#include <vector>
#include <random>
#include <time.h>
#include <omp.h>
#define MAX 10000
#define MIN -MAX
#define NUM 100

void initVector(std::vector<int> &vec) {
    srand(time(0));
    int sign;
    #pragma omp parallel for shared(vec)
    for (int i = 0; i < NUM; ++i) {
        vec[i] = rand() % MAX;
        sign = rand() % 2;
        if (sign){
            vec[i] = -vec[i];
        }
    }
}