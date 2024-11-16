#pragma once

#include <vector>
#include <random>
#include <time.h>
#include <omp.h>
#define MAX 10000
#define NUM 100000000

std::vector<int> initVector() {
    std::vector<int> vec(NUM);
    int sign;
    #pragma omp parallel for shared(vec)
    for (int i = 0; i < NUM; ++i) {
        vec[i] = rand() % MAX;
        sign = rand() % 2;
        if (sign){
            vec[i] = -vec[i];
        }
    }
    return vec;
}